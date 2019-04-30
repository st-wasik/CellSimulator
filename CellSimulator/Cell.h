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
		Passive, Aggressive, Random, GreenLettuce, Pizza
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

	std::string getName();
	void setName(std::string n);

	void setMakedFoodColor(sf::Color c);
	sf::Color getMakedFoodColor();

private:
	explicit Cell();
	Cell(float size, sf::Vector2f position, sf::Color color);
	Cell(Cell a, Cell b);
	Cell(std::string formattedCellString);

	void modifyValueFromString(std::string valueName, std::string value);
	void modifyValueFromVector(std::string valueName,const std::vector<std::string>& value);

	// vector of pointers to role-functions
	std::vector<void(*)(Cell*)> roles;

	void getFoodCollisionVector();
	void getCellCollisionVector();
	// curent cell stats:

	double currentSpeed;

	double foodLevel;

	bool freezed = false;

	bool dead = false;

	Genes genes;

	Ranged<double, 0, 100> horniness;

	std::string name;

	sf::Color makedFoodColor;

	std::shared_ptr<std::vector<std::shared_ptr<BaseObj>>> FoodCollisionVector = std::make_shared<std::vector<std::shared_ptr<BaseObj>>>();
	std::shared_ptr<std::vector<std::shared_ptr<Cell>>> CellCollisionVector = std::make_shared<std::vector<std::shared_ptr<Cell>>>();
	std::pair<std::shared_ptr<BaseObj>, double> closestCell; 
	std::pair<std::shared_ptr<BaseObj>, double> closestFood;
	// abbreviation used to save cell to file
	struct VarAbbrv final
	{
		//static constexpr const char *const currentRotation = "Rotation";
		//static constexpr const char *const currentPosition = "Position";
		//static constexpr const char *const color = "Color";
		//static constexpr const char *const currentAge = "Age";
		//static constexpr const char *const currentSpeed = "Speed";
		//static constexpr const char *const currentSize = "Size";
		//static constexpr const char *const isDead = "isDead";
		//static constexpr const char *const currentFoodLevel = "FoodLevel";
		//static constexpr const char *const isFreezed = "isFreezed";
		//static constexpr const char *const horniness = "Fertility";
		//static constexpr const char *const cellRoles = "Roles";

		//static constexpr const char *const aggression = "G_Aggression";
		//static constexpr const char *const divisionTh = "G_DivisionTh";
		//static constexpr const char *const foodLimit = "G_FoodLimit";
		//static constexpr const char *const maxAge = "G_MaxAge";
		//static constexpr const char *const maxSize = "G_MaxSize";
		//static constexpr const char *const maxSpeed = "G_MaxSpeed";
		//static constexpr const char *const radarRange = "G_RadarRg";
		//static constexpr const char *const metabolism = "G_Metabolism";

		static constexpr const char *const currentRotation = "Rt";
		static constexpr const char *const currentPosition = "Ps";
		static constexpr const char *const color = "C";
		static constexpr const char *const currentAge = "A";
		static constexpr const char *const currentSpeed = "Sp";
		static constexpr const char *const currentSize = "Si";
		static constexpr const char *const isDead = "De";
		static constexpr const char *const currentFoodLevel = "FL";
		static constexpr const char *const isFreezed = "FF";
		static constexpr const char *const horniness = "Hr";
		static constexpr const char *const cellRoles = "Rl";

		static constexpr const char *const aggression = "GAr";
		static constexpr const char *const divisionTh = "GDi";
		static constexpr const char *const foodLimit = "GFL";
		static constexpr const char *const maxAge = "GAg";
		static constexpr const char *const maxSize = "GSi";
		static constexpr const char *const maxSpeed = "GSp";
		static constexpr const char *const radarRange = "GRR";
		static constexpr const char *const metabolism = "GM";

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
