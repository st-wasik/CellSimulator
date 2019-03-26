#include "AutoFeederTool.h"
#include "Environment.h"
#include "FoodController.h"
#include <iostream>

std::mutex AutoFeederTool::mutex;

AutoFeederTool::~AutoFeederTool()
{
}

AutoFeederTool::AutoFeederTool() {
	maxThresholdValue = 50;
	maxFoodPerSec = 5;
	spawnTime = 1000 / maxFoodPerSec;
	isActive = false;
	clock.restart();
}

AutoFeederTool & AutoFeederTool::getInstance()
{
	std::lock_guard<std::mutex> lock(mutex);
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
	if (foodVector.size() < maxThresholdValue && deltaTime > spawnTime && isActive) {
		FoodController::getInstance().generateFood(sf::Vector2f(3,12), deltaTime/spawnTime);
		clock.restart();
	}
	else if (deltaTime > spawnTime) {
		clock.restart();
	}
}

void AutoFeederTool::setMaxThresholdValue(int value)
{
	this->maxThresholdValue = value;
}

void AutoFeederTool::setMaxFoodPerSec(int value)
{
	this->maxFoodPerSec = value;
	if (value != 0) {
		spawnTime = 1000 / maxFoodPerSec;
	}
}

void AutoFeederTool::setIsActive(bool value)
{
	this->isActive = value;
}

std::atomic<int>& AutoFeederTool::getMaxThresholdValue()
{
	return this->maxThresholdValue;
}

std::atomic<int>& AutoFeederTool::getMaxFoodPerSec()
{
	return this->maxFoodPerSec;
}

std::atomic<bool>& AutoFeederTool::getIsActive()
{
	return this->isActive;
}
