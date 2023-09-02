#include "WorldPresenter.h"

WorldPresenter::WorldPresenter():
	messageBusClient(),
	worldInitialState(messageBusClient.getWorldInitialState()),
    qTable(),
    epochNumber(0),
    stateNumber(0),
	begin(std::chrono::system_clock::now())
{
    setEpoch();
}

WorldPresenter::~WorldPresenter()
{
}

WorldInitialState WorldPresenter::getWorldInitialState()
{
	return worldInitialState;
}

void WorldPresenter::setEpoch()
{
    epoch = messageBusClient.getEpoch(epochNumber);

    setQFunction();
}

AgentState WorldPresenter::getCurrentAgentState()
{
    std::chrono::time_point<std::chrono::system_clock> checkPoint = std::chrono::system_clock::now();

    std::chrono::duration<double> duration = checkPoint - begin;

    if (duration.count() > 1.0 / 60)
    {
        begin = checkPoint;

        stateNumber++;

        if (stateNumber == epoch.agentStates.size())
        {
            stateNumber = 0;

            epochNumber++;
            if (epochNumber == 1000)
            {
                epochNumber = 0;
            }
            setEpoch();
        }

        setQFunction();
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }

	return epoch.agentStates[stateNumber];
}

void WorldPresenter::setQFunction()
{
    AgentState agentState = epoch.agentStates[stateNumber];

    qTable.setQFunction(agentState.x, agentState.y, agentState.qFunction);
}

QTableCell WorldPresenter::getQFunction(int x, int y)
{
    return qTable.getQFunction(x, y);
}
