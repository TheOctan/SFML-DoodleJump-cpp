#pragma once

#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include<SFML/Graphics.hpp>

namespace DoodleJump
{
	class Platform : public sf::Drawable
	{
	public:
		Platform(const sf::Texture& texture);

		void update(float time);
		void moveDown(float offset);
		void moveUp(float offset);
		void spawn();
		void random();

		sf::FloatRect getBoxCollider() const;

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:

		sf::Sprite		_sprite;
		sf::Vector2f	_position;

	};

} // namespace game

#endif // !PLAYER_HPP
