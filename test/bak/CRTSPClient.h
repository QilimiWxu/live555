
#include "Include.h"

DWORD WINAPI ThreadProc(LPVOID lpParam);

void continueAfterDESCRIBE(RTSPClient* rtspClient, int resultCode, char* resultString);
void continueAfterSETUP(RTSPClient* rtspClient, int resultCode, char* resultString);
void continueAfterPLAY(RTSPClient* rtspClient, int resultCode, char* resultString);

// Other event handler functions:
void subsessionAfterPlaying(void* clientData); // called when a stream's subsession (e.g., audio or video substream) ends
void subsessionByeHandler(void* clientData); // called when a RTCP "BYE" is received for a subsession
void streamTimerHandler(void* clientData);
// called at the end of a stream's expected duration (if the stream has not already signaled its end using a RTCP "BYE")

// The main streaming routine (for each "rtsp://" URL):
void openURL(UsageEnvironment& env, char const* progName, char const* rtspURL);

// Used to iterate through each stream's 'subsessions', setting up each one:
void setupNextSubsession(RTSPClient* rtspClient);

// Used to shut down and close a stream (including its "RTSPClient" object):
void shutdownStream(RTSPClient* rtspClient, int exitCode = 1);

// A function that outputs a string that identifies each stream (for debugging output).  Modify this if you wish:
UsageEnvironment& operator<<(UsageEnvironment& env, const RTSPClient& rtspClient);

// A function that outputs a string that identifies each subsession (for debugging output).  Modify this if you wish:
UsageEnvironment& operator<<(UsageEnvironment& env, const MediaSubsession& subsession);

void usage(UsageEnvironment& env, char const* progName);

//class StreamClientState {
//public:
//	StreamClientState();
//	virtual ~StreamClientState();
//
//public:
//	MediaSubsessionIterator* iter;
//	MediaSession* session;
//	MediaSubsession* subsession;
//	TaskToken streamTimerTask;
//	double duration;
//};

//class ourRTSPClient : public RTSPClient {
//public:
//	static ourRTSPClient* createNew(UsageEnvironment& env, char const* rtspURL,
//		int verbosityLevel = 0,
//		char const* applicationName = NULL,
//		portNumBits tunnelOverHTTPPortNum = 0);
//
//protected:
//	ourRTSPClient(UsageEnvironment& env, char const* rtspURL,
//		int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum);
//	// called only by createNew();
//	virtual ~ourRTSPClient();
//
//public:
//	StreamClientState scs;
//};
//
//class DummySink : public MediaSink {
//public:
//	static DummySink* createNew(UsageEnvironment& env,
//		MediaSubsession& subsession, // identifies the kind of data that's being received
//		char const* streamId = NULL); // identifies the stream itself (optional)
//
//private:
//	DummySink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId);
//	// called only by "createNew()"
//	virtual ~DummySink();
//
//	static void afterGettingFrame(void* clientData, unsigned frameSize,
//		unsigned numTruncatedBytes,
//	struct timeval presentationTime,
//		unsigned durationInMicroseconds);
//	void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
//	struct timeval presentationTime, unsigned durationInMicroseconds);
//
//private:
//	// redefined virtual functions:
//	virtual Boolean continuePlaying();
//
//private:
//	u_int8_t* fReceiveBuffer;
//	MediaSubsession& fSubsession;
//	char* fStreamId;
//};

#define RTSP_CLIENT_VERBOSITY_LEVEL 1 // by default, print verbose output from each "RTSPClient"

class CRTSPSession
{
public:
	CRTSPSession();
	virtual ~CRTSPSession();
	int startRTSPClient(char const* progName, char const* rtspURL, int debugLevel);
	int stopRTSPClient();
	int openURL(UsageEnvironment& env, char const* progName, char const* rtspURL, int debugLevel);
	RTSPClient* m_rtspClient;
	char eventLoopWatchVariable;
	//pthread_t tid;
	LPDWORD tid;
	HANDLE hThread;
	volatile int m_nStatus;
	bool m_running;
	string m_rtspUrl;
	string m_progName;
	int m_debugLevel;
	//static void *rtsp_thread_fun(void *param);
	void rtsp_fun();
};
