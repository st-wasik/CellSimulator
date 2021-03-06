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
		Passive, Aggressive, Random, GreenLettuce, Pizza, Default, Speed
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
	void setGenes(Genes g);

	double getFoodLevel();
	double getCurrentSpeed();

	void setCurrentSpeed(double speed);
	void setFoodLevel(double foodLevel);
	void setAge(double age);
	void setHorniness(double horniness);
	DynamicRanged<double>& getHorniness();

	void dropRole(void(*role)(Cell*));
	void dropRoles();
	void addRole(void(*role)(Cell*));

	double age;
	float delayTime;

	// returns string with cell description that can be used to save cell from environment to file (contains current stats, position etc.)
	std::string getSaveString();

	// returns string with cell description that can be used to save cell created in workshop (without stats, position, etc.)
	std::string getCellBlueprintString();

	std::string getName();
	void setName(std::string n);

	void setMakedFoodColor(sf::Color c);
	sf::Color getMakedFoodColor();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setPosition(const sf::Vector2f&);

	void setSize(const float&);

	void setRotation(const float & r);
	void rotate(const float & r);

	sf::CircleShape& getTypeShape();

	std::shared_ptr<BaseObj> getClosestCell();
	std::shared_ptr<BaseObj> getClosestFood();

private:
	explicit Cell();
	Cell(float size, sf::Vector2f position, sf::Color color);
	Cell(Cell a, Cell b);
	Cell(std::string formattedCellString);

	void modifyValueFromString(std::string valueName, std::string value);
	void modifyValueFromVector(std::string valueName, const std::vector<std::string>& value);

	// vector of pointers to role-functions
	std::vector<void(*)(Cell*)> roles;

	void calcFoodCollisionVector();
	void calcCellCollisionVector();
	// curent cell stats:

	double currentSpeed;

	double foodLevel;

	bool freezed = false;

	bool dead = false;

	Genes genes;

	DynamicRanged<double> horniness; // <0,100>

	std::string name;

	sf::Color makedFoodColor;

	sf::CircleShape typeShape;

	std::shared_ptr<std::vector<std::shared_ptr<BaseObj>>> FoodCollisionVector = std::make_shared<std::vector<std::shared_ptr<BaseObj>>>();
	std::shared_ptr<std::vector<std::shared_ptr<Cell>>> CellCollisionVector = std::make_shared<std::vector<std::shared_ptr<Cell>>>();
	std::pair<std::shared_ptr<BaseObj>, double> closestCell;
	std::pair<std::shared_ptr<BaseObj>, double> closestFood;
	float closestCellAngle;
	float closestFoodAngle;

	// abbreviation used to save cell to file
	struct VarAbbrv final
	{
		static constexpr const char *const currentRotation = "Rt";
		static constexpr const char *const currentPosition = "Ps";
		static constexpr const char *const color = "C";
		static constexpr const char *const makedFoodColor = "MFC";
		static constexpr const char *const currentAge = "A";
		static constexpr const char *const currentSpeed = "Sp";
		static constexpr const char *const currentSize = "Si";
		static constexpr const char *const isDead = "De";
		static constexpr const char *const currentFoodLevel = "FL";
		static constexpr const char *const isFreezed = "FF";
		static constexpr const char *const horniness = "Hr";
		static constexpr const char *const cellRoles = "Rl";
		static constexpr const char *const name = "Na";

		static constexpr const char *const aggression = "GAr";
		static constexpr const char *const divisionTh = "GDi";
		static constexpr const char *const foodLimit = "GFL";
		static constexpr const char *const maxAge = "GAg";
		static constexpr const char *const maxSize = "GSi";
		static constexpr const char *const maxSpeed = "GSp";
		static constexpr const char *const radarRange = "GRR";
		static constexpr const char *const metabolism = "GM";
		static constexpr const char *const type = "Tp";
		static constexpr const char *const turningRate = "TR";

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
