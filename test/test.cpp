
#include "Include.h"
//#include "BasicUsageEnvironment.hh"

#include "RTSPSession.h"
#include "CRTSPClient.h"


//#pragma comment (lib, "Ws2_32.lib") 
//#pragma comment (lib, "BasicUsageEnvironment.lib")
//#pragma comment (lib, "groupsock.lib")
//#pragma comment (lib, "liveMedia.lib")
//#pragma comment (lib, "UsageEnvironment.lib")


//rtsp://191.191.16.253:554/cam/realmonitor?channel=1&subtype=0&unicast=true&proto=Onvif


int main(){

	string progName = "admin:admin";
	string rtspURL = "rtsp://191.191.16.253:554/cam/realmonitor?channel=1&subtype=0&unicast=true&proto=Onvif";
	int debugLevel = 0;
	CRTSPSession* pRtsp = new CRTSPSession;


	if (pRtsp->startRTSPClient(progName.data(), rtspURL.data(), debugLevel)){
		delete pRtsp;
		pRtsp = NULL;
		return -1;
	}

	for (int j = 0; j < 90; j++){

	}


	int i = 0;
	for (i = 0; i < 50000; i++)
	{
		Sleep(10000);
	}






	//Í£Ö¹µÄÊ±ºò£º
	pRtsp->stopRTSPClient();
	delete pRtsp;
	pRtsp = NULL;

	int c = 0;
	c = add(5);
	getchar();
	getchar();
	return 1;
}








