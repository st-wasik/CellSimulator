#include "FoodBrush.h"
#include "CellSimMouse.h"
#include "MessagesManager.h"
#include "Environment.h"
#include "Food.h"
#include "CellSimApp.h"

#define PI 3.14159265

FoodBrush & FoodBrush::getInstance()
{
	static FoodBrush instance;
	return instance;
}

void FoodBrush::update()
{
	if (isActive)
	{
		elapsedTime += CellSimApp::getInstance().getDeltaTime();
		brush.setPosition(CellSimMouse::getPosition());
		if (CellSimMouse::isLeftPressed() && elapsedTime > delay)
		{
			elapsedTime = 0;
			float radius = brush.getRadius();
			Logger::log((CellSimApp::getInstance().getDeltaTime() * 3.14 * (radius / 2)) * 0.002 * hardness);
			for (int i = 0; i < (CellSimApp::getInstance().getDeltaTime() * 3.14 * (radius / 2)) * 0.002 * hardness; i++)
			{
				double angle = randomReal(0, 360);
				std::shared_ptr<Food> food;
				sf::Vector2f position(CellSimMouse::getPosition().x + randomReal(-radius * std::cos(angle * PI / 180), radius * std::cos(angle * PI / 180)), CellSimMouse::getPosition().y + randomReal(-radius * std::sin(angle * PI / 180), radius * std::sin(angle * PI / 180)));
				food = Food::create(2, position, sf::Color(0, randomInt(128, 255), randomInt(0, 64)), randomInt(3, 10));
				if (Environment::getInstance().isObjInEnvironmentBounds(food, food->getMaxSize()))
				{
					Environment::getInstance().insertNewFood(food);
				}
			}
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

void FoodBrush::setHardness(double hardness)
{
	this->hardness = hardness;
}

double FoodBrush::getHardness()
{
	return this->hardness;
}

void FoodBrush::setBrushRadius(float radius)
{
	if (radius >= 10.f)
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
	brush.setOutlineColor(sf::Color(255, 255, 255, 128));
	brush.setRadius(50.f);
	brush.setOutlineThickness(4.f);
	brush.setOrigin(brush.getRadius(), brush.getRadius());
	isActive = false;
	elapsedTime = 0;
	hardness = 2;
	delay = 1;
}


FoodBrush::~FoodBrush()
{
}
