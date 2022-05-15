#pragma once
#include "GameTile.h"
#include <iostream>
#include<string>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"


class Rock :
    public GameTile
{
    bool isMoving;
    bool isMovingSideways;
public:
    Rock(float, float);
    ~Rock();
    void changeIsMoving();
    void SetupVariables();

    bool getIsMovingSideways();
    bool getIsMoving();
    bool fallDown();
    bool fallLeft();
    bool fallRight();

    bool moveSideways(bool movesLeft , float speed);
};

