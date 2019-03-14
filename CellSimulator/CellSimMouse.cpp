#include "CellSimMouse.h"
#include <iostream>
#include "CellSimApp.h"

bool CellSimMouse::_prevIsLeftPressed = false;
bool CellSimMouse::_prevIsRightPressed = false;
bool CellSimMouse::_currentIsLeftPressed = false;
bool CellSimMouse::_currentIsRightPressed = false;
sf::Vector2f CellSimMouse::_currentPosition = sf::Vector2f(0, 0);
sf::Vector2f CellSimMouse::_prevPosition = sf::Vector2f(0, 0);
float CellSimMouse::_wheelDelta = 0.f;

void CellSimMouse::update()
{
	_prevPosition = _currentPosition;
	_currentPosition = CellSimApp::window->mapPixelToCoords(sf::Mouse::getPosition(*CellSimApp::window), CellSimApp::view);
	_prevIsLeftPressed = _currentIsLeftPressed;
	_prevIsRightPressed = _currentIsRightPressed;
	_currentIsLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	_currentIsRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	_wheelDelta = 0;
}

sf::Vector2f CellSimMouse::getPosition()
{
	return _currentPosition;
}

sf::Vector2f CellSimMouse::getPositionShift()
{
	auto x = _currentPosition - _prevPosition;
	return x;
}

bool CellSimMouse::wasLeftPressed()
{
	return !_prevIsLeftPressed && _currentIsLeftPressed;
}

bool CellSimMouse::wasLeftReleased()
{
	return _prevIsLeftPressed && !_currentIsLeftPressed;
}

bool CellSimMouse::isLeftPressed()
{
	return _currentIsLeftPressed;
}

bool CellSimMouse::wasRightPressed()
{
	return !_prevIsRightPressed && _currentIsRightPressed;
}

bool CellSimMouse::wasRigthReleased()
{
	return _prevIsRightPressed && !_currentIsRightPressed;
}

bool CellSimMouse::isRightPressed()
{
	return _currentIsRightPressed;
}

void CellSimMouse::setWheelDelta(const float & d)
{
	_wheelDelta = d;
}

float CellSimMouse::getWheelDelta()
{
	return _wheelDelta;
}