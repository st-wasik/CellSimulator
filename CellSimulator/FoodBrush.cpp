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
		if (CellSimMouse::isLeftPressed() && deltaTimeClock.getElapsedTime().asMilliseconds() > delay)
		{
			deltaTimeClock.restart();
			float radius = brush.getRadius();
			sf::Vector2f position(CellSimMouse::getPosition().x + randomInt(-radius*0.7, radius*0.7), CellSimMouse::getPosition().y + randomInt(-radius*0.7, radius*0.7));
			auto food = Food::create(0, position, sf::Color::Green, randomInt(3, 10));
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

void FoodBrush::setBrushDelay(int delay)
{
	this->delay = delay;
}

int FoodBrush::getBrushDelay()
{
	return this->delay;
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
	brush.setOutlineColor(sf::Color(255,255,255,128));
	brush.setRadius(50.f);
	brush.setOutlineThickness(4.f);
	brush.setOrigin(brush.getRadius(), brush.getRadius());
	isActive = false;
	deltaTimeClock.restart();
	delay = 25;
}


FoodBrush::~FoodBrush()
{
}
