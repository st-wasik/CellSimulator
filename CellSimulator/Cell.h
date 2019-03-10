#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Random.h"


#define PI 3.14159265358979323846

class Cell : public sf::Drawable
{
public:
	Cell();
	Cell(double size, sf::Vector2f position);
	~Cell();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	void moveForward();
	void rotateLeft(double angle);
	void rotateRight(double angle);
	sf::CircleShape cell;
	double currentSpeed;
	//double currentRotation; Nie potrzebne bo CircleShape przetrzymuje rotation
	double foodLevel;
	double size;
	bool wantToBieszczady;
	
};

