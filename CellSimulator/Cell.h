#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Random.h"
#include "BaseObj.h"

class CellRoles;

class Cell : public BaseObj
{
	friend class CellRoles;

public:
	Cell(float size, sf::Vector2f position, sf::Color color);
	~Cell();

	void update();

	void simulateHunger();


	// for moving cell by user
	void freeze();
	void unfreeze();

private:

	// vector of pointers to role-functions
	std::vector<void(*)(Cell*)> roles;


	// curent cell stats:

	double currentSpeed;

	double foodLevel;

	bool freezed = false;
};

