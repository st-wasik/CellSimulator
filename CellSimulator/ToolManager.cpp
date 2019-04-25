#include "ToolManager.h"
#include "CellMovementTool.h"
#include "CellInsertionTool.h"
#include "CellSelectionTool.h"
#include "FoodBrush.h"

ToolManager & ToolManager::getInstance()
{
	static ToolManager instance;
	return instance;
}


ToolManager::Tool ToolManager::getActiveTool()
{
	return activeTool;
}

void ToolManager::setActiveTool(Tool tool)
{
	activeTool = tool;

	if (active)
		reconfigure();
}

void ToolManager::disable()
{
	active = false;
	deactivateAllTools();
}

void ToolManager::enable()
{
	active = true;
	reconfigure();
}

ToolManager::ToolManager() : active(false), activeTool(Tool::None)
{
	deactivateAllTools();
}

void ToolManager::deactivateAllTools()
{
	CellMovementTool::getInstance().setIsActive(false);
	CellInsertionTool::getInstance().setIsActive(false);
	CellSelectionTool::getInstance().setIsActive(false);
	FoodBrush::getInstance().setIsActive(false);
}

void ToolManager::reconfigure()
{
	deactivateAllTools();
	switch (activeTool)
	{
	case Tool::Feeder:
		FoodBrush::getInstance().setIsActive(true);
		break;
	case Tool::Insertion:
		CellInsertionTool::getInstance().setIsActive(true);
		break;
	case Tool::SelectionMovement:
		CellSelectionTool::getInstance().setIsActive(true);
		CellMovementTool::getInstance().setIsActive(true);
		break;
	case Tool::None:
		break;
	}
}


ToolManager::~ToolManager()
{
}
