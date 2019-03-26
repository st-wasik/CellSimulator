#include "AutoFeederTool.h"
#include "Environment.h"
#include "FoodController.h"
#include <iostream>



AutoFeederTool::~AutoFeederTool()
{
}

AutoFeederTool::AutoFeederTool() {
	maxThresholdValue = 50;
	maxFoodPerSec = 5;
	currentFoodInSecondCount = 0;
	spawnTime = 1000 / maxFoodPerSec;
	clock.restart();
}

AutoFeederTool & AutoFeederTool::getInstance()
{
	static AutoFeederTool instance;
	return instance;
}

void AutoFeederTool::configure(int maxThresholdValue)
{
	this->maxThresholdValue = maxThresholdValue;
}

void AutoFeederTool::update()
{
	auto& foodVector = Environment::getInstance().getFoodsVector();
	int deltaTime = clock.getElapsedTime().asMilliseconds();
	if (foodVector.size() < maxThresholdValue && deltaTime > spawnTime) {
		FoodController::getInstance().generateFood(sf::Vector2f(3,12), deltaTime/spawnTime);
		clock.restart();
	}
}
