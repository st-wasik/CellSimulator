#pragma once
#include <SFML/Graphics.hpp>

class Food : public sf::Drawable
{
public:
	Food();
	Food(int radius, sf::Vector2f position, sf::Color color);
	~Food();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::CircleShape shape;
};

