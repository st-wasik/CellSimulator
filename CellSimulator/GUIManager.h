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

	static constexpr int backgroundWidth = 360;
private:
	GUIManager();
	GUIManager(const GUIManager&) = delete;
	GUIManager& operator=(const GUIManager&) = delete;
	~GUIManager();

	std::shared_ptr<sf::RenderWindow> window;

	int mode = 1;

	std::shared_ptr<tgui::Gui> mainGui,previewGui,createGui,modifyGui,insertGui,feedGui;

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
	std::shared_ptr<tgui::MenuBar> createMenuBar(std::shared_ptr<tgui::Gui> gui, int width, int height);
	std::shared_ptr<tgui::ListBox> createListBox(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y);


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
		buttonPreview,
		buttonCreate,
		buttonModify,
		buttonInsert;

	std::shared_ptr<tgui::EditBox>
		editBoxTemp,
		editBoxRad,
		editBoxQuan,
		editBoxFreq;

	std::shared_ptr<tgui::CheckBox>
		checkBoxFeed;
	std::shared_ptr<tgui::MenuBar>
		menuBar;

	//MULTI GUI
	std::shared_ptr<tgui::Label>
		aggresionValLabel,
		foodLevelValLabel,
		speedValLabel,
		sizeValLabel,
		horninessValLabel,
		ageValLabel,
		radarRangeValLabel,
		divisionThresholdValLabel;


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

	//CELL CREATE
	std::shared_ptr<tgui::EditBox>
		sizeC,
		speedC,
		ageC,
		horninessC,
		aggresionC,
		foodLevelC,
		divisionThresholdC,
		radarRangeC,
		nameC;

	std::shared_ptr<tgui::Button>
		buttonCreateC,
		buttonSaveC;

	//CELL MODIFY
	std::shared_ptr<tgui::EditBox>
		sizeM,
		speedM,
		ageM,
		horninessM,
		aggresionM,
		foodLevelM,
		divisionThresholdM,
		radarRangeM,
		nameM;

	std::shared_ptr<tgui::Button>
		buttonModifyM;

	//CELL INSERT
	std::shared_ptr<tgui::Label>
		aggresionValTTI,
		foodLevelValTTI,
		speedValTTI,
		sizeValTTI,
		horninessValTTI,
		ageValTTI,
		radarRangeTTI,
		divisionThresholdTTI;

	std::shared_ptr<tgui::ProgressBar>
		aggresionValI,
		foodLevelValI,
		speedValI,
		sizeValI,
		horninessValI,
		ageValI;

	std::shared_ptr<tgui::TextBox>
		radarRangeValI,
		divisionThresholdValI;

	std::shared_ptr<tgui::ListBox>
		listBoxI;

	std::shared_ptr<tgui::Button>
		buttonInsertI;

	//FEED
	std::shared_ptr<tgui::Slider>
		sliderRadius,
		sliderFreqF;

	std::shared_ptr<tgui::Button>
		buttonRadius,
		buttonFreqF;

	std::shared_ptr<tgui::EditBox>
		editBoxRadius,
		editBoxFreqF;
};

