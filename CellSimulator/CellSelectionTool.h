#pragma once
#include<vector>
#include<mutex>
#include"Cell.h"
class CellSelectionTool
{
public:
	static CellSelectionTool& getInstance();

	void update();

	void draw(sf::RenderWindow&);

	void clearSelectedCell();

	void setSelectedCell(std::shared_ptr<Cell>&);

	std::shared_ptr<Cell> getSelectedCell();

private:
	CellSelectionTool();
	CellSelectionTool(const CellSelectionTool&) = delete;
	CellSelectionTool& operator=(const CellSelectionTool&) = delete;

	std::shared_ptr<Cell> selectedCell;

	sf::CircleShape selectionMarker;
};

