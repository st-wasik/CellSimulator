#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Random.h"
#include "BaseObj.h"
#include <memory>
#include <algorithm>
#include "Logger.h"
#include "Food.h"
#include "Genes.h"

class CellRoles;

class Cell : public BaseObj
{
	friend class CellRoles;

public:
	Cell(float size, sf::Vector2f position, sf::Color color);
	~Cell();

	void update();


	// for moving cell by user
	void freeze();
	void unfreeze();

	void kill();
	bool isDead();

private:

	// vector of pointers to role-functions
	std::vector<void(*)(Cell*)> roles;

	bool collision(std::shared_ptr<BaseObj> obj);

	// curent cell stats:

	double currentSpeed;

	double foodLevel;

	bool freezed = false;

	bool dead = false;

	Genes genes;
};

