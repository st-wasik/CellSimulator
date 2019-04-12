#include "FilesManager.h"



FilesManager::FilesManager()
{
}


FilesManager::~FilesManager()
{
}

FilesManager & FilesManager::getInstance()
{
	static FilesManager instance;
	return instance;
}

std::string FilesManager::readFile(std::string filename)
{
	const std::string fullName = fileDirectory + filename + fileFormat;
	std::ifstream fin(fullName);

	if (fin.fail()) throw std::exception((std::string("Cannot open file ") + fullName).c_str());
	auto content = std::string{ std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>() };
	fin.close();
	return content;
}

void FilesManager::writeFile(std::string filename, std::string content)
{
	const std::string fullName = fileDirectory + filename + fileFormat;
	std::ofstream fout(fileDirectory + filename + fileFormat);

	if (fout.fail()) throw std::exception((std::string("Cannot open file ") + fullName).c_str());

	fout << content;
	fout.close();
}
