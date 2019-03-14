#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"

class Environment final
{
public:
	Environment() = delete;

	static void clear();

	static void configure();

	static void update();

	static void draw(sf::RenderWindow & window);

	static double getTemperature();
	static void setTemperature(const double&);

	static double getRadiation();
	static void setRadiation(const double&);

	static sf::Vector2f getSize();

	static unsigned int getAliveCellsCount();

private:
	static std::vector<Cell> cells;

	static std::vector<int/*Substance*/> substances;

	static sf::RectangleShape environmentBackground;

	static double _temperature;

	static double _radiation;
};