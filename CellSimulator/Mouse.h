#pragma once
#include <SFML/Window/Mouse.hpp>

namespace cell
{
	/*
	Provides access to mouse events
	*/
	class Mouse
	{
	public:
		Mouse() = delete;
		~Mouse();

		static void update();

		static sf::Vector2f getPosition();

		static sf::Vector2f getPositionShift();

		static bool wasLeftPressed();

		static bool wasLeftReleased();

		static bool isLeftPressed();

		static bool wasRightPressed();

		static bool wasRigthReleased();

		static bool isRightPressed();

		static void setWheelDelta(const float&);

		static float getWheelDelta();

	private:
		static bool _currentIsLeftPressed;
		static bool _currentIsRightPressed;
		static bool _prevIsLeftPressed;
		static bool _prevIsRightPressed;
		static sf::Vector2f _currentPosition;
		static sf::Vector2f _prevPosition;
		static float _wheelDelta;
	};
}