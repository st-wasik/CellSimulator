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

	sf::RectangleShape background;

	void setVisible(std::vector<std::shared_ptr<tgui::Widget>> widgets, int enable);
	void updateValues(std::shared_ptr<tgui::Label> ValTT, std::shared_ptr<tgui::ProgressBar> Val, sf::String setTextTT, sf::String setText, int max, int min, int val);

	std::shared_ptr<tgui::Label> createLabel(std::shared_ptr<tgui::Gui> gui, std::string text, int x, int y, int textSize, std::shared_ptr<tgui::Label> tooltip, int enabled, std::string renderer);
	std::shared_ptr<tgui::EditBox> createEditBox(std::shared_ptr<tgui::Gui> gui, int width, int height, int textSize, int x, int y, sf::String defaultText, int enabled);
	std::shared_ptr<tgui::Slider> createSlider(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y, int max, int min, int val, int enabled);
	std::shared_ptr<tgui::Button> createButton(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y, sf::String text, int enabled);
	std::shared_ptr<tgui::CheckBox> createCheckBox(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y, sf::String text, int textSize);
	std::shared_ptr<tgui::ProgressBar> createProgressBar(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y, int textSize, std::shared_ptr<tgui::Label> tooltip, int visible);
	std::shared_ptr<tgui::TextBox> createTextBox(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y, int textSize, int visible);

	//ENV SETTINGS
	std::shared_ptr<tgui::Label>
		labelQuan,
		labelFreq,
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
	std::vector<std::shared_ptr<tgui::Widget>> widgetsPreview;

	std::shared_ptr<tgui::Label>
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

