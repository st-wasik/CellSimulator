#include "CellInsertionTool.h"
#include "Environment.h"
#include "CellSimMouse.h"
#include "CellFactory.h"
#include "CellSimApp.h"
#include "MessagesManager.h"



CellInsertionTool & CellInsertionTool::getInstance()
{
	static CellInsertionTool instance;
	return instance;
}

void CellInsertionTool::update()
{
	if (isActive && cellBlueprint != nullptr)
	{
		cellBlueprint->setPosition(CellSimMouse::getPosition());
		auto cellPos = cellBlueprint->getPosition();

		if (CellSimMouse::wasLeftPressed() || (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && CellSimMouse::isLeftPressed()))
		{
			if (random)
			{
				cellBlueprint = CellFactory::getCell(Cell::Type::Random);
				cellBlueprint->setPosition(cellPos);
				cellBlueprint->setRotation(0);
			}

			if (Environment::getInstance().isCellInEnvironmentBounds(*cellBlueprint))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && CellSimMouse::isLeftPressed())
				{
					for (int i = 0; i < (CellSimApp::getInstance().getDeltaTime() / cellSpawnTime); ++i)
					{
						auto newCell = Cell::create(*cellBlueprint);
						newCell->unfreeze();
						newCell->setRotation(randomInt(0, 359));
						Environment::getInstance().insertNewCell(newCell);
					}
				}
				else
				{
					auto newCell = Cell::create(*cellBlueprint);
					newCell->unfreeze();
					newCell->setRotation(randomInt(0, 359));
					Environment::getInstance().insertNewCell(newCell);
				}
			}
			else
				MessagesManager::getInstance().append("Cell cannot be placed outside environment.");
		}
	}
}

void CellInsertionTool::draw(sf::RenderWindow& w)
{
	if (isActive && cellBlueprint != nullptr)
		w.draw(*cellBlueprint);
}

void CellInsertionTool::setCellBlueprint(Cell::Ptr cell)
{
	if (cell == nullptr) return;

	random = false;

	auto newCell = Cell::create(*cell);
	newCell->freeze();
	newCell->setRotation(0);
	cellBlueprint = newCell;
}

void CellInsertionTool::setRandomMode()
{
	setCellBlueprint(CellFactory::getCell(Cell::Type::Random));
	random = true;
}

Cell::Ptr CellInsertionTool::getCellBlueprint()
{
	return cellBlueprint;
}

void CellInsertionTool::setIsActive(bool a)
{
	isActive = a;
}

bool CellInsertionTool::getIsActive()
{
	return isActive;
}

CellInsertionTool::CellInsertionTool() : cellBlueprint(nullptr), isActive(false), random(false)
{
}


CellInsertionTool::~CellInsertionTool()
{
}
