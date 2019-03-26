#pragma once
#include <SFML/Graphics.hpp>
#include "Food.h"
#include <atomic>
#include <mutex>

class AutoFeederTool
{
public:
	~AutoFeederTool();
	static AutoFeederTool& getInstance();
	void configure(int maxThresholdValue);
	void update();
	void setMaxThresholdValue(int value);
	void setMaxFoodPerSec(int value);
	void setIsActive(bool value);
	std::atomic<int>& getMaxThresholdValue();
	std::atomic<int>& getMaxFoodPerSec();
	std::atomic<bool>& getIsActive();

	
private:
	AutoFeederTool();
	AutoFeederTool(AutoFeederTool const&) = delete;
	AutoFeederTool& operator=(AutoFeederTool const&) = delete;

	sf::Clock clock;
	int spawnTime;
	sf::Time deltaTime;
	static std::mutex mutex;
	std::atomic<int> maxThresholdValue;
	std::atomic<int> maxFoodPerSec;
	std::atomic<bool> isActive;
};

