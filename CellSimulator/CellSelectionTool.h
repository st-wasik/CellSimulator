#pragma once
#include<vector>
#include<mutex>
#include<atomic>
#include"Cell.h"
class CellSelectionTool
{
public:
	static CellSelectionTool& getInstance();

	void update();

	void updateSelectionMarker();

	void draw(sf::RenderWindow&);

	void clearSelectedCell();

	void setSelectedCell(std::shared_ptr<Cell>&);

	std::shared_ptr<Cell> getSelectedCell();

	// returns ptr to copy of cell - this solution is thread-safe
	std::shared_ptr<Cell> getSelectedCellCopy();

	std::atomic_bool& getFollowSelectedCell();
	void setFollowSelectedCell(bool f);

private:
	CellSelectionTool();
	CellSelectionTool(const CellSelectionTool&) = delete;
	CellSelectionTool& operator=(const CellSelectionTool&) = delete;

	std::shared_ptr<Cell> selectedCell;
	std::shared_ptr<Cell> selectedCellCopy;

	std::atomic_bool selectedCellCopyValid;

	sf::CircleShape selectionMarker;
	sf::CircleShape cellRadarRange;

	std::atomic_bool followSelectedCell;
};

