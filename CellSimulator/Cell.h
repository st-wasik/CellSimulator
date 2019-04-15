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
	void dropRoles();
	void addRole(void(*role)(Cell*));

	double age;

	// returns string with cell description that can be used to save cell from environment to file (contains current stats, position etc.)
	std::string getSaveString();

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
	struct VarAbbrv final
	{
		static constexpr const char *const currentRotation = "Rotation";
		static constexpr const char *const currentPosition = "Position";
		static constexpr const char *const color = "Color";
		static constexpr const char *const currentAge = "Age";
		static constexpr const char *const currentSpeed = "Speed";
		static constexpr const char *const currentSize = "Size";
		static constexpr const char *const isDead = "isDead";
		static constexpr const char *const currentFoodLevel = "FoodLevel";
		static constexpr const char *const isFreezed = "isFreezed";
		static constexpr const char *const horniness = "Fertility";
		static constexpr const char *const cellRoles = "Roles";

		static constexpr const char *const aggression = "G_Aggression";
		static constexpr const char *const divisionTh = "G_DivisionTh";
		static constexpr const char *const foodLimit = "G_FoodLimit";
		static constexpr const char *const maxAge = "G_MaxAge";
		static constexpr const char *const maxSize = "G_MaxSize";
		static constexpr const char *const maxSpeed = "G_MaxSpeed";
		static constexpr const char *const radarRange = "G_RadarRg";

	private:
		VarAbbrv() = delete;
		VarAbbrv(const VarAbbrv&) = delete;
		VarAbbrv& operator=(const VarAbbrv&) = delete;
		virtual ~VarAbbrv() = 0;
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
