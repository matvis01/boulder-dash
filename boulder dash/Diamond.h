#pragma once
#include "GameTile.h"
class Diamond :
    public GameTile
{
    bool isMoving;
public:
    Diamond(float, float);
    ~Diamond();
    void changeIsMoving();
    void SetupVariables();

    bool getIsMovingSideways();
    bool getIsMoving();
    bool fallDown();
    bool fallLeft();
    bool fallRight();

    bool moveSideways(bool movesLeft, float speed);
};

