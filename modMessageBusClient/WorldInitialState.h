#pragma once

#include "AppleSet.h"
#include "Pit.h"

struct WorldInitialState
{
    AppleSet appleSet;

    Pit pit;

    int 
        startX,
        startY;
};
