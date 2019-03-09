#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Environment final
{
public:
	Environment() = delete;

	static double temperature;

	static double radiation;

	static void clear();

	static void configure();

	static void update();

	static void draw(sf::RenderWindow& window);

private:
	static std::vector<int/*Cell*/> cells;

	static std::vector<int/*Substance*/> substances;

	static sf::RectangleShape environmentBackground;

};