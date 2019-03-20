#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Food.h"
#include <atomic>

class Environment final
{
public:
	Environment() = delete;

	static void clear();

	static void configure();

	static void update();

	static void draw(sf::RenderWindow & window);

	static std::atomic<double>& getTemperature();
	static void setTemperature(const double&);

	static std::atomic<double>& getRadiation();
	static void setRadiation(const double&);

	static sf::Vector2f getSize();

	static unsigned int getAliveCellsCount();

	std::shared_ptr<Cell> getCellAtPosition(const sf::Vector2f&);

private:
	static std::vector<std::shared_ptr<Cell>> cells;

	static std::vector<std::shared_ptr<int>/*Substance*/> substances;

	static std::vector<std::shared_ptr<Food>> food;

	static sf::RectangleShape environmentBackground;
	static sf::RectangleShape temperatureBackground;

	static std::atomic<double> _temperature;

	static std::atomic<double> _radiation;

	static bool isCellInEnvironmentBounds(Cell& c);

	//static sf::Texture backgroundImage;
};