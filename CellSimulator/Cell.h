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
#include "Ranged.h"
#include "MixDouble.h"


class CellRoles;

class Cell : public BaseObj
{
	friend class CellRoles;

	friend class CellFactory;

public:
	enum class Type
	{
		Passive, Aggressive, Random, GreenLettuce
	};

	template <typename ... Types>
	static std::shared_ptr<Cell> create(Types ... values);

	~Cell();

	void update();

	// for moving cell by user
	void freeze();
	void unfreeze();

	// Marks cell as killed. It will be moved to dead cells vector in next loop turn.
	void kill();
	bool isDead();

	Genes& getGenes();
	double getFoodLevel();
	double getCurrentSpeed();

	void setCurrentSpeed(double speed);
	void setFoodLevel(double foodLevel);
	void setAge(double age);
	void setHorniness(double horniness);
	Ranged<double, 0, 100>& getHorniness();

	void dropRole(void(*role)(Cell*));
	void addRole(void(*role)(Cell*));

	double age;

	// returns string with cell description that can be used to save cell from environment to file (contains current stats, position etc.)
	std::string getCellSaveString();

	// returns string with cell description that can be used to save cell created in workshop (without stats, position, etc.)
	std::string getCellBlueprintString();

private:
	Cell(float size, sf::Vector2f position, sf::Color color);
	Cell(Cell a, Cell b);

	// vector of pointers to role-functions
	std::vector<void(*)(Cell*)> roles;

	// returns vector of all objects colliding with cell
	std::shared_ptr<std::vector<std::shared_ptr<BaseObj>>> getFoodCollisionVector();

	// curent cell stats:

	double currentSpeed;

	double foodLevel;

	bool freezed = false;

	bool dead = false;

	Genes genes;

	Ranged<double, 0, 100> horniness;

};

template<typename ...Types>
inline std::shared_ptr<Cell> Cell::create(Types ...values)
{
	auto result = std::make_shared<Cell>(Cell(values...));
	result->setSelfPtr(result);
	return result;
}
