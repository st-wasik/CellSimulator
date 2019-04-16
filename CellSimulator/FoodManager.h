#pragma once
#include <SFML/Graphics.hpp>
class FoodManager
{
public:
	~FoodManager();
	static FoodManager& getInstance();
	static void generateFood(sf::Vector2f size, int amount);

private:
	FoodManager();
	FoodManager(FoodManager const&) = delete;
	FoodManager& operator=(FoodManager const&) = delete;
};

