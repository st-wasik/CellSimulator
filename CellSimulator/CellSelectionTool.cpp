#include "CellSelectionTool.h"
#include "CellSimMouse.h"
#include "Environment.h"
#include "Distance.h"
#include "CellSimApp.h"
#include "CellMovementTool.h"

CellSelectionTool & CellSelectionTool::getInstance()
{
	static CellSelectionTool instance;
	return instance;
}

void CellSelectionTool::update()
{
	if (CellSimMouse::wasLeftPressed() && isActive)
	{
		CellSelectionTool::clearSelectedCell();
		auto movedCell = CellMovementTool::getInstance().getAttachedCell();
		if (movedCell == nullptr)
		{
			auto& cells = Environment::getInstance().getCellsVector();
			auto selectedCell = std::find_if(cells.begin(), cells.end(), [&](std::shared_ptr<Cell> c) {return getDistance(c->getPosition(), CellSimMouse::getPosition()) < c->getSize(); });
			if (selectedCell != cells.end())
			{
				setSelectedCell(*selectedCell);
			}
		}
		else
		{
			selectedMovedCell = true;
			setSelectedCell(movedCell);
		}
	}

	if (selectedCell != nullptr)
	{
		*selectedCellCopy = *selectedCell;
		selectedCellCopyValid = true;

		updateSelectionMarker();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
		{
			selectedCell->kill();
		}

		if (selectedCell->isMarkedToDelete() || selectedCell->isDead())
		{
			selectedCell = nullptr;
			selectedCellCopyValid = false;
			if (selectedMovedCell) selectedMovedCell = false;
		}
	}
	else
	{
		selectedCellCopyValid = false;
	}
}

void CellSelectionTool::updateSelectionMarker()
{
	if (selectedCell != nullptr)
	{
		float size = selectedCell->getSize() + 30;
		auto pos = selectedCell->getPosition();
		selectionMarker.setRadius(size);
		selectionMarker.setOrigin(size, size);
		selectionMarker.setPosition(pos);

		auto closestCell = selectedCell->getClosestCell();
		if (closestCell != nullptr)
		{
			targetCellSelectionMarker.setRadius(closestCell->getSize() + 20);
			targetCellSelectionMarker.setOrigin(closestCell->getSize() + 20, closestCell->getSize() + 20);
			targetCellSelectionMarker.setPosition(closestCell->getPosition());
		}

		auto closestFood = selectedCell->getClosestFood();
		if (closestFood != nullptr)
		{
			targetFoodSelectionMarker.setRadius(closestFood->getSize() + 20);
			targetFoodSelectionMarker.setOrigin(closestFood->getSize() + 20, closestFood->getSize() + 20);
			targetFoodSelectionMarker.setPosition(closestFood->getPosition());
		}

		auto radarRadius = selectedCell->getGenes().radarRange.get();
		cellRadarRange.setOrigin(sf::Vector2f(radarRadius, radarRadius));
		cellRadarRange.setRadius(radarRadius);
		cellRadarRange.setPosition(pos);

		selectedCellName.setString(selectedCell->getName());
		selectedCellName.setOrigin({ selectedCellName.getGlobalBounds().width / 2, selectedCellName.getGlobalBounds().height / 2 });
		selectedCellName.setPosition({ pos.x, pos.y - nameMargin - selectedCell->getSize() });
	}
}

void CellSelectionTool::draw(sf::RenderWindow &w)
{
	if (selectedCell != nullptr)
	{
		w.draw(selectionMarker);
		w.draw(cellRadarRange);
		w.draw(selectedCellName);
		if (selectedCell->getClosestCell() != nullptr && selectedCell->getGenes().type.get() != 1)
			w.draw(targetCellSelectionMarker);

		if (selectedCell->getClosestFood() != nullptr  && selectedCell->getGenes().type.get() != 2)
			w.draw(targetFoodSelectionMarker);
	}
}

void CellSelectionTool::clearSelectedCell()
{
	setFollowSelectedCell(false);
	selectedCellName.setString("");
	selectedCell = nullptr;
}

void CellSelectionTool::setSelectedCell(std::shared_ptr<Cell> &s)
{
	selectedCell = s;

	selectionMarker.setFillColor(sf::Color::Transparent);
	selectionMarker.setOutlineColor(sf::Color(192, 192, 192, 128));
	selectionMarker.setOutlineThickness(5);
	selectionMarker.setPosition(selectedCell->getPosition());


	auto targetCell = selectedCell->getClosestCell();
	if (targetCell != nullptr)
	{
		targetCellSelectionMarker.setPosition(targetCell->getPosition());
	}

	auto targetFood = selectedCell->getClosestFood();
	if (targetCell != nullptr)
	{
		targetFoodSelectionMarker.setPosition(targetCell->getPosition());
	}

	cellRadarRange.setFillColor(sf::Color(0, 0, 0, 16));
	auto radius = selectedCell->getGenes().radarRange.get() * 50;
	cellRadarRange.setPosition(selectedCell->getPosition());
	cellRadarRange.setOrigin(sf::Vector2f(radius, radius));
	cellRadarRange.setRadius(radius);
}

std::shared_ptr<Cell> CellSelectionTool::getSelectedCell()
{
	return selectedCell;
}

std::shared_ptr<Cell> CellSelectionTool::getSelectedCellCopy()
{
	if (selectedCellCopyValid)
	{
		auto result = Cell::create(*selectedCellCopy);
		return std::dynamic_pointer_cast<Cell>(result);
	}
	return nullptr;
}

std::atomic_bool& CellSelectionTool::getFollowSelectedCell()
{
	return followSelectedCell;
}

void CellSelectionTool::setFollowSelectedCell(bool f)
{
	if (selectedCell != nullptr && f == true)
		followSelectedCell = f;
	if (f == false)
		followSelectedCell = f;
}

void CellSelectionTool::setIsActive(bool a)
{
	isActive = a;
}

bool CellSelectionTool::getIsActive()
{
	return isActive;
}

CellSelectionTool::CellSelectionTool() : selectedCellCopyValid(false), isActive(false)
{
	selectedCellCopy = Cell::create(0.0, sf::Vector2f{ 0.0f, 0.0f }, sf::Color::Transparent);

	selectedCellName.setFont(CellSimApp::getInstance().getFont());
	selectedCellName.setCharacterSize(fontSize);
	selectedCellName.setFillColor(sf::Color::White);

	selectedMovedCell = false;

	targetCellSelectionMarker.setFillColor(sf::Color::Transparent);
	targetCellSelectionMarker.setOutlineColor(sf::Color(216, 0, 0, 128));
	targetCellSelectionMarker.setOutlineThickness(5);

	targetFoodSelectionMarker.setFillColor(sf::Color::Transparent);
	targetFoodSelectionMarker.setOutlineColor(sf::Color(0, 216, 0, 128));
	targetFoodSelectionMarker.setOutlineThickness(5);
}
