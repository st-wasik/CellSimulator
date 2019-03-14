#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Random.h"

class CellRoles;

class Cell : public sf::Drawable
{
	friend class CellRoles;

public:
	Cell(float size, sf::Vector2f position);
	~Cell();

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	// vector of pointers to role-functions
	std::vector<void(*)(Cell*)> roles;

	sf::CircleShape cell;


	// curent cell stats:

	double currentSpeed;

	double foodLevel;

	double size;

	bool wantToBieszczady;
};

