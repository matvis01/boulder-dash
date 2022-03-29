#pragma once
#include "GameTile.h"
#include <iostream>
#include<string>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class Wall :public GameTile
{

public:
    bool fallDown();
    bool fallLeft();
    bool fallRight();
    bool getIsMoving();
    void changeIsMoving();

    Wall(float, float);
    ~Wall();
    void SetupVariables();
};

