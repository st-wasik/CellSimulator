#include "CellSelectionController.h"
#include "CellSimMouse.h"
#include "Environment.h"

std::shared_ptr<Cell> CellSelectionController::selectedCell;

sf::CircleShape CellSelectionController::selectionMarker;

void CellSelectionController::update()
{
	if (selectedCell != nullptr)
	{
		float size = selectedCell->getSize() + 20;
		selectionMarker.setRadius(size);
		selectionMarker.setOrigin(size, size);
		selectionMarker.setPosition(selectedCell->getPosition());
	}
}

void CellSelectionController::draw(sf::RenderWindow &w)
{
	if (selectedCell != nullptr)
		w.draw(selectionMarker);
}

void CellSelectionController::clearSelectedCell()
{
	selectedCell = nullptr;
}

void CellSelectionController::setSelectedCell(std::shared_ptr<Cell> &s)
{
	selectedCell = s;

	float size = selectedCell->getSize() + 20;
	selectionMarker.setRadius(size);
	selectionMarker.setOrigin(size, size);
	selectionMarker.setPosition(selectedCell->getPosition());
	selectionMarker.setFillColor(sf::Color::Transparent);
	selectionMarker.setOutlineColor(sf::Color(192, 192, 192, 128));
	selectionMarker.setOutlineThickness(3);
}

std::shared_ptr<Cell> CellSelectionController::getSelectedCell()
{
	return selectedCell;
}
