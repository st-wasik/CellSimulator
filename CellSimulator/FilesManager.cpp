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
	std::ifstream fin(filename);

	if (fin.fail()) throw std::exception((std::string("Cannot open file ") + filename).c_str());
	auto content = std::string{ std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>() };
	fin.close();
	return content;
}

void FilesManager::writeFile(std::string filename, std::string content)
{
	std::ofstream fout(filename);

	if (fout.fail()) throw std::exception((std::string("Cannot open file ") + filename).c_str());

	fout << content;
	fout.close();
}
