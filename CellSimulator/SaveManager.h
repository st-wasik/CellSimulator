#pragma once
#include <string>
#include "Cell.h"
#include <list>
class SaveManager
{
public:
	static constexpr const char* const envSaveDir = "./saves/";
	static constexpr const char* const envSaveFormat = ".env";

	static constexpr const char* const cellSaveDir = "./cells/";
	static constexpr const char* const cellSaveFormat = ".cell";

	~SaveManager();
	static SaveManager& getInstance();

	bool saveCellToFile(Cell::Ptr cell, std::string filename);

	void saveEnvironmentToFile(std::string filename);

	Cell::Ptr readCellFromFile(std::string filename);

	void readEnvironmentFromFile(std::string filename);

	std::vector<std::string> getAvailableCellSaves();
	std::vector<std::string> getAvailableEnvSaves();

private:
	SaveManager();
	SaveManager(const SaveManager&) = delete;
	SaveManager& operator=(const SaveManager&) = delete;
};

