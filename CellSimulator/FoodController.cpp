#include "FoodController.h"
#include "Random.h"
#include "Environment.h"



FoodController::FoodController()
{
}


FoodController::~FoodController()
{
}

FoodController & FoodController::getInstance()
{
	static FoodController instance;
	return instance;
}

void FoodController::generateFood(sf::Vector2f size, int amount)
{
	for (int i = 0; i < amount; i++) {
		auto food = Food::create(
			randomInt(size.x, size.y),
			sf::Vector2f(randomInt(40, static_cast<int>(Environment::getInstance().getSize().x - 40)), randomInt(40, static_cast<int>(Environment::getInstance().getSize().y - 40))),
			sf::Color(0, randomInt(128, 255), randomInt(0, 64)));

		Environment::getInstance().insertNewFood(food);
	}
}
