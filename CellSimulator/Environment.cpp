#include "Environment.h"
#include <random>

std::vector<Cell> Environment::cells;

std::vector<int/*Substance*/> Environment::substances;

sf::RectangleShape Environment::environmentBackground;

double Environment::temperature;

double Environment::radiation;

void Environment::clear()
{
	cells.clear();
	substances.clear();
}

void Environment::configure()
{
	auto& eb = environmentBackground;
	eb.setSize(sf::Vector2f{ 1000,1000 });
	eb.setFillColor(sf::Color{ 170, 135, 200 });
	eb.setOutlineColor(sf::Color::Red);
	eb.setOutlineThickness(5);
	eb.setPosition(sf::Vector2f{ 0,0 });

	//To be positioned elsewhere in future
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distW(0, 800-40);
	std::uniform_int_distribution<std::mt19937::result_type> distH(0, 600-40);

	for (int i = 0; i < 20; i++) {
		cells.push_back(Cell(20, sf::Vector2f(distW(rng), distH(rng))));
	}
}

void Environment::update()
{
	for (auto & cell : cells)
	{
		cell.update();
	}

	for (auto & subst : substances)
	{
		//subst.update();
	}
}

void Environment::draw(sf::RenderWindow & window)
{
	window.draw(environmentBackground);
	for (auto & cell : cells) {
		window.draw(cell);
	}
}

double Environment::getTemperature()
{
	return temperature;
}

void Environment::setTemperature(const double & t)
{
	temperature = t;
}

double Environment::getRadiation()
{
	return radiation;
}

void Environment::setRadiation(const double & r)
{
	radiation = r;
}
