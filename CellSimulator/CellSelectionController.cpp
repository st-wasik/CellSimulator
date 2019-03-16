#include "CellSelectionController.h"
#include "CellSimMouse.h"
#include "Environment.h"

std::vector<Cell>::iterator CellSelectionController::selectedCell;

sf::CircleShape CellSelectionController::selectionMarker;

std::mutex CellSelectionController::selectionMutex;

bool CellSelectionController::isSelectionValid = false;

void CellSelectionController::update()
{
	std::lock_guard<std::mutex> lock(selectionMutex);
	if (isSelectionValid)
	{
		float size = selectedCell->getSize() + 20;
		selectionMarker.setRadius(size);
		selectionMarker.setOrigin(size, size);
		selectionMarker.setPosition(selectedCell->getPosition());
	}
}

void CellSelectionController::draw(sf::RenderWindow &w)
{
	std::lock_guard<std::mutex> lock(selectionMutex);
	if (isSelectionValid)
		w.draw(selectionMarker);
}

void CellSelectionController::clearSelectedCell()
{
	std::lock_guard<std::mutex> lock(selectionMutex);
	isSelectionValid = false;
}

void CellSelectionController::setSelectedCell(std::vector<Cell>::iterator &s)
{
	std::lock_guard<std::mutex> lock(selectionMutex);

	selectedCell = s;
	isSelectionValid = true;
	float size = selectedCell->getSize() + 20;
	selectionMarker.setRadius(size);
	selectionMarker.setOrigin(size, size);
	selectionMarker.setPosition(selectedCell->getPosition());
	selectionMarker.setFillColor(sf::Color::Transparent);
	selectionMarker.setOutlineColor(sf::Color(192, 192, 192, 128));
	selectionMarker.setOutlineThickness(3);
}
