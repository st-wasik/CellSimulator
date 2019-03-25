#pragma once
#include <SFML/Graphics.hpp>
class FoodController
{
public:
	~FoodController();
	static FoodController& getInstance();
	static void generateFood(sf::Vector2f size, int amount);

private:
	FoodController();
	FoodController(FoodController const&) = delete;
	FoodController& operator=(FoodController const&) = delete;
};

