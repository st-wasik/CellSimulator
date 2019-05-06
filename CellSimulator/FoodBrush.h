#pragma once
#include <SFML/Graphics.hpp>
class FoodBrush
{
public:
	static FoodBrush& getInstance();

	void update();

	void draw(sf::RenderWindow& w);

	void setIsActive(bool a);
	bool getIsActive();

	void setBrushDelay(int delay);
	int getBrushDelay();

	void setHardness(double hardness);
	double getHardness();

	void setBrushRadius(float size);
	float getBrushRadius();

	FoodBrush();
	~FoodBrush();

private:
	bool isActive;
	int delay;
	int elapsedTime;
	double hardness;
	sf::CircleShape brush;
};

