#include "CellSimMouse.h"
#include <iostream>
#include "CellSimApp.h"
#include "GUIManager.h"

bool CellSimMouse::_prevIsLeftPressed = false;
bool CellSimMouse::_prevIsRightPressed = false;
bool CellSimMouse::_currentIsLeftPressed = false;
bool CellSimMouse::_currentIsRightPressed = false;
sf::Vector2f CellSimMouse::_currentPosition = sf::Vector2f(0, 0);
sf::Vector2f CellSimMouse::_prevPosition = sf::Vector2f(0, 0);
float CellSimMouse::_wheelDelta = 0.f;

void CellSimMouse::update()
{
	auto m = sf::Mouse::getPosition(*CellSimApp::getInstance().getWindowHandle());
	if ((m.x < 0 || m.x > CellSimApp::getInstance().getWindowHandle()->getSize().x) || (m.y < 0 || m.y > CellSimApp::getInstance().getWindowHandle()->getSize().y))
		return;
	//if (sf::IntRect(0, 0, GUIManager::backgroundWidth, CellSimApp::getInstance().getWindowHandle()->getSize().y).contains(m))
	//	return;

	_wheelDelta = 0;
	_prevPosition = _currentPosition;
	_currentPosition = CellSimApp::getInstance().window->mapPixelToCoords(sf::Mouse::getPosition(*CellSimApp::getInstance().window), CellSimApp::getInstance().view);
	_prevIsLeftPressed = _currentIsLeftPressed;
	_prevIsRightPressed = _currentIsRightPressed;
	_currentIsLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	_currentIsRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
}

sf::Vector2f CellSimMouse::getPosition()
{
	return _currentPosition;
}

sf::Vector2f CellSimMouse::getPositionShift()
{
	return _currentPosition - _prevPosition;
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
