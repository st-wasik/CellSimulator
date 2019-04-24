#include "CellFactory.h"
#include "CellRoles.h"
#include "TextureProvider.h"

std::shared_ptr<Cell> CellFactory::getCell(Cell::Type type)
{
	std::shared_ptr<Cell> result = Cell::create(20.f, sf::Vector2f{0.f, 0.f}, sf::Color::Red);

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
		result->setBaseColor(sf::Color::Red);
		break;

	case Cell::Type::Passive:
		result->genes.aggresion = 10;
		result->genes.divisionThreshold = 25;
		result->genes.foodLimit = 90;
		result->genes.maxAge = 95;
		result->genes.maxSize = 45;
		result->genes.maxSpeed = 1;
		result->genes.radarRange = 4;
		result->setBaseColor(sf::Color::Blue);
		break;

	case Cell::Type::Random:
		g.randomize();
		result->genes = g;
		result->setBaseColor(sf::Color::Yellow);
		break;

	case Cell::Type::GreenLettuce:
		result->genes.aggresion = 0;
		result->genes.divisionThreshold = 45;
		result->genes.foodLimit = 0;
		result->genes.maxAge = 10;
		result->genes.maxSize = 25;
		result->genes.maxSpeed = 0.75;
		result->genes.radarRange = 0;
		result->setBaseColor(sf::Color::Green);
		result->dropRole(CellRoles::eat);
		result->dropRole(CellRoles::simulateHunger);
		result->dropRole(CellRoles::mutate);
		result->dropRole(CellRoles::makeOlder);
		result->dropRole(CellRoles::grow);
		result->dropRole(CellRoles::divideAndConquer);
		result->dropRole(CellRoles::getingHot);
		result->dropRole(CellRoles::sniffForFood);
		result->addRole(CellRoles::makeFood);
		result->setBaseColor(sf::Color::White);
		result->shape.setTextureRect(sf::IntRect{ 0,0,960,960 });
		result->shape.setTexture(TextureProvider::getInstance().getTexture("greenLettuce").get());
		break;
	}

	return result;
}

std::shared_ptr<Cell> CellFactory::getCell(std::string formattedCellString)
{
	return Cell::create(formattedCellString);
}
