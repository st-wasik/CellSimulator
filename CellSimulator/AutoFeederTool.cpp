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
	AutoFeederTool instance;
	return instance;
}

void AutoFeederTool::configure(int maxThresholdValue)
{
	this->maxThresholdValue = maxThresholdValue;
}

void AutoFeederTool::update()
{
	//std::cout << clock.getElapsedTime().asMilliseconds() << "\t";
	//clock.restart();
	//std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;
	auto& foodVector = Environment::getInstance().getFoodsVector();

	if (foodVector.size() < maxThresholdValue) {
		FoodController::getInstance().generateFood(sf::Vector2f(3,12), 1);
		currentFoodInSecondCount++;
	}
	/*if (clock.getElapsedTime().asSeconds() >= 10) {
		currentFoodInSecondCount = 0;
		clock.restart();
	}*/
	
}
