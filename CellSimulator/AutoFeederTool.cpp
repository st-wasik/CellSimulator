#include "AutoFeederTool.h"
#include "Environment.h"
#include "FoodController.h"
#include <iostream>



AutoFeederTool::~AutoFeederTool()
{
}

AutoFeederTool::AutoFeederTool() {
	maxThresholdValue = 50;
	maxFoodPerSec = 2;
	currentFoodInSecondCount = 0;
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

	if (foodVector.size() < maxThresholdValue && currentFoodInSecondCount < maxFoodPerSec) {
		FoodController::getInstance().generateFood(sf::Vector2f(3,12), 1);
		currentFoodInSecondCount++;
	}
	if (clock.getElapsedTime().asSeconds() >= 1) {
		currentFoodInSecondCount = 0;
		clock.restart();
	}
	
}
