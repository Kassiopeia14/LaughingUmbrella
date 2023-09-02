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

	//---------------------------------------

	for (int i = 0; i < 1000; i++)
	{
		Epoch epoch = engine.processEpoch();

		std::string postEpochResult = MessageBusClient.sendEpoch(epoch);
		
		std::cout << "POST: " << postEpochResult << std::endl;
	}
	system("pause");
}