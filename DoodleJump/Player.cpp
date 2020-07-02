#include "Player.hpp"
#include "Platform.hpp"

namespace DoodleJump
{
	Player::Player(const sf::Texture& texture, sf::Vector2f position)
	:	_sprite		(texture),
		_position	(position),
		height		(200),
		dx			(0), 
		dy			(-0.6f),
		fell		(false)
	{
		this->_sprite.setOrigin(_sprite.getGlobalBounds().width / 2.f + 10, 0);	
	}

	void Player::update(float time)
	{
		if (isFell()) this->fell = true;

		if (!fell)
			this->control();
		
		if (dx > 0) this->_sprite.setScale(-1, 1);
		if (dx < 0) this->_sprite.setScale(1, 1);

		dy += 0.0006*time;
		if (fell) dy = 0;

		this->_position.x += dx * time;
		this->_position.y += dy * time;

		dx = 0;
		
		if (this->_position.x > 400) this->_position.x = -_sprite.getGlobalBounds().width;
		if (this->_position.x < -_sprite.getGlobalBounds().width) this->_position.x = 400;

		this->_sprite.setPosition(
			this->_position.x + _sprite.getGlobalBounds().width / 2 + 10,
			this->_position.y
		);
	}

	void Player::control()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) dx = 0.2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) dx = -0.2;
	}

	void Player::collision(const sf::FloatRect& rect)
	{
		if (
			(this->_position.x + 50 > rect.left) &&
			(this->_position.x + 20 < rect.left + 68) &&
			(this->_position.y + 70 > rect.top) &&
			(this->_position.y + 70 < rect.top + 14) &&
			(this->dy > 0)
			)
		{
			this->dy = -0.6f;
		}
	}

	void Player::freeze()
	{
		this->_position.y = this->height;
	}

	void Player::moveDown(float offset)
	{
		this->_position.y += abs(offset);
		if (this->_position.y > 533) this->_position.y = 533;
	}

	void Player::reset()
	{
		// сбрасываем параметры персонажа выставляя значения по умолчанию
		this->fell = false;
		this->_position = sf::Vector2f(200, 200);
		this->dy = -0.6;
	}

	float Player::getVerticalAcceleration() const
	{
		return this->dy;
	}

	bool Player::isJump() const
	{
		return this->_position.y < this->height;
	}

	bool Player::isFell() const
	{
		return this->_position.y + 70 > 533;
	}

	void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(this->_sprite);
	}
}
