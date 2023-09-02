#include <iostream>
#include "../modHTTP/POST_HTTPRequest.h"
#include "../modMessageBusClient/MessageBusClient.h"
#include "../modMessageBusClient/Epoch.h"
#include "Engine.h"


int main()
{
	Engine engine;

	MessageBusClient MessageBusClient;

	std::string postWorldInitialStateResult = MessageBusClient.sendWorldInitialState(engine.getWorldInitialState());

	std::cout << "POST: " << postWorldInitialStateResult << std::endl;

	//---------------------------------------

	for (int i = 0; i < 10000; i++)
	{
		Epoch epoch = engine.processEpoch();

		std::string postEpochResult = MessageBusClient.sendEpoch(epoch);
		
		std::cout << "POST: " << postEpochResult << std::endl;
	}
	system("pause");
}