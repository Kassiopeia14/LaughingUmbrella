#include "WorldPresenter.h"

WorldPresenter::WorldPresenter():
	messageBusClient(),
	worldInitialState(messageBusClient.getWorldInitialState()),
    stateNumber(0),
	begin(std::chrono::system_clock::now())
{
}

WorldPresenter::~WorldPresenter()
{
}

WorldInitialState WorldPresenter::getWorldInitialState()
{
	return worldInitialState;
}

void WorldPresenter::setEpoch(int number)
{
    epoch = messageBusClient.getEpoch(number);
}

AgentState WorldPresenter::getCurrentAgentState()
{
    std::chrono::time_point<std::chrono::system_clock> checkPoint = std::chrono::system_clock::now();

    std::chrono::duration<double> duration = checkPoint - begin;

    if (duration.count() > 1.0 / 5)
    {
        begin = checkPoint;

        stateNumber++;

        if (stateNumber == epoch.agentStates.size())
        {
            stateNumber = 0;
        }
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }

	return epoch.agentStates[stateNumber];
}

