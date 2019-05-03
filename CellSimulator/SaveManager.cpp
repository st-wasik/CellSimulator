#include "SaveManager.h"
#include "FilesManager.h"
#include "Environment.h"
#include <Windows.h>

SaveManager::SaveManager()
{
}

SaveManager::~SaveManager()
{
}

SaveManager & SaveManager::getInstance()
{
	static SaveManager instance;
	return instance;
}

void SaveManager::saveCellToFile(Cell::Ptr cell, std::string filename)
{
	std::string fullpath = cellSaveDir + filename + cellSaveFormat;
	try
	{
		FilesManager::getInstance().writeFile(fullpath, cell->getCellBlueprintString());
	}
	catch (std::exception e)
	{
		Logger::log(e.what());
	}
}

void SaveManager::saveEnvironmentToFile(std::string filename)
{
	std::string fullpath = envSaveDir + filename + envSaveFormat;
	try
	{
		FilesManager::getInstance().writeFile(fullpath, Environment::getInstance().getSaveString());
	}
	catch (std::exception e)
	{
		Logger::log(e.what());
	}
}

Cell::Ptr SaveManager::readCellFromFile(std::string filename)
{
	std::string saveString;
	std::string fullpath = cellSaveDir + filename + cellSaveFormat;
	try
	{
		saveString = FilesManager::getInstance().readFile(fullpath);
	}
	catch (std::exception e)
	{
		Logger::log(e.what());
	}

	return Cell::create(saveString);
}

void SaveManager::readEnvironmentFromFile(std::string filename)
{
	std::string saveString;
	std::string fullpath = envSaveDir + filename + envSaveFormat;
	try
	{
		saveString = FilesManager::getInstance().readFile(fullpath);
	}
	catch (std::exception e)
	{
		Logger::log(e.what());
	}
	Environment::getInstance().configure(saveString);
}

// https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
std::vector<std::string> SaveManager::getAvailableCellSaves()
{
	std::string folder = cellSaveDir;
	std::vector<std::string> names;
	std::string search_path = folder + "/*" + cellSaveFormat;
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				std::string filename(fd.cFileName);
				filename.erase(filename.end()-std::string(cellSaveFormat).size(), filename.end());
				names.push_back(filename);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

std::vector<std::string> SaveManager::getAvailableEnvSaves()
{
	std::string folder = envSaveDir;
	std::vector<std::string> names;
	std::string search_path = folder + "/*" + envSaveFormat;
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				std::string filename(fd.cFileName);
				filename.erase(filename.end() - std::string(envSaveFormat).size(), filename.end());
				names.push_back(filename);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

