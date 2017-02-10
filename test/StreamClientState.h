
#pragma once

#include "Include.h"

class StreamClientState
{
public:
	StreamClientState();
	virtual ~StreamClientState();
public:
	MediaSubsessionIterator* iter;
	MediaSession* session;
	MediaSubsession* subsession;
	TaskToken streamTimerTask;
	double duration;
};

