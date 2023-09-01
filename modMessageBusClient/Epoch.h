#pragma once

#include <vector>
#include "AgentState.h"

struct Epoch
{
	int number;

	std::vector<AgentState> agentStates;
};