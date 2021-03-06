#include "CellFactory.h"
#include "CellRoles.h"
#include "TextureProvider.h"

std::shared_ptr<Cell> CellFactory::getCell(Cell::Type type)
{
	std::shared_ptr<Cell> result = Cell::create(20.f, sf::Vector2f{ 0.f, 0.f }, sf::Color::Transparent);

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
		result->genes.radarRange = 350;
		result->genes.type = 2;
		result->setFoodLevel(60);
		result->setBaseColor(sf::Color::Red);
		CellRoles::updateColor(result.get());
		break;

	case Cell::Type::Passive:
		result->genes.aggresion = 10;
		result->genes.divisionThreshold = 25;
		result->genes.foodLimit = 90;
		result->genes.maxAge = 95;
		result->genes.maxSize = 45;
		result->genes.maxSpeed = 1;
		result->genes.radarRange = 200;
		result->genes.type = 1;
		result->setFoodLevel(60);
		result->setBaseColor(sf::Color::Blue);
		CellRoles::updateColor(result.get());
		break;

	case Cell::Type::Speed:
		result->genes.aggresion = 50;
		result->genes.divisionThreshold = 90;
		result->genes.foodLimit = 150;
		result->genes.maxAge = 85;
		result->genes.maxSize = 35;
		result->genes.maxSpeed = 2;
		result->genes.radarRange = 300;
		result->genes.type = 0;
		result->setFoodLevel(60);
		result->setBaseColor(sf::Color::Yellow);
		CellRoles::updateColor(result.get());
		break;

	case Cell::Type::Random:
		g.randomize();
		result->genes = g;
		result->setBaseColor(sf::Color::Yellow);
		CellRoles::updateColor(result.get());
		break;

	case Cell::Type::GreenLettuce:
		result->genes.aggresion = 0;
		result->genes.divisionThreshold = 45;
		result->genes.foodLimit = 100;
		result->genes.maxAge = 10;
		result->genes.maxSize = 25;
		result->genes.maxSpeed = 0.75;
		result->genes.radarRange = 0;
		result->genes.turningRate = 0.5;
		result->genes.metabolism = 0.5;
		result->genes.type = -1;
		result->dropRole(CellRoles::eat);
		result->dropRole(CellRoles::simulateHunger);
		result->dropRole(CellRoles::mutate);
		result->dropRole(CellRoles::makeOlder);
		result->dropRole(CellRoles::grow);
		result->dropRole(CellRoles::divideAndConquer);
		result->dropRole(CellRoles::getingHot);
		result->dropRole(CellRoles::sniffForFood);
		result->dropRole(CellRoles::fight);
		result->dropRole(CellRoles::updateColor);
		result->addRole(CellRoles::makeFood);
		result->setBaseColor(sf::Color::White);
		result->setMakedFoodColor(sf::Color(8, 128, 8));
		result->shape.setTextureRect(sf::IntRect{ 0,0,960,960 });
		result->shape.setTexture(TextureProvider::getInstance().getTexture("greenLettuce").get());
		result->typeShape.setFillColor(sf::Color::Transparent);
		break;

	case Cell::Type::Pizza:
		result->genes.aggresion = 0;
		result->genes.divisionThreshold = 45;
		result->genes.foodLimit = 150;
		result->genes.maxAge = 10;
		result->genes.maxSize = 45;
		result->genes.maxSpeed = 0.5;
		result->genes.radarRange = 0;
		result->genes.metabolism = 0.2;
		result->genes.turningRate = 0.5;
		result->genes.type = -1;
		result->dropRole(CellRoles::eat);
		result->dropRole(CellRoles::simulateHunger);
		result->dropRole(CellRoles::mutate);
		result->dropRole(CellRoles::makeOlder);
		result->dropRole(CellRoles::grow);
		result->dropRole(CellRoles::divideAndConquer);
		result->dropRole(CellRoles::getingHot);
		result->dropRole(CellRoles::sniffForFood);
		result->dropRole(CellRoles::fight);
		result->dropRole(CellRoles::updateColor);
		result->addRole(CellRoles::makeFood);
		result->setBaseColor(sf::Color::White);
		result->setMakedFoodColor(sf::Color(224, 144, 33, 255));
		result->shape.setTextureRect(sf::IntRect{ 0,0,1052,1052 });
		result->shape.setTexture(TextureProvider::getInstance().getTexture("pizza").get());
		result->typeShape.setFillColor(sf::Color::Transparent);
		result->setSize(45);
		break;
	case Cell::Type::Default:
		result->genes.aggresion = 50;
		result->genes.divisionThreshold = 50;
		result->genes.foodLimit = 75;
		result->genes.maxAge = 50;
		result->genes.maxSize = 35;
		result->genes.maxSpeed = 1.0;
		result->genes.radarRange = 250;
		result->genes.metabolism = 1.0;
		result->genes.type = 0;
		result->genes.turningRate = 3.25;
		result->setBaseColor(sf::Color::White);
		result->setFoodLevel(60);
		result->setSize(20);
		break;
	}

	return result;
}

std::shared_ptr<Cell> CellFactory::getCell(std::string formattedCellString)
{
	return Cell::create(formattedCellString);
}
