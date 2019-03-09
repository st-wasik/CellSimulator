#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Cell : public sf::Drawable
{
public:
	Cell();
	Cell(double size, sf::Vector2f position);
	~Cell();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::CircleShape cell;
	double currentSpeed;
	double currentRotation;
	double foodLevel;
	double size;
	bool wantToBieszczady;
	
};

