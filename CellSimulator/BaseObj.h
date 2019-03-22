#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Random.h"

class BaseObj :public sf::Drawable
{
public:
	BaseObj(float size, sf::Vector2f position, sf::Color color);
	~BaseObj();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float getSize();
	void setSize(const float&);

	float getRotation();
	void setRotation(const float&);

	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f&);

	std::string toString();

	bool toDelete;

protected:
	sf::CircleShape shape;
	sf::Color baseColor;
};

