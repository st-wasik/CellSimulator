#include "CellMovementTool.h"
#include "CellSimMouse.h"
#include "Environment.h"
#include "CellSelectionTool.h"
#include "CellSimApp.h"

CellMovementTool & CellMovementTool::getInstance()
{
	static CellMovementTool instance;
	return instance;
}

void CellMovementTool::update()
{
	constexpr int selectionMargin = 50;
	constexpr double positioningMargin = 0.5;

	if (CellSimMouse::isLeftPressed() && isActive)
	{
		if (selectedCell != nullptr)
		{

			auto newPos = selectedCell->getPosition() + CellSimMouse::getPositionShift();
			auto envSize = Environment::getInstance().getSize();
			auto cellSize = selectedCell->getSize();

			if (newPos.x - cellSize < 0)
				newPos.x = 0 + positioningMargin + cellSize;
			else if (newPos.x + cellSize > envSize.x)
				newPos.x = envSize.x - positioningMargin - cellSize;
			if (newPos.y - cellSize < 0)
				newPos.y = 0 + positioningMargin + cellSize;
			else if (newPos.y + cellSize > envSize.y)
				newPos.y = envSize.y - positioningMargin - cellSize;

			selectedCell->setPosition(newPos);

			float size = 0;
			//float size = selectedCell->getSize() + 30;
			selectionMarker.setRadius(size);
			selectionMarker.setOrigin(size, size);
			selectionMarker.setPosition(newPos);
			selectionMarker.setPointCount(7);
			selectionMarker.rotate(0.75*CellSimApp::getInstance().getDeltaTime());
		}
		else
		{
			// if key pressed once
			if (CellSimMouse::wasLeftPressed() && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				auto cell = Environment::getInstance().getCellAtPosition(CellSimMouse::getPosition());
				if (cell != nullptr)
				{
					attachCell(cell);
				}
			}
		}
	}
	else
	{
		detachCell();
	}
}

void CellMovementTool::draw(sf::RenderWindow &w)
{
	if (selectedCell != nullptr)
	{
		w.draw(selectionMarker);
		w.draw(*selectedCell);
	}
}

void CellMovementTool::detachCell()
{
	if (selectedCell != nullptr)
	{
		CellSelectionTool::getInstance().setSelectedCell(selectedCell);

		placeCellToEnvironment();
		selectedCell->unfreeze();
		selectedCell = nullptr;
	}
}

void CellMovementTool::attachCell(std::shared_ptr<Cell>&s)
{
	selectedCell = s;
	selectedCell->freeze();
	pickCellFromEnvironment();

	CellSelectionTool::getInstance().clearSelectedCell();

	selectionMarker.setFillColor(sf::Color(255, 255, 255, 0));
	selectionMarker.setOutlineColor(sf::Color(192, 192, 192, 128));
	selectionMarker.setOutlineThickness(5);
	selectionMarker.setPosition(selectedCell->getPosition());
}

std::shared_ptr<Cell> CellMovementTool::getAttachedCell()
{
	return selectedCell;
}

void CellMovementTool::setIsActive(bool a)
{
	isActive = a;
}

bool CellMovementTool::getIsActive()
{
	return isActive;
}

CellMovementTool::CellMovementTool() : isActive(false)
{
}

double CellMovementTool::getDistance(const sf::Vector2f & a, const sf::Vector2f & b)
{
	auto v = a - b;
	return sqrt(v.x*v.x + v.y*v.y);
}

void CellMovementTool::pickCellFromEnvironment()
{
	if (selectedCell != nullptr)
	{
		auto& cells = Environment::getInstance().getCellsVector();

		auto cellToPick = std::find(cells.begin(), cells.end(), selectedCell);
		if (cellToPick != cells.end())
			cells.erase(cellToPick);
	}
}

void CellMovementTool::placeCellToEnvironment()
{
	if (selectedCell != nullptr)
	{
		Environment::getInstance().getCellsVector().push_back(selectedCell);
	}
}
