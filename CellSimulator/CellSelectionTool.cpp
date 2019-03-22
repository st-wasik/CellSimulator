#include "CellSelectionTool.h"
#include "CellSimMouse.h"
#include "Environment.h"

std::shared_ptr<Cell> CellSelectionTool::selectedCell;

sf::CircleShape CellSelectionTool::selectionMarker;

void CellSelectionTool::update()
{
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
		if (selectedCell->toDelete) selectedCell = nullptr;
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
