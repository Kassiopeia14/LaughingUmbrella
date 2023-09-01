#pragma once
#include "../modMessageBusClient/WorldInitialState.h"
#include "../modMessageBusClient/MessageBusClient.h"

class WorldPresenter
{
public:
	WorldPresenter();
	~WorldPresenter();

	WorldInitialState getWorldInitialState();

private:

	MessageBusClient messageBusClient;

	WorldInitialState worldInitialState;

};
