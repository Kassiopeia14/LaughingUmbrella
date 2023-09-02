#pragma once

#include "Apple.h"
#include "Pit.h"

struct WorldInitialState
{
    Apple apple;

    Pit pit;

    int 
        startX,
        startY;
};
