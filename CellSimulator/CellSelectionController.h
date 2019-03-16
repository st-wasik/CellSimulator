#pragma once
#include<vector>
#include<mutex>
#include"Cell.h"
class CellSelectionController
{
public:
	CellSelectionController() = delete;

	static void update();

	static void draw(sf::RenderWindow&);

	static void clearSelectedCell();

	static void setSelectedCell(std::vector<Cell>::iterator&);

	static void getSelectedCell();

private:
	static std::vector<Cell>::iterator selectedCell;

	static sf::CircleShape selectionMarker;

	static std::mutex selectionMutex;

	static bool isSelectionValid;

};

