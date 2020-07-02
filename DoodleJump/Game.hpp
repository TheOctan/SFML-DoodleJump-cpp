#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include<SFML/Graphics.hpp>
#include<vector>

#include"Player.hpp"
#include"Platform.hpp"

namespace DoodleJump
{
	typedef std::vector<Platform> PlatformHolder;

	class Game
	{
	public:
		Game(
			sf::Texture& backgroud_t,
			sf::Texture& platform_t,
			sf::Texture& doodle_t,
			sf::Font&	 font
		);

		void update();
		void render(sf::RenderWindow& window);
		void reset();

		bool isGameOver() const;

	private:
		
		sf::Sprite		background_s;
		sf::Text		gameOver_text;
		sf::Text		score_text;
		sf::Text		continue_text;

		Player			player;
		PlatformHolder	platforms;

		sf::Clock		clock;

		bool			gameOver;
		float			gameOverTimer;
		float			score;
	};

} // namespace game

#endif // !GAME_HPP


