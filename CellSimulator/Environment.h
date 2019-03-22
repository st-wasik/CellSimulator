#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Food.h"
#include <atomic>

class Environment final
{
public:
	~Environment();

	static Environment& getInstance();


	void clear();

	void update();

	void draw(sf::RenderWindow & window);

	std::atomic<double>& getTemperature();
	void setTemperature(const double&);

	std::atomic<double>& getRadiation();
	void setRadiation(const double&);

	sf::Vector2f getSize();

	int getAliveCellsCount();
	int getFoodCount();


	std::shared_ptr<Cell> getCellAtPosition(const sf::Vector2f&);

	std::vector<std::shared_ptr<Food>>& getFoodsVector();
	std::vector<std::shared_ptr<Cell>>& getCellsVector();

private:
	Environment();
	Environment(Environment const&) = delete;
	void operator=(Environment const&) = delete;

	void configure();

	void updateBackground();


	std::vector<std::shared_ptr<Cell>> cells;
	std::vector<std::shared_ptr<int>/*Substance*/> substances;
	std::vector<std::shared_ptr<Food>> food;


	sf::RectangleShape environmentBackground;
	sf::RectangleShape temperatureBackground;

	std::atomic<double> _temperature;
	std::atomic<double> _radiation;
	std::atomic<int> _aliveCellsCount;
	std::atomic<int> _foodCount;

	sf::Color backgroundDefaultColor;

	bool isCellInEnvironmentBounds(Cell& c);
};