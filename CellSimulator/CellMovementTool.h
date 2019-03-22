#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
class CellMovementTool
{
public:
	CellMovementTool() = delete;

	static void update();

	static void draw(sf::RenderWindow&);

	static void detachCell();

	static void attachCell(std::shared_ptr<Cell>&);

	static std::shared_ptr<Cell> getAttachedCell();

private:
	static std::shared_ptr<Cell> selectedCell;

	static sf::CircleShape selectionMarker;

	static double getDistance(const sf::Vector2f& a, const sf::Vector2f& b);

	void static pickCellFromEnvironment();

	void static placeCellToEnvironment();
};

