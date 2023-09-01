#include "WorldPresenter.h"

WorldPresenter::WorldPresenter():
	messageBusClient(),
	worldInitialState(messageBusClient.getWorldInitialState())

{
}

WorldPresenter::~WorldPresenter()
{
}

WorldInitialState WorldPresenter::getWorldInitialState()
{
	return worldInitialState;
}