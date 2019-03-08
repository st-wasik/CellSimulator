#include "Mouse.h"

#include <iostream>
#include "MainApp.h"

using cell::Mouse;

bool Mouse::_prevIsLeftPressed = false;
bool Mouse::_prevIsRightPressed = false;
bool Mouse::_currentIsLeftPressed = false;
bool Mouse::_currentIsRightPressed = false;
sf::Vector2f Mouse::_position = sf::Vector2f(0,0);

Mouse::~Mouse()
{
}

void Mouse::update()
{
	_position = MainApp::getWindowHandle().mapPixelToCoords(sf::Mouse::getPosition(MainApp::getWindowHandle()), MainApp::getViewHandle());
	_prevIsLeftPressed = _currentIsLeftPressed;
	_prevIsRightPressed = _currentIsRightPressed;
	_currentIsLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	_currentIsRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
}

sf::Vector2f Mouse::getPosition()
{
	return _position;
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

bool Mouse::isRigthPressed()
{
	return _currentIsRightPressed;
}
