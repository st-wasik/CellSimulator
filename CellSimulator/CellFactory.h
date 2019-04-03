#pragma once
#include "Cell.h"
#include <memory>
class CellFactory
{
public:
	CellFactory() = delete;
	~CellFactory() = delete;

	static std::shared_ptr<Cell> getCell(Cell::Type);
};

