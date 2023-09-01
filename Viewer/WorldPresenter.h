#pragma once

#include <chrono>

#include "../modMessageBusClient/WorldInitialState.h"
#include "../modMessageBusClient/MessageBusClient.h"
#include "../modMessageBusClient/AgentState.h"
#include "QTable.h"

class WorldPresenter
{
public:
	WorldPresenter();
	~WorldPresenter();

	WorldInitialState getWorldInitialState();

	void setEpoch(int number);

	AgentState getCurrentAgentState();

	void setQFunction();

	QTableCell getQFunction(int x, int y);

private:

	MessageBusClient messageBusClient;

	WorldInitialState worldInitialState;

	QTable qTable;

	Epoch epoch;

	int stateNumber;

	std::chrono::time_point<std::chrono::system_clock> begin;

};
