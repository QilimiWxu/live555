#pragma once


#include "ourRTSPClient.h"

 // by default, print verbose output from each "RTSPClient"


class CRTSPSession
{
public:
	CRTSPSession();
	virtual ~CRTSPSession();
	void rtsp_fun();
	int startRTSPClient(char const* progName, char const* rtspURL, int debugLevel);
	int stopRTSPClient();
	int openURL(UsageEnvironment& env, char const* progName, char const* rtspURL, int debugLevel);


private:
	RTSPClient* m_rtspClient;
	char eventLoopWatchVariable;
	//pthread_t tid;
	LPDWORD tid;
	HANDLE hThread;
	volatile int m_nStatus;
	bool m_running;
	string m_rtspUrl;
	const char* cm_rtspUrl;
	string m_progName;
	const char* cm_progName;
	int m_debugLevel;
	//volatile int iThreadData;//临界区数据
	//static void *rtsp_thread_fun(void *param);
};

