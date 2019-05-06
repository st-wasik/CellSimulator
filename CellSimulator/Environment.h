#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Food.h"
#include <atomic>
#include <list>

using baseObjMatrix = std::vector<std::vector< std::vector<std::shared_ptr<BaseObj> >>>;

class Environment final
{
public:
	~Environment();
	static Environment& getInstance();
	static sf::Vector2i getCollisionSectorCoords(std::shared_ptr<BaseObj> o);

	void configure(sf::Vector2f envSize = {2000,1000}, bool fill = false);
	void configure(std::string formattedEnvString);
	void clear();
	void update();
	void draw(sf::RenderWindow & window);

	void pauseSimulation();
	void startSimualtion();
	std::atomic_bool& getIsSimulationActive();

	std::atomic<double>& getTemperature();
	void setTemperature(const double&);

	std::atomic<double>& getRadiation();
	void setRadiation(const double&);

	sf::Vector2f getSize();
	int getAliveCellsCount();
	int getFoodCount();

	std::shared_ptr<Cell> getCellAtPosition(const sf::Vector2f&);

	const std::vector<std::shared_ptr<Food>>& getFoodsVector();
	std::vector<std::shared_ptr<Cell>>& getCellsVector();
	std::vector<std::shared_ptr<Cell>>& getNewCellsVector();
	const std::vector<std::shared_ptr<Food>>& getNewFoodsVector();

	baseObjMatrix& getCellCollisionSectors();
	baseObjMatrix& getFoodCollisionSectors();

	// inserts new cell to environment
	void insertNewCell(std::shared_ptr<Cell>);

	// inserts new food to environment
	void insertNewFood(std::shared_ptr<Food>);

	// returns string that can be used to save whole environment to file 
	std::string getSaveString();

	bool isObjInEnvironmentBounds(BaseObj::Ptr o, float expectedSize = 0);

	void modifyValueFromString(std::string valueName, std::string value);
	void modifyValueFromVector(std::string valueName, const std::vector<std::string>& value);
private:
	// used to determine collision sector size
	// value = cell max radius*2 (diameter) + margin
	static constexpr int sectorSize = 50 * 2 + 30; 

	Environment();
	Environment(Environment const&) = delete;
	Environment& operator=(Environment const&) = delete;

	void updateBackground();
	void sterilizeEnvironment();

	std::vector<std::shared_ptr<Cell>> cells;
	std::vector<std::shared_ptr<Cell>> deadCells;
	std::vector<std::shared_ptr<Cell>> newCells;
	std::vector<std::shared_ptr<Food>> food;
	std::vector<std::shared_ptr<Food>> newFood;
	baseObjMatrix cellCollisionSectors;
	baseObjMatrix foodCollisionSectors;

	sf::RectangleShape environmentBackground;
	sf::Color backgroundDefaultColor;

	std::atomic<double> _temperature;
	std::atomic<double> _radiation;
	std::atomic<int> _aliveCellsCount;
	std::atomic<int> _foodCount;
	std::atomic_bool _clearEnvironment;
	std::atomic_bool _simulationActive;

	struct VarAbbrv final
	{
		static constexpr const char *const temperature = "Temperature";
		static constexpr const char *const radiation = "Radiation";
		static constexpr const char *const isSimualtionActive = "isSimulationActive";
		static constexpr const char *const envSize = "EnvSize";

	private:
		VarAbbrv() = delete;
		VarAbbrv(const VarAbbrv&) = delete;
		VarAbbrv& operator=(const VarAbbrv&) = delete;
		virtual ~VarAbbrv() = 0;
	};
};