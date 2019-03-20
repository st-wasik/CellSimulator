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

	float getSize();
	void setSize(const float&);

	float getRotation();
	void setRotation(const float&);

	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f&);

	std::string toString();

	void simulateHunger();


	// for moving cell by user
	void freeze();
	void unfreeze();

private:

	// vector of pointers to role-functions
	std::vector<void(*)(Cell*)> roles;

	sf::CircleShape cell;


	// curent cell stats:

	double currentSpeed;

	double foodLevel;

	bool freezed;
};

