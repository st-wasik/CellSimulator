#include "Environment.h"

std::vector<int/*Cell*/> Environment::cells;

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
}

void Environment::update()
{
	for (auto & cell : cells)
	{
		//cell.update();
	}

	for (auto & subst : substances)
	{
		//subst.update();
	}
}

void Environment::draw(sf::RenderWindow & window)
{
	window.draw(environmentBackground);
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
