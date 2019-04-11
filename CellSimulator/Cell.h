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

	using Ptr = std::shared_ptr<Cell>;

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
	Cell(std::string formattedCellString);

	void modifyValueFromString(std::string valueName, std::string value);

	// vector of pointers to role-functions
	std::vector<void(*)(Cell*)> roles;

	// returns vector of all foods colliding with cell
	std::shared_ptr<std::vector<std::shared_ptr<BaseObj>>> getFoodCollisionVector();

	// curent cell stats:

	double currentSpeed;

	double foodLevel;

	bool freezed = false;

	bool dead = false;

	Genes genes;

	Ranged<double, 0, 100> horniness;

	// abbreviation used to save cell to file
	struct VarAbbrv
	{
		static constexpr const char *const currentRotation = "CRROT";
		static constexpr const char *const currentPositionX = "CPOSX";
		static constexpr const char *const currentPositionY = "CPOSY";
		static constexpr const char *const colorR = "COLRR";
		static constexpr const char *const colorG = "COLRG";
		static constexpr const char *const colorB = "COLRB";
		static constexpr const char *const colorA = "COLRA";
		static constexpr const char *const currentAge = "CRAGE";
		static constexpr const char *const currentSpeed = "CRSPD";
		static constexpr const char *const currentSize = "CRSIZ";
		static constexpr const char *const isDead = "CDEAD";
		static constexpr const char *const currentFoodLevel = "FDLVL";
		static constexpr const char *const isFreezed = "FRZED";
		static constexpr const char *const horniness = "HRNES";

		static constexpr const char *const aggression = "AGGRN";
		static constexpr const char *const divisionTh = "DIVTH";
		static constexpr const char *const foodLimit = "FDLIM";
		static constexpr const char *const maxAge = "MXAGE";
		static constexpr const char *const maxSize = "MXSIZ";
		static constexpr const char *const maxSpeed = "MXSPD";
		static constexpr const char *const radarRange = "RADRG";

	private:
		VarAbbrv() = delete;
		VarAbbrv(const VarAbbrv&) = delete;
		VarAbbrv& operator=(const VarAbbrv&) = delete;
	};

};

template<typename ...Types>
inline std::shared_ptr<Cell> Cell::create(Types ...values)
{
	Cell::Ptr result;
	try
	{
		result = std::make_shared<Cell>(Cell(values...));
	}
	catch (std::exception e)
	{
		Logger::log(e.what());
		result = std::make_shared<Cell>(Cell(20, { 0,0 }, sf::Color::White));
	}
	result->setSelfPtr(result);
	return result;
}
