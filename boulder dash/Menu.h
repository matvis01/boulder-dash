#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

using namespace sf;
using namespace std;

class Menu
{
    RenderWindow* window;
     
    Event sfmlEvent;

    Font font;
    vector<Text> text;

public:
    int selectedButton = 0;
    void update();
    void render();

    Menu(RenderWindow* window,String, String);
    Menu(RenderWindow* window, String, String,String);
    ~Menu();

    void MoveUp();
    void MoveDown();
    void pollEvents();
};

