#include "CellFactory.h"

std::shared_ptr<Cell> CellFactory::getCell(Cell::Type type)
{
	std::shared_ptr<Cell> result = std::make_shared<Cell>(Cell(20.f, {0.f, 0.f}, sf::Color::Transparent));
	Genes g;

	switch (type)
	{
	case Cell::Type::Aggressive:
		result->genes.aggresion = 90;
		result->genes.divisionThreshold = 30;
		result->genes.foodLimit = 120;
		result->genes.maxAge = 90;
		result->genes.maxSize = 35;
		result->genes.maxSpeed = 2;
		result->genes.radarRange = 7;
		break;

	case Cell::Type::Passive:
		result->genes.aggresion = 10;
		result->genes.divisionThreshold = 25;
		result->genes.foodLimit = 90;
		result->genes.maxAge = 95;
		result->genes.maxSize = 45;
		result->genes.maxSpeed = 1;
		result->genes.radarRange = 4;
		break;

	case Cell::Type::Random:
		g.randomize();
		result->genes = g;
		break;

	case Cell::Type::GreenLettuce:
		result->genes.aggresion = 0;
		result->genes.divisionThreshold = 45;
		result->genes.foodLimit = 150;
		result->genes.maxAge = 100;
		result->genes.maxSize = 25;
		result->genes.maxSpeed = 0.75;
		result->genes.radarRange = 0;
		break;
	}

	return result;
}
