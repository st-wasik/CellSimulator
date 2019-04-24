#include "FoodBrush.h"
#include "CellSimMouse.h"
#include "MessagesManager.h"
#include "Environment.h"
#include "Food.h"



FoodBrush & FoodBrush::getInstance()
{
	static FoodBrush instance;
	return instance;
}

void FoodBrush::update()
{
	if (isActive) 
	{
		brush.setPosition(CellSimMouse::getPosition());
		if (CellSimMouse::wasLeftPressed())
		{
			auto food = Food::create(randomInt(3,10), CellSimMouse::getPosition(),sf::Color::Green);
			Environment::getInstance().insertNewFood(food);
		}
	}
}

void FoodBrush::draw(sf::RenderWindow& w)
{
	if (isActive)
	{
		w.draw(brush);
	}
}

void FoodBrush::setIsActive(bool a)
{
	isActive = a;
}

bool FoodBrush::getIsActive()
{
	return isActive;
}

void FoodBrush::setBrushRadius(float radius)
{
	if (radius > 10.f)
	{
		brush.setRadius(radius);
		brush.setOrigin(radius, radius);
	}
	else 
	{
		MessagesManager::getInstance().append("Brush radius cannot be smaller than 10.0!");
	}
}

float FoodBrush::getBrushRadius()
{
	return brush.getRadius();
}

FoodBrush::FoodBrush()
{
	brush.setFillColor(sf::Color::Transparent);
	brush.setOutlineColor(sf::Color::White);
	brush.setRadius(50.f);
	brush.setOutlineThickness(4.f);
	brush.setOrigin(brush.getRadius(), brush.getRadius());
	isActive = false;
}


FoodBrush::~FoodBrush()
{
}
