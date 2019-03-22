#pragma once
#include <SFML/Graphics.hpp>
#include "BaseObj.h"

class Food : public BaseObj
{
public:
	Food(float size, sf::Vector2f position, sf::Color color);

	~Food();

};

