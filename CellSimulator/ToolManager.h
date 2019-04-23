#pragma once
class ToolManager
{
public:
	~ToolManager();

	enum class Tool
	{
		Feeder, Insertion, SelectionMovement, None
	};

	static ToolManager& getInstance();

	Tool getActiveTool();
	void setActiveTool(Tool tool);

	void disable();
	void enable();

private:
	ToolManager();
	ToolManager(const ToolManager&) = delete;
	ToolManager& operator=(const ToolManager&) = delete;

	Tool activeTool;
	bool active;

	void deactivateAllTools();

	void reconfigure();
};

