#pragma once

#include <chrono>

#include "../modMessageBusClient/WorldInitialState.h"
#include "../modMessageBusClient/MessageBusClient.h"
#include "../modMessageBusClient/AgentState.h"

class WorldPresenter
{
public:
	WorldPresenter();
	~WorldPresenter();

	WorldInitialState getWorldInitialState();

	void setEpoch(int number);

	AgentState getCurrentAgentState();

private:

	MessageBusClient messageBusClient;

	WorldInitialState worldInitialState;

	Epoch epoch;

	int stateNumber;

	std::chrono::time_point<std::chrono::system_clock> begin;

};
