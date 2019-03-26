#pragma once
#include <SFML/Graphics.hpp>
#include "Food.h"

class AutoFeederTool
{
public:
	~AutoFeederTool();
	static AutoFeederTool& getInstance();
	void configure(int maxThresholdValue);
	void update();
private:
	AutoFeederTool();
	AutoFeederTool(AutoFeederTool const&) = delete;
	AutoFeederTool& operator=(AutoFeederTool const&) = delete;

	sf::Clock clock;
	int maxThresholdValue;
	int maxFoodPerSec;
	int currentFoodInSecondCount;
	int spawnTime;
	sf::Time deltaTime;
};

