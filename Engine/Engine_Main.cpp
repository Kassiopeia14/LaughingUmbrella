#include <iostream>
#include "../modHTTP/POST_HTTPRequest.h"
#include "../modMessageBusClient/MessageBusClient.h"
#include "../modMessageBusClient/Epoch.h"
#include "Engine.h"


int main()
{
	Engine engine;

	MessageBusClient MessageBusClient;

	WorldInitialState worldInitialState
	{
		.apple = {.x = 5, .y = 9},
		.pit =
		{
			.cells = { {.x = 7, .y = 1}, {.x = 7, .y = 2}, {.x = 7, .y = 3} }
		}
	};

	std::string postWorldInitialStateResult = MessageBusClient.sendWorldInitialState(worldInitialState);

	std::cout << "POST: " << postWorldInitialStateResult << std::endl;

	/*
	Epoch epoch = {
		.number = 0,
		.agentStates = 
		{ 
			{.x = 3, .y = 2, .accumulatedReward = engine.getAccumulatedReward(), .qFunction = engine.getQFunction()},
			{.x = 3, .y = 3, .accumulatedReward = engine.getAccumulatedReward(), .qFunction = engine.getQFunction() },
			{.x = 4, .y = 3, .accumulatedReward = engine.getAccumulatedReward(), .qFunction = engine.getQFunction() },
			{.x = 5, .y = 3, .accumulatedReward = engine.getAccumulatedReward(), .qFunction = engine.getQFunction() },
			{.x = 5, .y = 4, .accumulatedReward = engine.getAccumulatedReward(), .qFunction = engine.getQFunction() },
			{.x = 5, .y = 5, .accumulatedReward = engine.getAccumulatedReward(), .qFunction = engine.getQFunction() }
		}
	};

	*/

	//---------------------------------------

	Epoch epoch = engine.processEpoch();

	std::string postEpochResult = MessageBusClient.sendEpoch(epoch);

	std::cout << "POST: " << postEpochResult << std::endl;

	system("pause");
}