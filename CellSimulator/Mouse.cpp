#include "Mouse.h"

#include <iostream>
#include "MainApp.h"

using cell::Mouse;

bool Mouse::_prevIsLeftPressed = false;
bool Mouse::_prevIsRightPressed = false;
bool Mouse::_currentIsLeftPressed = false;
bool Mouse::_currentIsRightPressed = false;
sf::Vector2f Mouse::_currentPosition = sf::Vector2f(0, 0);
sf::Vector2f Mouse::_prevPosition = sf::Vector2f(0, 0);
float Mouse::_wheelDelta = 0.f;

Mouse::~Mouse()
{
}

void Mouse::update()
{
	_prevPosition = _currentPosition;
	_currentPosition = MainApp::getWindowHandle().mapPixelToCoords(sf::Mouse::getPosition(MainApp::getWindowHandle()), MainApp::getViewHandle());
	_prevIsLeftPressed = _currentIsLeftPressed;
	_prevIsRightPressed = _currentIsRightPressed;
	_currentIsLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	_currentIsRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	_wheelDelta = 0;
}

sf::Vector2f Mouse::getPosition()
{
	return _currentPosition;
}

sf::Vector2f cell::Mouse::getPositionShift()
{
	auto x = _currentPosition - _prevPosition;
	return x;
}

bool Mouse::wasLeftPressed()
{
	return !_prevIsLeftPressed && _currentIsLeftPressed;
}

bool Mouse::wasLeftReleased()
{
	return _prevIsLeftPressed && !_currentIsLeftPressed;
}

bool Mouse::isLeftPressed()
{
	return _currentIsLeftPressed;
}

bool Mouse::wasRightPressed()
{
	return !_prevIsRightPressed && _currentIsRightPressed;
}

bool Mouse::wasRigthReleased()
{
	return _prevIsRightPressed && !_currentIsRightPressed;
}

bool Mouse::isRightPressed()
{
	return _currentIsRightPressed;
}

void cell::Mouse::setWheelDelta(const float & d)
{
	_wheelDelta = d;
}

float cell::Mouse::getWheelDelta()
{
	return _wheelDelta;
}
