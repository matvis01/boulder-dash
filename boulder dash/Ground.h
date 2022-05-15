#pragma once
#include "GameTile.h"
class Ground :
    public GameTile
{
public:

    bool fallDown();
    bool fallLeft();
    bool fallRight();
    bool getIsMoving();
    bool getIsMovingSideways();
    void changeIsMoving();
    bool moveSideways(bool movesLeft, float speed);

    Ground(float, float);
    ~Ground();
    void SetupVariables();
};

