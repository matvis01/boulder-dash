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
public:
    Rock(float, float);
    ~Rock();
    void changeIsMoving();
    void SetupVariables();

    bool getIsMoving();
    bool fallDown();
    bool fallLeft();
    bool fallRight();
};

