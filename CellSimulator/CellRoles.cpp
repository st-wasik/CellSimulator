#include "CellRoles.h"
#include "Random.h"
#include "Environment.h"
#include "Logger.h"
#include "CellSimApp.h"

constexpr double PI = 3.14159265358979323846;

void CellRoles::moveForward(Cell * c)
{
	const auto prevPosition = c->getPosition();
	auto moveSpeed = (Environment::getInstance().getTemperature() + 100) / 100 * c->currentSpeed;
	c->shape.move(moveSpeed * std::sin((PI / 180)*c->getRotation()) * CellSimApp::getDeltaTime(), moveSpeed * -std::cos((PI / 180)*c->getRotation()) * CellSimApp::getDeltaTime());

	for (int attempt = 0; checkEnvironmentBounds(c); ++attempt)
	{
		c->shape.setPosition(prevPosition);
		c->shape.setRotation(c->getRotation() + 90);
		c->shape.move(moveSpeed * std::sin((PI / 180)*c->getRotation()) * CellSimApp::getDeltaTime(), moveSpeed * -std::cos((PI / 180)*c->getRotation()) * CellSimApp::getDeltaTime());

		if (attempt > 5) { c->setPosition(Environment::getInstance().getSize() / 2.f); break; }
	}
}

void CellRoles::changeDirection(Cell * c)
{
	// DIRECTION CHANGE THRESHOLD SHOULD BE STORED IN GENES
	if (randomInt(0, 100) > 97)
		if (randomInt(0, 100) <= 50)
		{
			c->shape.rotate(randomReal(-50, 0));
		}
		else
		{
			c->shape.rotate(randomReal(0, 50));
		}
}

void CellRoles::changeSpeed(Cell * c)
{
	// SPEED CHANGE THRESHOLD SHOULD BE STORED IN GENES
	if (randomInt(0, 1000) > 995)
		c->currentSpeed = randomReal(0.1, 2);
}

void CellRoles::eat(Cell * c)
{
	std::vector<std::shared_ptr<Food>> foods = Environment::getInstance().getFoodsVector();

	for (auto& f : foods)
	{
		if (c->collision(f) && !f->toDelete)
		{
			c->foodLevel += static_cast<int>(f->getSize());

			// ONLY FOR TEST - DELETE LATER
			c->setSize(c->getSize() + 1);
			f->toDelete = true;
		}
	}
}

void CellRoles::updateColor(Cell * c)
{
	static double threshold = 30;

	int newR, newG, newB;

	auto newColor = c->baseColor;

	//temperature
	auto& envTemp = Environment::getInstance().getTemperature();
	auto& envRad = Environment::getInstance().getRadiation();
	if (envTemp > threshold)
	{
		newR = 2 * abs(envTemp - threshold) + c->baseColor.r;
		if (newR > 255) newR = 255;
		newColor.r = newR;
	}
	else if (envTemp < -threshold)
	{
		newB = 2 * abs(envTemp + threshold) + c->baseColor.b;
		if (newB > 255) newB = 255;
		newColor.b = newB;
	}

	//radiation
	if (envRad > threshold)
	{
		newG = 3 * abs(envRad - threshold) + c->baseColor.g;
		if (newG > 255) newG = 255;
		newColor.g = newG;
	}

	c->shape.setFillColor(newColor);
}

void CellRoles::beDead(Cell * c)
{
	auto color = c->shape.getFillColor();
	if (color.a > 0)
	{
		double a = static_cast<double>(color.a) - 0.075*CellSimApp::getDeltaTime();
		if (0 > a) a = 0;
		color.a = a;
		c->shape.setFillColor(color);
	}
	else
	{
		c->toDelete = true;
	}
}


void CellRoles::simulateHunger(Cell * c) {
	c->foodLevel -= 0.01 * CellSimApp::getDeltaTime();
}

bool CellRoles::checkEnvironmentBounds(Cell * c)
{
	const auto& envSize = Environment::getInstance().getSize();
	const auto& cellPos = c->shape.getPosition();

	// if-else structure for future improvements - return collision bound

	//check left bound
	if (c->shape.getPosition().x - c->getSize() <= 0)
	{
		return true;
	}
	//check right bound
	else if (c->shape.getPosition().x + c->getSize() >= envSize.x)
	{
		return true;
	}
	//check top bound
	else if (c->shape.getPosition().y - c->getSize() <= 0)
	{
		return true;
	}
	//check bottom bound
	else if (c->shape.getPosition().y + c->getSize() >= envSize.y)
	{
		return true;
	}

	return false;
}
