#include "CellRoles.h"
#include "Random.h"
#include "Environment.h"
#include "Logger.h"
#include "CellSimApp.h"
#include "CellSelectionTool.h"
#include "Distance.h"
constexpr double PI = 3.14159265358979323846;

void CellRoles::moveForward(Cell * c)
{
	const auto prevPosition = c->getPosition();
	auto moveSpeed = (Environment::getInstance().getTemperature() + 100) / 100 * c->currentSpeed;
	c->shape.move(moveSpeed * std::sin((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime(), moveSpeed * -std::cos((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime());

	for (int attempt = 0; checkEnvironmentBounds(c); ++attempt)
	{
		c->shape.setPosition(prevPosition);
		c->shape.setRotation(c->getRotation() + 90);
		c->shape.move(moveSpeed * std::sin((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime(), moveSpeed * -std::cos((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime());

		if (attempt > 5) { c->setPosition(Environment::getInstance().getSize() / 2.f); break; }
	}
}

void CellRoles::changeDirection(Cell * c)
{
	auto & foods = Environment::getInstance().getFoodsVector();
	std::shared_ptr<Food> closestFood=nullptr;
	double distance=1000;
	if (c->foodLevel < c->genes.foodLimit.get())
	{
		for (auto & food : foods)
		{
			if (getDistance(c->getPosition(), food->getPosition()) <= distance)
			{
				distance = getDistance(c->getPosition(), food->getPosition());
				closestFood = food;
			}
		}
	}
	if (closestFood != nullptr && distance <= c->genes.radarRange.get()*50+c->getSize())
	{
		auto v = closestFood->getPosition() - c->getPosition();
		auto angle = atan2(v.y, v.x);
		double angle_change = 5 * CellSimApp::getInstance().getDeltaTime();
		angle = angle * (180 / PI);
		if (angle < 0)
		{
			angle = 360 - (-angle);
		}
		angle += 90; //Remove this for some magic
		double cfDiffrence = c->getRotation() - angle;
		double abscfDiffrence = abs(cfDiffrence);
		if (abscfDiffrence > 180)
		{
			if (360 - abscfDiffrence < angle_change)
			{
				c->shape.rotate(cfDiffrence <= 0 ? -(360 - abscfDiffrence)*CellSimApp::getInstance().getDeltaTime() : (360 - abscfDiffrence)*CellSimApp::getInstance().getDeltaTime());
			}
			else
			{
				c->shape.rotate(cfDiffrence <= 0 ? -angle_change : angle_change);
			}
		}
		else
		{
			if (abscfDiffrence < angle_change)
			{
				c->shape.rotate(cfDiffrence >= 0 ? -abscfDiffrence * CellSimApp::getInstance().getDeltaTime() : abscfDiffrence * CellSimApp::getInstance().getDeltaTime());
			}
			else
			{
				c->shape.rotate(cfDiffrence >= 0 ? -angle_change : angle_change);
			}
		}
	}
	else if (randomInt(0, 100) > 97)
	{
		if (randomInt(0, 100) <= 50)
		{
			c->shape.rotate(randomReal(-25, 0));
		}
		else
		{
			c->shape.rotate(randomReal(0, 25));
		}
	}
}

void CellRoles::changeSpeed(Cell * c)
{
	// SPEED CHANGE THRESHOLD SHOULD BE STORED IN GENES
	if (randomInt(0, 1000) > 995)
		c->currentSpeed = randomReal(0.1, static_cast<float>(c->genes.maxSpeed.get()));
}

void CellRoles::eat(Cell * c)
{
	auto& foods = Environment::getInstance().getFoodsVector();

	for (auto& f : foods)
	{
		if (c->collision(f) && !f->isMarkedToDelete() && c->foodLevel < c->genes.foodLimit.get())
		{
			c->foodLevel += static_cast<float>(f->getSize());
			if (!c->horniness.isMax())
			{
				c->horniness = c->horniness.get() +  randomReal(0, 10);
			}
			if (c->getSize() < c->genes.maxSize.get())
			{
				c->setSize(c->getSize() + 1);
			}
			f->markToDelete();
		}
	}
}

void CellRoles::updateColor(Cell * c)
{
	static double threshold = 30;

	Ranged<int, 0, 255> newR, newG, newB;

	auto newColor = c->baseColor;

	//temperature
	auto& envTemp = Environment::getInstance().getTemperature();
	auto& envRad = Environment::getInstance().getRadiation();
	if (envTemp > threshold)
	{
		newR = 2 * abs(envTemp - threshold) + c->baseColor.r;
		newColor.r = newR.get();
	}
	else if (envTemp < -threshold)
	{
		newB = 2 * abs(envTemp + threshold) + c->baseColor.b;
		newColor.b = newB.get();
	}

	//radiation
	if (envRad > threshold)
	{
		newG = 3 * abs(envRad - threshold) + c->baseColor.g;
		newColor.g = newG.get();
	}

	c->shape.setFillColor(newColor);
}

void CellRoles::beDead(Cell * c)
{
	auto color = c->shape.getFillColor();
	if (color.a > 0)
	{
		double a = static_cast<double>(color.a) - CellSimApp::getInstance().getDeltaTime();
		if (0 > a) a = 0;
		color.a = a;
		c->shape.setFillColor(color);
	}
	else
	{
		c->markToDelete();
	}
}


void CellRoles::simulateHunger(Cell * c) {
	c->foodLevel -= randomReal(0.005, 0.02) * CellSimApp::getInstance().getDeltaTime();
	if (c->foodLevel <= 0)
	{
		c->kill();
	}

}

void CellRoles::divideAndConquer(Cell * c)
{
	auto& cells = Environment::getInstance().getCellsVector();
	if (c->foodLevel >= c->genes.foodLimit.get() && c->getSize() >= c->genes.maxSize.get() && randomInt(0, 100) <= c->genes.divisionThreshold.get())
	{
		c->foodLevel = 50;
		c->setSize(20);
		Environment::getInstance().insertNewCell(std::make_shared<Cell>(*c));
		c->setRotation(c->getRotation() + 180);
	}
}

void CellRoles::grow(Cell * c)
{
	auto rand = randomReal(0.025, 0.06);

	if (c->getSize() < c->genes.maxSize.get() && c->foodLevel > 50)
	{
		c->setSize(c->getSize() + rand * CellSimApp::getInstance().getDeltaTime());
	}

	if (c->getSize() > 10 && c->foodLevel < 20)
	{
		c->setSize(c->getSize() - rand * CellSimApp::getInstance().getDeltaTime());
	}
}

void CellRoles::getingHot(Cell * c)
{
	if (c->horniness.isMax())
	{
		auto & cells = Environment::getInstance().getCellsVector();
		for (auto & cell : cells)
		{
			if (cell->getHorniness().isMax() && c->genes.type.get()==cell->genes.type.get() && c->collision(cell))
			{
				c->setHorniness(0);
				cell->setHorniness(0);
				std::shared_ptr<Cell> tmp = std::make_shared<Cell>(*c, *cell);
				Environment::getInstance().insertNewCell(tmp);
			}
		}
	}
}

void CellRoles::makeFood(Cell * c)
{
	if (randomInt(0, 1000) > 998)
	{
		auto size = c->getSize();

		int foods = randomInt(0, 100) > 70 ? 2 : 1;
		auto foodSize = 0.4 * size;
		auto& foodsVect = Environment::getInstance().getNewFoodsVector();

		for (int i = 0; i < foods; ++i)
		{
			float xDeviation = randomInt(-size / 2, size / 2);
			float yDeviation = randomInt(-size / 2, size / 2);

			auto position = c->getPosition() + sf::Vector2f{ xDeviation, yDeviation };

			auto food = std::make_shared<Food>(Food(foodSize, position, c->getBaseColor()));
			foodsVect.push_back(food);
		}
	}

}

void CellRoles::fight(Cell * c)
{
	std::vector<std::shared_ptr<Cell>> cells = Environment::getInstance().getCellsVector();

	for (auto& cell : cells)
	{
		if (c->collision(cell) && c != cell.get())
		{
			float cSize = c->getSize();
			float cellSize = cell->getSize();
			int sizeDelta = 2;
			
			if (cSize > cellSize) {
				c->setSize(cSize - sizeDelta);
				cell->setSize(cellSize + sizeDelta);
				cell->foodLevel += sizeDelta;
			}
			else if (cSize < cellSize) {
				c->setSize(cSize + sizeDelta);
				c->foodLevel += sizeDelta;
				cell->setSize(cellSize - sizeDelta);
			}

			double cCurrentSpeed = c->getCurrentSpeed();
			double cellCurrentSpeed = cell->getCurrentSpeed();
			
			c->setRotation(c->getRotation() + 180);
			c->shape.move(cCurrentSpeed * std::sin((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime(), cCurrentSpeed * -std::cos((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime());
			cell->setRotation(c->getRotation() + 180);
			cell->shape.move(cellCurrentSpeed * std::sin((PI / 180)*cell->getRotation()) * CellSimApp::getInstance().getDeltaTime(), cellCurrentSpeed * -std::cos((PI / 180)*cell->getRotation()) * CellSimApp::getInstance().getDeltaTime());
		}
	}
}

void CellRoles::makeOlder(Cell * c)
{
	if (c->age >= c->genes.maxAge.get())
	{
		c->kill();
		return;
	}
	c->age += CellSimApp::getInstance().getDeltaTime()*0.01;
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
