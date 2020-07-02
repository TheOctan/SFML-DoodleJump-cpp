#pragma once

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include<SFML/Graphics.hpp>

namespace DoodleJump
{
	class Player : public sf::Drawable
	{
	public:
		Player(
			const sf::Texture& texture,
			sf::Vector2f position = sf::Vector2f(0, 0)
		);
		
		void update(float time);
		void control();
		void collision(const sf::FloatRect& rect);
		void freeze();
		void moveDown(float offset);
		void reset();

		float getVerticalAcceleration() const;
		bool isJump() const;
		bool isFell() const;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		
		sf::Sprite		_sprite;
		sf::Vector2f	_position;

		int		height;
		float	dx;
		float	dy;
		bool	fell;
	};

} // namespace game

#endif // !PLAYER_HPP
