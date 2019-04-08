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

	void clear();

	void update();

	void configure();

	void draw(sf::RenderWindow & window);

	std::atomic<double>& getTemperature();
	void setTemperature(const double&);

	std::atomic<double>& getRadiation();
	void setRadiation(const double&);

	sf::Vector2f getSize();

	int getAliveCellsCount();
	int getFoodCount();


	std::shared_ptr<Cell> getCellAtPosition(const sf::Vector2f&);

	const std::list<std::shared_ptr<Food>>& getFoodsVector();
	std::vector<std::shared_ptr<Cell>>& getCellsVector();
	std::vector<std::shared_ptr<Cell>>& getNewCellsVector();
	std::list<std::shared_ptr<Food>>& getNewFoodsVector();
	baseObjMatrix& getCellCollisionSectors();
	baseObjMatrix& getFoodCollisionSectors();

	// inserts new cell to environment
	void insertNewCell(std::shared_ptr<Cell>);

	// inserts new food to environment
	void insertNewFood(std::shared_ptr<Food>);

	static sf::Vector2i getCollisionSectorCoords(std::shared_ptr<BaseObj> o);

private:
	Environment();
	Environment(Environment const&) = delete;
	Environment& operator=(Environment const&) = delete;

	void updateBackground();

	std::vector<std::shared_ptr<Cell>> cells;
	std::vector<std::shared_ptr<Cell>> deadCells;
	std::vector<std::shared_ptr<Cell>> newCells;
	std::list<std::shared_ptr<Food>> food;
	std::list<std::shared_ptr<Food>> newFood;

	baseObjMatrix cellCollisionSectors;
	baseObjMatrix foodCollisionSectors;

	sf::RectangleShape environmentBackground;

	std::atomic<double> _temperature;
	std::atomic<double> _radiation;
	std::atomic<int> _aliveCellsCount;
	std::atomic<int> _foodCount;

	sf::Color backgroundDefaultColor;

	bool isCellInEnvironmentBounds(Cell& c);


	static constexpr int sectorSize = 50 * 2 + 30; //cell max radius + margin
};