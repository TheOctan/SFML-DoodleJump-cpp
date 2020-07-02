#include "Game.hpp"

namespace DoodleJump
{
	Game::Game(
		sf::Texture& backgroud_t,
		sf::Texture& platform_t,
		sf::Texture& doodle_t,
		sf::Font&	 font
	)
	:	player			(doodle_t, sf::Vector2f(200, 200)),
		platforms		(10, Platform(platform_t)),
		gameOver_text	("Game Over", font, 100),
		score_text		("0", font, 60),
		continue_text	("Press space to continue...", font, 40),
		gameOver		(false),
		gameOverTimer	(0)
	{
		this->background_s.setTexture(backgroud_t);

		this->gameOver_text.setFillColor(sf::Color::Red);
		this->gameOver_text.move(12, 120);
		
		this->score_text.setFillColor(sf::Color::Red);
		this->score_text.setStyle(sf::Text::Style::Bold);
		this->score_text.setPosition(10, 0);

		this->continue_text.setFillColor(sf::Color::Red);
		this->continue_text.setPosition(10, 480);

		for (auto& platform : this->platforms)
			platform.random();
	}

	void Game::update()
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 500;

		// updating game logic
		player.update(time);
		for (auto& platform : this->platforms)
		{
			platform.update(time);
			player.collision(platform.getBoxCollider());
		}

		if (player.isJump())
		{
			this->score += abs(player.getVerticalAcceleration()) / 30.f;

			player.freeze();
			for (auto& platform : this->platforms)
				platform.moveDown(player.getVerticalAcceleration()*time);
		}

		if (player.isFell()) gameOver = true;

		if (gameOver)
		{
			for (auto& platform : this->platforms)
				platform.moveUp(0.6*time);

			this->gameOverTimer += time;

			if (!(gameOverTimer > 1000))
				this->score_text.move(0, -0.6*time);
		}
		else
		{
			this->score_text.setString(std::to_string((int)score) + " m");
		}
		
		if (gameOverTimer > 1000 && gameOver)
		{
			this->score_text.setString("Score: " + std::to_string((int)score));
			this->score_text.setPosition(100, 250);

			this->player.moveDown(0.2*time);
		}
	}

	void Game::render(sf::RenderWindow & window)
	{
		window.draw(background_s);
		window.draw(player);
		for (const auto& platform : this->platforms)						
			window.draw(platform);

		window.draw(score_text);

		if (gameOver)
		{
			window.draw(gameOver_text);
			
			if(gameOverTimer > 1000)
				window.draw(continue_text);
		}
	}

	void Game::reset()
	{
		this->gameOver = false;
		this->score = 0.f;
		this->gameOverTimer = 0.f;

		this->player.reset();
		this->score_text.setPosition(10, 0);

		for (auto& platform : this->platforms)
			platform.random();
	}

	bool Game::isGameOver() const
	{
		return this->gameOverTimer > 1000 && this->gameOver;
	}
}
