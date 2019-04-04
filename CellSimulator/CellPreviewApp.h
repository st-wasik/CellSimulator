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
		maxSpeed,
		aggresion,
		radarRange,
		divisionThreshold,
		foodLimit,
		maxSize,
		age,
		foodLevel,
		currentSpeed,
		size,
		horniness,
		maxSpeedVal,
		aggresionVal,
		radarRangeVal,
		divisionThresholdVal,
		foodLimitVal,
		maxSizeVal,
		ageVal,
		foodLevelVal,
		currentSpeedVal,
		sizeVal,
		horninessVal;

};

