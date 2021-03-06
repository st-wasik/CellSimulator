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

	void setIsActive(bool a);
	bool getIsActive();

private:
	CellSelectionTool();
	CellSelectionTool(const CellSelectionTool&) = delete;
	CellSelectionTool& operator=(const CellSelectionTool&) = delete;

	std::shared_ptr<Cell> selectedCell;
	std::shared_ptr<Cell> selectedCellCopy;

	std::atomic_bool selectedCellCopyValid;

	sf::Text selectedCellName;
	sf::CircleShape selectionMarker;
	sf::CircleShape targetCellSelectionMarker;
	sf::CircleShape targetFoodSelectionMarker;
	sf::CircleShape cellRadarRange;

	std::atomic_bool followSelectedCell;

	bool selectedMovedCell;

	bool isActive;

	static constexpr int fontSize = 20;
	static constexpr int nameMargin = 23;
};

