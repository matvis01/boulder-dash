#include "Menu.h"


void Menu::update()
{
	pollEvents();
}

void Menu::render()
{
	for (int i = 0; i < text.size(); i++)
	{
		window->draw(text[i]);
	}
}

Menu::Menu(RenderWindow *window, String s1, String s2)
{
	this->window = window;

	if (!this->font.loadFromFile("fonts/ARCADE_I.ttf"))
		std::cout << ("could not load menu font");


	Text t;
	
	t.setFont(font);
	t.setCharacterSize(50);

	text.push_back(t);
	text[0].setString(s1);
	text[0].setFillColor(Color::Red);
	text[0].setPosition(Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f));
	text[0].setOrigin(text[0].getCharacterSize() * text[0].getString().getSize() / 2.f, text[0].getCharacterSize() / 2.f);


	text.push_back(t);
	text[1].setString(s2);
	text[1].setFillColor(Color::White);
	text[1].setPosition(Vector2f(window->getSize().x / 2.f, window->getSize().y * 3 / 4.f));
	text[1].setOrigin(text[1].getCharacterSize() * text[1].getString().getSize() / 2.f, text[1].getCharacterSize() / 2.f);
  }

Menu::Menu(RenderWindow* window, String s1, String s2, String s3)
{
	this->window = window;

	if (!this->font.loadFromFile("fonts/ARCADE_I.ttf"))
		std::cout << ("could not load menu font");


	Text t;

	t.setFont(font);
	t.setCharacterSize(50);

	text.push_back(t);
	text[0].setString(s1);
	text[0].setFillColor(Color::Red);
	text[0].setPosition(Vector2f(window->getSize().x / 2.f, window->getSize().y / 4.f));
	text[0].setOrigin(text[0].getCharacterSize() * text[0].getString().getSize() / 2.f, text[0].getCharacterSize() / 2.f);


	text.push_back(t);
	text[1].setString(s2);
	text[1].setFillColor(Color::White);
	text[1].setPosition(Vector2f(window->getSize().x / 2.f, window->getSize().y * 2 / 4.f));
	text[1].setOrigin(text[1].getCharacterSize() * text[1].getString().getSize() / 2.f, text[1].getCharacterSize() / 2.f);

	text.push_back(t);
	text[2].setString(s3);
	text[2].setFillColor(Color::White);
	text[2].setPosition(Vector2f(window->getSize().x / 2.f, window->getSize().y * 3 / 4.f));
	text[2].setOrigin(text[2].getCharacterSize() * text[2].getString().getSize() / 2.f, text[2].getCharacterSize() / 2.f);
}

void Menu::pollEvents()
{
	if (this->window->pollEvent(this->sfmlEvent))
	{
		if (sfmlEvent.type == Event::Closed) 
			this->window->close();

		if (sfmlEvent.type == Event::KeyPressed)
		{
			if (this->sfmlEvent.key.code == Keyboard::Down)
				MoveDown();
			if (this->sfmlEvent.key.code == Keyboard::Up)
				MoveUp();
		}
	}
}

Menu::~Menu()
{
}

void Menu::MoveUp()
{
	if (selectedButton > 0)
	{
		text[selectedButton].setFillColor(Color::White);
		selectedButton--;
		text[selectedButton].setFillColor(Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedButton < text.size()-1)
	{
		text[selectedButton].setFillColor(Color::White);
		selectedButton++;
		text[selectedButton].setFillColor(Color::Red);
	}
}
