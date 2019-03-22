#pragma once
#include<vector>
#include<mutex>
#include"Cell.h"
class CellSelectionTool
{
public:
	CellSelectionTool() = delete;

	static void update();

	static void draw(sf::RenderWindow&);

	static void clearSelectedCell();

	static void setSelectedCell(std::shared_ptr<Cell>&);

	static std::shared_ptr<Cell> getSelectedCell();

private:
	static std::shared_ptr<Cell> selectedCell;

	static sf::CircleShape selectionMarker;
};

