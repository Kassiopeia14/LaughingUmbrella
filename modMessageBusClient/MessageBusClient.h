#pragma once

#include <iostream>

#include "../modHTTP/POST_HTTPRequest.h"
#include "../modHTTP/GET_HTTPRequest.h"

#include "JSONConvert.h"
#include "WorldInitialState.h"

class MessageBusClient
{
public:

	MessageBusClient();
	~MessageBusClient();

	std::string sendWorldInitialState(WorldInitialState worldInitialState);
	
	WorldInitialState getWorldInitialState();

private:

};

