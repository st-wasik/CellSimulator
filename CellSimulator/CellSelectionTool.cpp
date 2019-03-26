#include "CellSelectionTool.h"
#include "CellSimMouse.h"
#include "Environment.h"
#include "Distance.h"

CellSelectionTool & CellSelectionTool::getInstance()
{
	static CellSelectionTool instance;
	return instance;
}

void CellSelectionTool::update()
{
	if (CellSimMouse::wasLeftPressed())
	{
		CellSelectionTool::clearSelectedCell();
		auto& cells = Environment::getInstance().getCellsVector();
		auto selectedCell = std::find_if(cells.begin(), cells.end(), [&](std::shared_ptr<Cell> c) {return getDistance(c->getPosition(), CellSimMouse::getPosition()) < c->getSize(); });
		if (selectedCell != cells.end())
		{
			setSelectedCell(*selectedCell);
		}
	}


	if (selectedCell != nullptr)
	{
		float size = selectedCell->getSize() + 30;
		selectionMarker.setRadius(size);
		selectionMarker.setOrigin(size, size);
		selectionMarker.setPosition(selectedCell->getPosition());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
		{
			selectedCell->kill();
		}
		if (selectedCell->isMarkedToDelete() || selectedCell->isDead()) selectedCell = nullptr;
	}
}

void CellSelectionTool::draw(sf::RenderWindow &w)
{
	if (selectedCell != nullptr)
		w.draw(selectionMarker);
}

void CellSelectionTool::clearSelectedCell()
{
	selectedCell = nullptr;
}

void CellSelectionTool::setSelectedCell(std::shared_ptr<Cell> &s)
{
	selectedCell = s;

	selectionMarker.setFillColor(sf::Color::Transparent);
	selectionMarker.setOutlineColor(sf::Color(192, 192, 192, 128));
	selectionMarker.setOutlineThickness(5);
	selectionMarker.setPosition(selectedCell->getPosition());
}

std::shared_ptr<Cell> CellSelectionTool::getSelectedCell()
{
	return selectedCell;
}

CellSelectionTool::CellSelectionTool()
{
}
