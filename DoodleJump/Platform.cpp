#include "Platform.hpp"

#include<cstdlib>

namespace DoodleJump
{
	Platform::Platform(const sf::Texture & texture)
	:	_sprite		(texture)
	{
	}

	void Platform::update(float time)
	{
		if (this->_position.y > 533) this->spawn();

		this->_sprite.setPosition(_position);
	}

	void Platform::moveDown(float offset)
	{
		this->_position.y += abs(offset);
	}

	void Platform::moveUp(float offset)
	{
		this->_position.y -= abs(offset);
		if (this->_position.y < -15) this->_position.y = -15;
	}

	void Platform::spawn()
	{
		this->_position.x = float(rand() % 400 - 34);
		this->_position.y = 0;
	}

	void Platform::random()
	{
		this->_position.x = float(rand() % 400 - 34);
		this->_position.y = float(rand() % 533);
	}

	sf::FloatRect Platform::getBoxCollider() const
	{
		return this->_sprite.getGlobalBounds();
	}

	void Platform::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(this->_sprite);
	}
}
