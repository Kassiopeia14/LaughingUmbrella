#pragma once
#include "QFunction.h"

struct AgentState
{
	int x, y;

	double accumulatedReward;

	QFunction qFunction;
};