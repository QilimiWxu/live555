


#include "RTSPSession.h"
#include "CRTSPClient.h"


DWORD WINAPI ThreadProc(LPVOID lpParam){
	CRTSPSession *pThis = (CRTSPSession*)lpParam;
	pThis->rtsp_fun();
	return 1;
}

CRTSPSession::CRTSPSession(){
	m_rtspClient = NULL;
	m_running = false;
	hThread = NULL;
	eventLoopWatchVariable = 0;
	this->m_debugLevel = 1;
	//iThreadData = 0;
}
CRTSPSession::~CRTSPSession(){
}

int CRTSPSession::startRTSPClient(char const* progName, char const* rtspURL, int debugLevel){
	if (hThread != NULL){
		stopRTSPClient();
	}
	this->m_progName = progName;
	this->m_rtspUrl = rtspURL;
	this->m_debugLevel = debugLevel;
	eventLoopWatchVariable = 0;
	CRTSPSession *pThis = this;
	//int r = pthread_create(&tid, NULL, rtsp_thread_fun, this);
	hThread = CreateThread(NULL, 0, ThreadProc, (LPVOID)pThis, 0, tid);
	if (hThread == NULL)	{
		perror("pthread_create()");
		pThis = NULL; 
		return -1;
	}
	pThis = NULL;
	return 0;
}
int CRTSPSession::stopRTSPClient()
{
	eventLoopWatchVariable = 1;
	CloseHandle(hThread);
	return 0;
}
//void *CRTSPSession::rtsp_thread_fun(void *param)
//{
//	CRTSPSession *pThis = (CRTSPSession*)param;
//	pThis->rtsp_fun();
//	return NULL;
//}
void CRTSPSession::rtsp_fun()
{
	//::startRTSP(m_progName.c_str(), m_rtspUrl.c_str(), m_ndebugLever);
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);
	//if (openURL(*env, m_progName.c_str(), m_rtspUrl.c_str(), m_debugLevel) == 0)
	int i = 0;
	if (openURL(*env, m_progName.data(), m_rtspUrl.data(), m_debugLevel) == 0)
	{
		m_nStatus = 1;
		env->taskScheduler().doEventLoop(&eventLoopWatchVariable);

		m_running = false;
		eventLoopWatchVariable = 0;

		if (m_rtspClient)
		{
			shutdownStream(m_rtspClient, 0);
		}
		m_rtspClient = NULL;
	}

	env->reclaim();
	env = NULL;
	delete scheduler;
	scheduler = NULL;
	m_nStatus = 2;
}
int CRTSPSession::openURL(UsageEnvironment& env, char const* progName, char const* rtspURL, int debugLevel)
{
	m_rtspClient = ourRTSPClient::createNew(env, rtspURL, debugLevel, progName);
	if (m_rtspClient == NULL)
	{
		env << "Failed to create a RTSP client for URL \"" << rtspURL << "\": " << env.getResultMsg() << "\n";
		return -1;
	}
	//((ourRTSPClient*)m_rtspClient)->m_nID = m_nID;
	m_rtspClient->sendDescribeCommand(continueAfterDESCRIBE);
	return 0;
}
