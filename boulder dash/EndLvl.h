#pragma once
#include "GameTile.h"
class EndLvl :
    public GameTile
{
public:

    bool fallDown();
    bool fallLeft();
    bool fallRight();
    bool getIsMoving();
    void changeIsMoving();
    bool moveSideways(bool movesLeft, float speed);

    EndLvl(float, float);
    ~EndLvl();
    void SetupVariables();
};
