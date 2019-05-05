#include "FoodManager.h"
#include "Random.h"
#include "Environment.h"



FoodManager::FoodManager()
{
}


FoodManager::~FoodManager()
{
}

FoodManager & FoodManager::getInstance()
{
	static FoodManager instance;
	return instance;
}

void FoodManager::generateFood(sf::Vector2f size, int amount)
{
	for (int i = 0; i < amount; i++) {
		auto food = Food::create(
			0,
			sf::Vector2f(randomInt(40, static_cast<int>(Environment::getInstance().getSize().x - 40)), randomInt(40, static_cast<int>(Environment::getInstance().getSize().y - 40))),
			sf::Color(0, randomInt(128, 255), randomInt(0, 64)),
			randomInt(size.x, size.y));

		Environment::getInstance().insertNewFood(food);
	}
}
