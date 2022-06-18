#pragma once
#include "functions.h"


using namespace sf;
using namespace std;

class Menu
{
    RenderWindow* window;
     
    Event sfmlEvent;

    Font font;
    vector<Text> text;

    Texture texture;
    Sprite sprite;

public:
    int selectedButton = 0;
    void render();

    Menu(RenderWindow* window,String, String);
    Menu(RenderWindow* window, String, String,String);
    ~Menu();

    void MoveUp();
    void MoveDown();
};

