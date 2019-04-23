#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
class CellMovementTool
{
public:
	static CellMovementTool& getInstance();

	void update();

	void draw(sf::RenderWindow&);

	void detachCell();

	void attachCell(std::shared_ptr<Cell>&);

	std::shared_ptr<Cell> getAttachedCell();

	void setIsActive(bool a);
	bool getIsActive();

private:
	CellMovementTool();
	CellMovementTool(const CellMovementTool&) = delete;
	CellMovementTool& operator=(const CellMovementTool&) = delete;

	std::shared_ptr<Cell> selectedCell;

	sf::CircleShape selectionMarker;

	double getDistance(const sf::Vector2f& a, const sf::Vector2f& b);

	void  pickCellFromEnvironment();

	void  placeCellToEnvironment();

	bool isActive;
};

