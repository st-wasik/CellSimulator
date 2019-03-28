#pragma once
#include <string>
#include<SFML/Graphics.hpp>
#include<TGUI/TGUI.hpp>
#include<atomic>
#include<mutex>
class CellListApp
{
public:
	~CellListApp();

	static CellListApp& getInstance();

	void update();

	void close();

	void configure();

	std::shared_ptr<sf::RenderWindow> getWindowHandle();

private:
	CellListApp();
	CellListApp(const CellListApp&) = delete;
	CellListApp& operator=(const CellListApp&) = delete;

	std::shared_ptr<sf::RenderWindow> window;

	sf::VideoMode windowVideoMode;

	std::string windowTitle;

	std::shared_ptr<tgui::Gui> gui;

	tgui::Theme theme;

	static std::mutex mutex;

	//gui elements
};
