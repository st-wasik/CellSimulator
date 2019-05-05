#pragma once
#include "Cell.h"
class CellInsertionTool
{
public:
	static CellInsertionTool& getInstance();

	void update();

	void draw(sf::RenderWindow& w);

	void setCellBlueprint(Cell::Ptr cell);

	void setRandomMode();

	Cell::Ptr getCellBlueprint();

	void setIsActive(bool a);
	bool getIsActive();

private:
	CellInsertionTool();
	CellInsertionTool(const CellInsertionTool&) = delete;
	CellInsertionTool& operator=(const CellInsertionTool&) = delete;
	~CellInsertionTool();

	Cell::Ptr cellBlueprint;

	bool isActive;
	bool random;

	static constexpr int cellSpawnTime = 5;
};

