#include "Player.h"

Player::Player(string color)
{
	_color = color;
}

Player::~Player()
{
}

//
void Player::setColor(string color)
{
	_color = color;
}

// a function return color
string Player::getColor() const
{
	return _color;
}
