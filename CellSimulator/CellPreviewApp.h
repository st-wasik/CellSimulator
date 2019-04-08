#pragma once
#include <string>
#include<SFML/Graphics.hpp>
#include<TGUI/TGUI.hpp>
#include<atomic>
class CellPreviewApp
{
public:
	~CellPreviewApp();

	static CellPreviewApp& getInstance();

	void update();

	void close();

	void configure();

	std::shared_ptr<sf::RenderWindow> getWindowHandle();

private:
	CellPreviewApp();
	CellPreviewApp(const CellPreviewApp&) = delete;
	CellPreviewApp& operator=(const CellPreviewApp&) = delete;

	std::shared_ptr<sf::RenderWindow> window;

	sf::VideoMode windowVideoMode;

	std::string windowTitle;

	std::shared_ptr<tgui::Gui> gui;

	tgui::Theme theme;

	//gui elements
	std::shared_ptr<tgui::Label>
		aggresion,
		radarRange,
		divisionThreshold,
		foodLevel,
		speed,
		size,
		horniness,
		age,
		aggresionValTT,
		radarRangeValTT,
		divisionThresholdValTT,
		foodLevelValTT,
		speedValTT,
		sizeValTT,
		horninessValTT,
		ageValTT;
		
	std::shared_ptr<tgui::ProgressBar>
		aggresionVal,
		radarRangeVal,
		divisionThresholdVal,
		foodLevelVal,
		speedVal,
		sizeVal,
		horninessVal,
		ageVal;

};