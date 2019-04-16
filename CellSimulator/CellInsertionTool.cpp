#include "CellInsertionTool.h"
#include "Environment.h"
#include "CellSimMouse.h"
#include "CellFactory.h"
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

		if (CellSimMouse::wasLeftPressed())
		{
			if (Environment::getInstance().isCellInEnvironmentBounds(*cellBlueprint))
			{
				auto newCell = Cell::create(*cellBlueprint);
				newCell->unfreeze();
				newCell->setRotation(randomInt(0, 359));
				Environment::getInstance().insertNewCell(newCell);
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

	auto newCell = Cell::create(*cell);
	newCell->freeze();
	newCell->setRotation(0);
	cellBlueprint = newCell;
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

CellInsertionTool::CellInsertionTool() : cellBlueprint(nullptr)
{
}


CellInsertionTool::~CellInsertionTool()
{
}
