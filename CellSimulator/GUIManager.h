#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Cell.h"
class GUIManager final
{
public:

	static GUIManager& getInstance();

	void configure(std::shared_ptr<sf::RenderWindow> window);

	void handleEvent(sf::Event& e);

	void update();

	void draw();

private:
	GUIManager();
	GUIManager(const GUIManager&) = delete;
	GUIManager& operator=(const GUIManager&) = delete;
	~GUIManager();

	std::shared_ptr<sf::RenderWindow> window;

	std::shared_ptr<tgui::Gui> gui;

	tgui::Theme theme;

	std::shared_ptr<Cell> selectedCellPtr;

	//ENV SETTINGS
	std::shared_ptr<tgui::Label>
		labelTemp,
		labelRad,
		labelQuan,
		labelFreq,
		labelCells,
		labelFood,
		labelCellsVar,
		labelFoodVar;

	std::shared_ptr<tgui::Slider>
		sliderTemp,
		sliderRad,
		sliderQuan,
		sliderFreq;

	std::shared_ptr<tgui::Button>
		buttonTemp,
		buttonRad,
		buttonQuan,
		buttonFreq,
		buttonFeed,
		buttonSelect;

	std::shared_ptr<tgui::EditBox>
		editBoxTemp,
		editBoxRad,
		editBoxQuan,
		editBoxFreq;

	std::shared_ptr<tgui::CheckBox>
		checkBoxFeed;



	//CELL PREVIEW
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
		foodLevelValTT,
		speedValTT,
		sizeValTT,
		horninessValTT,
		ageValTT,
		radarRangeTT,
		divisionThresholdTT;

	std::shared_ptr<tgui::ProgressBar>
		aggresionVal,
		foodLevelVal,
		speedVal,
		sizeVal,
		horninessVal,
		ageVal;

	std::shared_ptr<tgui::TextBox>
		radarRangeVal,
		divisionThresholdVal;

};

