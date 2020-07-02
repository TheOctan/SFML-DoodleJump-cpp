#include"config.hpp"			// настройки подключения SFML библиотек

#include<SFML/Graphics.hpp>

#include<ctime>
#include<iostream>

#include"Game.hpp"

using namespace DoodleJump;

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(400, 533), "Doodle Jump", sf::Style::Close);
	window.setMouseCursorVisible(false);

	sf::Image icon;
	icon.loadFromFile("images/DoodleJump.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Texture backgroud;
	sf::Texture	platform;
	sf::Texture doodle;
	sf::Font	font;
	
	backgroud.loadFromFile("images/background1.png");
	platform.loadFromFile("images/platform.png");
	doodle.loadFromFile("images/doodle.png");
	font.loadFromFile("fonts/doodleJump.ttf");

	Game game(backgroud, platform, doodle, font);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space || 
			   event.type == sf::Event::MouseButtonPressed)
				if (game.isGameOver())
				{
					game.reset();
				}
		}

		game.update();

		window.clear();
		game.render(window);
		window.display();
	}

	return 0;
}