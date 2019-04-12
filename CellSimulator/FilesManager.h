#pragma once
#include <fstream>
#include <string>
class FilesManager
{
public:
	static constexpr const char* const fileDirectory = "";
	static constexpr const char* const fileFormat = ".cell";

	~FilesManager();
	static FilesManager& getInstance();

	// returns the contents of selected file
	std::string readFile(std::string filename);

	// writes string to selected file
	void writeFile(std::string filename, std::string content);

private:
	FilesManager();
	FilesManager(const FilesManager&) = delete;
	FilesManager& operator=(const FilesManager&) = delete;

};

