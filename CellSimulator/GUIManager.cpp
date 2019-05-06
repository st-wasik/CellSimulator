#include "GUIManager.h"
#include "Environment.h"
#include "AutoFeederTool.h"
#include "CellSelectionTool.h"
#include "CellInsertionTool.h"
#include "DoubleToString.h"
#include "ToolManager.h"
#include "CellSimMouse.h"
#include "CellSimApp.h"
#include "MessagesManager.h"
#include "SaveManager.h"
#include "CellFactory.h"
#include "DoubleToString.h"
#include <regex>
#include "RegexPattern.h"

std::shared_ptr<tgui::Label> GUIManager::createLabel(std::shared_ptr<tgui::Gui> gui, std::string text, int x, int y, int textSize, std::shared_ptr<tgui::Label> tooltip = nullptr, int enabled = 1, std::string renderer = "Label")
{
	std::shared_ptr<tgui::Label> Label = tgui::Label::create();

	Label->setRenderer(theme.getRenderer(renderer));
	Label->setText(text);
	Label->setPosition(x, y);
	Label->setTextSize(textSize);
	if (!enabled)
		Label->setInheritedOpacity(0.5);
	Label->setToolTip(tooltip);
	if (renderer == "Label")
		gui->add(Label);

	return Label;
}

std::shared_ptr<tgui::EditBox> GUIManager::createEditBox(std::shared_ptr<tgui::Gui> gui, int width, int height, int textSize, int x, int y, sf::String defaultText, int enabled = 1)
{
	std::shared_ptr<tgui::EditBox> EditBox = tgui::EditBox::create();

	EditBox->setRenderer(theme.getRenderer("EditBox"));
	EditBox->setSize(width, height);
	EditBox->setTextSize(textSize);
	EditBox->setPosition(x, y);
	EditBox->setDefaultText(defaultText);
	EditBox->setAlignment(tgui::EditBox::Alignment::Center);
	if (!enabled)
	{
		EditBox->setEnabled(enabled);
		EditBox->setInheritedOpacity(0.5);
	}
	if (gui != nullptr)
		gui->add(EditBox);

	return EditBox;
}

std::shared_ptr<tgui::Slider> GUIManager::createSlider(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y, int max, int min, int val, int enabled = 1)
{
	std::shared_ptr <tgui::Slider> Slider = tgui::Slider::create();
	Slider->setRenderer(theme.getRenderer("Slider"));
	Slider->setPosition(x, y);
	Slider->setSize(width, height);
	Slider->setMaximum(max);
	Slider->setMinimum(min);
	Slider->setValue(val);
	if (!enabled)
	{
		Slider->setEnabled(enabled);
		Slider->setInheritedOpacity(0.5);
	}
	gui->add(Slider);

	return Slider;
}

std::shared_ptr<tgui::Button> GUIManager::createButton(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y, sf::String text, int enabled = 1)
{
	std::shared_ptr<tgui::Button> Button = tgui::Button::create();
	Button->setRenderer(theme.getRenderer("Button"));
	Button->setPosition(x, y);
	Button->setText(text);
	Button->setSize(width, height);
	if (!enabled)
	{
		Button->setEnabled(enabled);
		Button->setInheritedOpacity(0.5);
	}
	if (gui != nullptr)
		gui->add(Button);

	return Button;
}

std::shared_ptr<tgui::CheckBox> GUIManager::createCheckBox(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y, sf::String text, int textSize)
{
	std::shared_ptr<tgui::CheckBox> CheckBox = tgui::CheckBox::create();
	CheckBox->setRenderer(theme.getRenderer("CheckBox"));
	CheckBox->setPosition(x, y);
	CheckBox->setText(text);
	CheckBox->setSize(width, height);
	CheckBox->setTextSize(textSize);
	gui->add(CheckBox);

	return CheckBox;
}
std::shared_ptr<tgui::ProgressBar> GUIManager::createProgressBar(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y, int textSize, std::shared_ptr<tgui::Label> tooltip, int visible = 0)
{
	std::shared_ptr<tgui::ProgressBar> ProgressBar = tgui::ProgressBar::create();
	ProgressBar->setRenderer(theme.getRenderer("ProgressBar"));
	ProgressBar->setPosition(x, y);
	ProgressBar->setSize(width, height);
	ProgressBar->setTextSize(textSize);
	ProgressBar->setVisible(visible);
	ProgressBar->setToolTip(tooltip);
	gui->add(ProgressBar);

	return ProgressBar;
}
std::shared_ptr<tgui::TextBox> GUIManager::createTextBox(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y, int textSize, int visible = 0)
{
	std::shared_ptr<tgui::TextBox> TextBox = tgui::TextBox::create();
	TextBox->setRenderer(theme.getRenderer("TextBox"));
	TextBox->setPosition(x, y);
	TextBox->setSize(width, height);
	TextBox->setTextSize(textSize);
	TextBox->setVisible(visible);
	TextBox->setReadOnly(1);
	TextBox->setEnabled(0);
	TextBox->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
	gui->add(TextBox);

	return TextBox;
}
std::shared_ptr<tgui::MenuBar> GUIManager::createMenuBar(std::shared_ptr<tgui::Gui> gui, int width, int height)
{
	std::shared_ptr<tgui::MenuBar> MenuBar = tgui::MenuBar::create();
	MenuBar->setRenderer(theme.getRenderer("MenuBar"));
	MenuBar->setSize(width, height);
	MenuBar->addMenu("Simulation");
	MenuBar->addMenu("Help");
	MenuBar->addMenuItem("Simulation", "New");
	MenuBar->connectMenuItem("Simulation", "New", []() {Environment::getInstance().configure(); });
	MenuBar->addMenuItem("Simulation", "New Random");
	MenuBar->connectMenuItem("Simulation", "New Random", []() {Environment::getInstance().configure(sf::Vector2f(randomReal(0.5, 3.5) * 1000, randomReal(0.5, 3.5) * 1000), true); });
	MenuBar->addMenuItem("Simulation", "Clear (C)");
	MenuBar->connectMenuItem("Simulation", "Clear (C)", []() {Environment::getInstance().clear(); });
	MenuBar->addMenuItem("Simulation", "Save (F5)");
	MenuBar->connectMenuItem("Simulation", "Save (F5)", []() {SaveManager::getInstance().saveEnvironmentToFile("quick_save"); });
	MenuBar->addMenuItem("Simulation", "Load (F9)");
	MenuBar->connectMenuItem("Simulation", "Load (F9)", []() {SaveManager::getInstance().readEnvironmentFromFile("quick_save"); });
	MenuBar->addMenuItem("Simulation", "Exit (Esc)");
	MenuBar->connectMenuItem("Simulation", "Exit (Esc)", []() {CellSimApp::getInstance().close(); });
	MenuBar->addMenuItem("Help", "Info");
	MenuBar->addMenuItem("Help", "Authors");
	gui->add(MenuBar);

	return MenuBar;
}

std::shared_ptr<tgui::ListBox> GUIManager::createListBox(std::shared_ptr<tgui::Gui> gui, int width, int height, int x, int y)
{
	std::shared_ptr<tgui::ListBox> ListBox = tgui::ListBox::create();
	ListBox->setRenderer(theme.getRenderer("ListBox"));
	ListBox->setSize(width, height);
	ListBox->setTextSize(18);
	ListBox->setItemHeight(24);
	ListBox->setPosition(x, y);
	ListBox->addItem("Aggressive");
	ListBox->addItem("Passive");
	ListBox->addItem("Lettuce");
	ListBox->addItem("Pizza");
	for (auto& v : SaveManager::getInstance().getAvailableCellSaves())
	{
		ListBox->addItem(v);
	}
	gui->add(ListBox);

	return ListBox;
}

void GUIManager::setVisible(std::vector<std::shared_ptr<tgui::Widget>> widgets, int enable)
{
	for (int i = 0; i < widgets.size(); i++)
	{
		widgets[i]->setVisible(enable);
	}
}

void GUIManager::updateValues(std::shared_ptr<tgui::Label> ValTT, std::shared_ptr<tgui::ProgressBar> Val, sf::String setTextTT, sf::String setText, int max, int min, int val)
{
	ValTT->setText(setTextTT);
	Val->setText(setText);
	Val->setMaximum(max);
	Val->setMinimum(min);
	Val->setValue(val);
}

GUIManager::GUIManager() : typeC(std::make_shared<int>(0))
{
}

GUIManager::~GUIManager()
{
}

GUIManager & GUIManager::getInstance()
{
	static GUIManager instance;
	return instance;
}

void GUIManager::configure(std::shared_ptr<sf::RenderWindow> window)
{
	MessagesManager::getInstance().configure();

	this->window = window;
	mainGui = std::make_shared<tgui::Gui>(*window);
	previewGui = std::make_shared<tgui::Gui>(*window);
	createGui = std::make_shared<tgui::Gui>(*window);
	modifyGui = std::make_shared<tgui::Gui>(*window);
	insertGui = std::make_shared<tgui::Gui>(*window);
	feedGui = std::make_shared<tgui::Gui>(*window);
	theme.load("../../CellSimulator/TGUI-0.8/themes/TransparentGrey.txt");

	background.setSize(sf::Vector2f(backgroundWidth, window->getSize().y));
	background.setFillColor(sf::Color(32, 32, 32, 128));
	background.setPosition({ 0,0 });
	background.setOutlineColor(sf::Color(32, 32, 16));
	background.setOutlineThickness(7);

	//ENV SETTINGS
	menuBar = createMenuBar(mainGui, 360, 20);

	createLabel(mainGui, "Temperature", 50, 25, 18);

	editBoxTemp = createEditBox(mainGui, 60, 25, 18, 220, 42, std::to_string((int)Environment::getInstance().getTemperature()));

	sliderTemp = createSlider(mainGui, 200, 9, 10, 50, 100, -100, Environment::getInstance().getTemperature());

	buttonTemp = createButton(mainGui, 60, 25, 285, 42, "SET");

	createLabel(mainGui, "Radiation", 70, 70, 18);

	editBoxRad = createEditBox(mainGui, 60, 25, 18, 220, 87, std::to_string((int)Environment::getInstance().getRadiation()));

	sliderRad = createSlider(mainGui, 200, 9, 10, 95, 100, 0, Environment::getInstance().getRadiation());

	buttonRad = createButton(mainGui, 60, 25, 285, 87, "SET");

	checkBoxFeed = createCheckBox(mainGui, 15, 15, 10, 130, "Auto-feed", 14);

	labelQuan = createLabel(mainGui, "Food limit [%]", 45, 155, 18, nullptr, 0);

	editBoxQuan = createEditBox(mainGui, 60, 25, 18, 220, 172, std::to_string((int)AutoFeederTool::getInstance().getMaxThresholdValue()), 0);

	sliderQuan = createSlider(mainGui, 200, 9, 10, 180, 100, 1, AutoFeederTool::getInstance().getMaxThresholdValue(), 0);

	buttonQuan = createButton(mainGui, 60, 25, 285, 172, "SET", 0);

	labelFreq = createLabel(mainGui, "Feed frequency", 38, 200, 18, nullptr, 0);

	editBoxFreq = createEditBox(mainGui, 60, 25, 18, 220, 217, std::to_string((int)AutoFeederTool::getInstance().getMaxFoodPerSec()), 0);

	sliderFreq = createSlider(mainGui, 200, 9, 10, 225, 250, 1, AutoFeederTool::getInstance().getMaxFoodPerSec(), 0);

	buttonFreq = createButton(mainGui, 60, 25, 285, 217, "SET", 0);

	createLabel(mainGui, "Cells:", 10, 260, 18);

	createLabel(mainGui, "Food:", 10, 290, 18);

	labelCellsVar = createLabel(mainGui, std::to_string(Environment::getInstance().getAliveCellsCount()), 75, 260, 18);

	labelFoodVar = createLabel(mainGui, std::to_string(Environment::getInstance().getFoodCount()), 75, 290, 18);

	buttonPreview = createButton(mainGui, 70, 40, 5, 335, "Preview", 0);

	buttonCreate = createButton(mainGui, 70, 40, 75, 335, "Create");

	buttonModify = createButton(mainGui, 70, 40, 145, 335, "Modify");

	buttonInsert = createButton(mainGui, 70, 40, 215, 335, "Insert");

	buttonFeed = createButton(mainGui, 70, 40, 285, 335, "Feed");

	//CHILD WINDOWS

	newWindow = tgui::ChildWindow::create();
	newWindow->setRenderer(theme.getRenderer("ChildWindow"));
	newWindow->setSize(360, 160);
	newWindow->setPosition(window->getSize().x / 2 - 180, window->getSize().y / 2 - 80);
	newWindow->setTitle("Insert width and height of new simulation window");
	newWindow->setEnabled(0);
	newWindow->setVisible(0);
	previewGui->add(newWindow);

	saveWindow = tgui::ChildWindow::create();
	saveWindow->setRenderer(theme.getRenderer("ChildWindow"));
	saveWindow->setSize(360, 160);
	saveWindow->setPosition(window->getSize().x / 2 - 180, window->getSize().y / 2 - 80);
	saveWindow->setTitle("   Save");
	saveWindow->setEnabled(0);
	saveWindow->setVisible(0);
	previewGui->add(saveWindow);

	loadWindow = tgui::ChildWindow::create();
	loadWindow->setRenderer(theme.getRenderer("ChildWindow"));
	loadWindow->setSize(360, 160);
	loadWindow->setPosition(window->getSize().x / 2 - 180, window->getSize().y / 2 - 80);
	loadWindow->setTitle("Load");
	loadWindow->setEnabled(0);
	loadWindow->setVisible(0);
	previewGui->add(loadWindow);

	width = createEditBox(nullptr, 80, 25, 18, 70, 40, "Width");
	newWindow->add(width);

	height = createEditBox(nullptr, 80, 25, 18, 210, 40, "Height");
	newWindow->add(height);

	confirmN = createButton(nullptr, 70, 30, 100, 100, "Confirm");
	newWindow->add(confirmN);

	cancelN = createButton(nullptr, 70, 30, 190, 100, "Cancel");
	newWindow->add(cancelN);

	nameSave = createEditBox(nullptr, 120, 25, 18, 120, 40, "Name");
	saveWindow->add(nameSave);

	confirmS = createButton(nullptr, 70, 30, 100, 100, "Confirm");
	saveWindow->add(confirmS);

	cancelS = createButton(nullptr, 70, 30, 190, 100, "Cancel");
	saveWindow->add(cancelS);

	loadList = tgui::ListBox::create();
	loadList->setRenderer(theme.getRenderer("ListBox"));
	loadList->setSize(160, 72);
	loadList->setTextSize(18);
	loadList->setItemHeight(24);
	loadList->setPosition(100, 10);
	for (int i = 0; i < SaveManager::getInstance().getAvailableEnvSaves().size(); i++)
	{
		loadList->addItem(SaveManager::getInstance().getAvailableEnvSaves()[i]);
	}
	loadWindow->add(loadList);

	confirmL = createButton(nullptr, 70, 30, 100, 100, "Confirm");
	loadWindow->add(confirmL);

	cancelL = createButton(nullptr, 70, 30, 190, 100, "Cancel");
	loadWindow->add(cancelL);

	//GUI OFFSET
	constexpr int offset = 400;

	//CELL PREVIEW
	createLabel(previewGui, "Size", 10, 10 + offset, 18);
	sizeValLabel = createLabel(insertGui, "Max Size (20 - 50)", 10, 10 + offset, 18);
	modifyGui->add(sizeValLabel);
	createGui->add(sizeValLabel);

	sizeValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	sizeVal = createProgressBar(previewGui, 170, 20, 150, 12 + offset, 16, sizeValTT);
	widgetsPreview.push_back(sizeVal);

	createLabel(previewGui, "Speed", 10, 40 + offset, 18);
	speedValLabel = createLabel(insertGui, "Max Speed (0.1-2)", 10, 40 + offset, 18);
	modifyGui->add(speedValLabel);
	createGui->add(speedValLabel);

	speedValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	speedVal = createProgressBar(previewGui, 170, 20, 150, 42 + offset, 16, speedValTT);
	widgetsPreview.push_back(speedVal);

	createLabel(previewGui, "Age", 10, 70 + offset, 18);
	ageValLabel = createLabel(insertGui, "Max Age (1-100)", 10, 70 + offset, 18);
	modifyGui->add(ageValLabel);
	createGui->add(ageValLabel);

	ageValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	ageVal = createProgressBar(previewGui, 170, 20, 150, 72 + offset, 16, ageValTT);
	widgetsPreview.push_back(ageVal);

	createLabel(previewGui, "Fertility", 10, 100 + offset, 18);

	horninessValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	horninessVal = createProgressBar(previewGui, 170, 20, 150, 102 + offset, 16, horninessValTT);
	widgetsPreview.push_back(horninessVal);

	createLabel(previewGui, "Aggresion", 10, 130 + offset, 18);
	aggresionValLabel = createLabel(insertGui, "Aggresion (0-100)", 10, 100 + offset, 18);
	modifyGui->add(aggresionValLabel);
	createGui->add(aggresionValLabel);

	aggresionValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	aggresionVal = createProgressBar(previewGui, 170, 20, 150, 132 + offset, 16, aggresionValTT);
	widgetsPreview.push_back(aggresionVal);

	createLabel(previewGui, "Food level", 10, 160 + offset, 18);
	foodLevelValLabel = createLabel(insertGui, "Food limit (0-150)", 10, 130 + offset, 18);
	modifyGui->add(foodLevelValLabel);
	createGui->add(foodLevelValLabel);

	foodLevelValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	foodLevelVal = createProgressBar(previewGui, 170, 20, 150, 162 + offset, 16, foodLevelValTT);
	widgetsPreview.push_back(foodLevelVal);

	divisionThresholdTT = createLabel(previewGui, "Division Threshold", 0, 0, 18, nullptr, 1, "ToolTip");

	createLabel(previewGui, "Div. th", 10, 190 + offset, 18, divisionThresholdTT);
	divisionThresholdValLabel = createLabel(insertGui, "Div. th", 10, 160 + offset, 18, divisionThresholdTT);
	modifyGui->add(divisionThresholdValLabel);
	createGui->add(divisionThresholdValLabel);

	divisionThresholdVal = createProgressBar(previewGui, 70, 20, 200, 192 + offset, 16, nullptr);
	widgetsPreview.push_back(divisionThresholdVal);

	radarRangeTT = createLabel(previewGui, "Detection Range", 0, 0, 18, nullptr, 1, "ToolTip");

	createLabel(previewGui, "Detec. rg", 10, 220 + offset, 18, radarRangeTT);
	radarRangeValLabel = createLabel(insertGui, "Detec. rg", 10, 190 + offset, 18, radarRangeTT);
	modifyGui->add(radarRangeValLabel);
	createGui->add(radarRangeValLabel);

	radarRangeVal = createProgressBar(previewGui, 70, 20, 200, 222 + offset, 16, nullptr);
	widgetsPreview.push_back(radarRangeVal);

	//CELL CREATE
	createCellPtr = CellFactory::getCell(Cell::Type::Default);

	sizeC = createEditBox(createGui, 70, 20, 18, 200, 12 + offset, doubleToString(createCellPtr->getGenes().maxSize.get(), 2));

	speedC = createEditBox(createGui, 70, 20, 18, 200, 42 + offset, doubleToString(createCellPtr->getGenes().maxSpeed.get(), 2));

	ageC = createEditBox(createGui, 70, 20, 18, 200, 72 + offset, doubleToString(createCellPtr->getGenes().maxAge.get(), 2));

	aggresionC = createEditBox(createGui, 70, 20, 18, 200, 102 + offset, doubleToString(createCellPtr->getGenes().aggresion.get(), 2));

	foodLevelC = createEditBox(createGui, 70, 20, 18, 200, 132 + offset, doubleToString(createCellPtr->getGenes().foodLimit.get(), 2));

	divisionThresholdC = createEditBox(createGui, 70, 20, 18, 200, 162 + offset, doubleToString(createCellPtr->getGenes().divisionThreshold.get(), 2));

	radarRangeC = createEditBox(createGui, 70, 20, 18, 200, 192 + offset, doubleToString(createCellPtr->getGenes().radarRange.get(), 2));

	buttonCarnivoreC = createButton(createGui, 70, 30, 25, 240 + offset, "Carnivore");

	buttonOmnivoreC = createButton(createGui, 70, 30, 145, 240 + offset, "Omnivore", 0);

	buttonHerbivoreC = createButton(createGui, 70, 30, 265, 240 + offset, "Herbivore");

	nameC = createEditBox(createGui, 140, 26, 18, 110, 280 + offset, "Name");

	buttonCreateC = createButton(createGui, 70, 40, 105, 320 + offset, "Create");

	buttonSaveC = createButton(createGui, 70, 40, 185, 320 + offset, "Save");

	//CELL MODIFY
	sizeM = createEditBox(modifyGui, 70, 20, 18, 200, 12 + offset, "");
	widgetsModify.push_back(sizeM);

	speedM = createEditBox(modifyGui, 70, 20, 18, 200, 42 + offset, "");
	widgetsModify.push_back(speedM);

	ageM = createEditBox(modifyGui, 70, 20, 18, 200, 72 + offset, "");
	widgetsModify.push_back(ageM);

	aggresionM = createEditBox(modifyGui, 70, 20, 18, 200, 102 + offset, "");
	widgetsModify.push_back(aggresionM);

	foodLevelM = createEditBox(modifyGui, 70, 20, 18, 200, 132 + offset, "");
	widgetsModify.push_back(foodLevelM);

	divisionThresholdM = createEditBox(modifyGui, 70, 20, 18, 200, 162 + offset, "");
	widgetsModify.push_back(divisionThresholdM);

	radarRangeM = createEditBox(modifyGui, 70, 20, 18, 200, 192 + offset, "");
	widgetsModify.push_back(radarRangeM);

	buttonCarnivoreM = createButton(modifyGui, 70, 30, 25, 240 + offset, "Carnivore");

	buttonOmnivoreM = createButton(modifyGui, 70, 30, 145, 240 + offset, "Omnivore");

	buttonHerbivoreM = createButton(modifyGui, 70, 30, 265, 240 + offset, "Herbivore");

	nameM = createEditBox(modifyGui, 140, 26, 18, 110, 280 + offset, "Name");
	widgetsModify.push_back(nameM);

	buttonModifyM = createButton(modifyGui, 100, 40, 130, 320 + offset, "Modify");

	for (int i = 0; i < widgetsModify.size(); i++)
	{
		widgetsModify[i]->setAlignment(tgui::EditBox::Alignment::Left);
	}

	//CELL INSERT
	sizeValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	sizeValI = createProgressBar(insertGui, 70, 20, 200, 12 + offset, 16, sizeValTTI);

	speedValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	speedValI = createProgressBar(insertGui, 70, 20, 200, 42 + offset, 16, speedValTTI);

	ageValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	ageValI = createProgressBar(insertGui, 70, 20, 200, 72 + offset, 16, ageValTTI);

	aggresionValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	aggresionValI = createProgressBar(insertGui, 70, 20, 200, 102 + offset, 16, aggresionValTTI);

	foodLevelValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	foodLevelValI = createProgressBar(insertGui, 70, 20, 200, 132 + offset, 16, foodLevelValTTI);

	divisionThresholdTTI = createLabel(insertGui, "Division Threshold", 0, 0, 18, nullptr, 1, "ToolTip");

	divisionThresholdValI = createProgressBar(insertGui, 70, 20, 200, 162 + offset, 16, nullptr);

	radarRangeTTI = createLabel(insertGui, "Detection Range", 0, 0, 18, nullptr, 1, "ToolTip");

	radarRangeValI = createProgressBar(insertGui, 70, 20, 200, 192 + offset, 16, nullptr);

	listBoxI = createListBox(insertGui, 200, 120, 80, 270 + offset);

	//FEED

	createLabel(feedGui, "Radius", 75, 35 + offset, 18);

	editBoxRadius = createEditBox(feedGui, 60, 25, 18, 220, 52 + offset, std::to_string((int)AutoFeederTool::getInstance().getMaxThresholdValue()));

	sliderRadius = createSlider(feedGui, 200, 9, 10, 60 + offset, 100, 1, AutoFeederTool::getInstance().getMaxThresholdValue());

	buttonRadius = createButton(feedGui, 60, 25, 285, 52 + offset, "SET");

	createLabel(feedGui, "Frequency", 60, 100 + offset, 18);

	editBoxFreqF = createEditBox(feedGui, 60, 25, 18, 220, 117 + offset, std::to_string((int)AutoFeederTool::getInstance().getMaxFoodPerSec()));

	sliderFreqF = createSlider(feedGui, 200, 9, 10, 125 + offset, 250, 1, AutoFeederTool::getInstance().getMaxFoodPerSec());

	buttonFreqF = createButton(feedGui, 60, 25, 285, 117 + offset, "SET");

	//MOVE MENU
	menuBar->moveToFront();

	//EVENTS ENV
	sliderTemp->connect("ValueChanged", [&]()
	{
		Environment::getInstance().setTemperature(sliderTemp->getValue());
		if (editBoxTemp->getText() != "")
			editBoxTemp->setText("");
		editBoxTemp->setDefaultText(std::to_string((int)sliderTemp->getValue()));
	});

	buttonTemp->connect("pressed", [=]()
	{
		if (editBoxTemp->getText() != "")
		{
			sliderTemp->setValue(std::stoi(editBoxTemp->getText().toAnsiString()));
			editBoxTemp->setDefaultText(std::to_string((int)sliderTemp->getValue()));
			editBoxTemp->setText("");
		}
	});

	sliderRad->connect("ValueChanged", [&]()
	{
		Environment::getInstance().setRadiation(sliderRad->getValue());
		if (editBoxRad->getText() != "")
			editBoxRad->setText("");
		editBoxRad->setDefaultText(std::to_string((int)sliderRad->getValue()));
	});

	buttonRad->connect("pressed", [=]()
	{
		if (editBoxRad->getText() != "")
		{
			sliderRad->setValue(std::stoi(editBoxRad->getText().toAnsiString()));
			editBoxRad->setDefaultText(std::to_string((int)sliderRad->getValue()));
			editBoxRad->setText("");
		}
	});

	sliderQuan->connect("ValueChanged", [&]()
	{
		AutoFeederTool::getInstance().setMaxThresholdValue(sliderQuan->getValue());
		if (editBoxQuan->getText() != "")
			editBoxQuan->setText("");
		editBoxQuan->setDefaultText(std::to_string((int)sliderQuan->getValue()));
	});

	buttonQuan->connect("pressed", [=]()
	{
		if (editBoxQuan->getText() != "")
		{
			sliderQuan->setValue(std::stoi(editBoxQuan->getText().toAnsiString()));
			editBoxQuan->setDefaultText(std::to_string((int)sliderQuan->getValue()));
			editBoxQuan->setText("");
		}
	});

	sliderFreq->connect("ValueChanged", [&]()
	{
		AutoFeederTool::getInstance().setMaxFoodPerSec(sliderFreq->getValue());
		if (editBoxFreq->getText() != "")
			editBoxFreq->setText("");
		editBoxFreq->setDefaultText(std::to_string((int)sliderFreq->getValue()));
	});

	buttonFreq->connect("pressed", [=]()
	{
		if (editBoxFreq->getText() != "")
		{
			sliderFreq->setValue(std::stoi(editBoxFreq->getText().toAnsiString()));
			editBoxFreq->setDefaultText(std::to_string((int)sliderFreq->getValue()));
			editBoxFreq->setText("");
		}
	});

	buttonPreview->connect("pressed", [=]()
	{
		mode = 1;
		buttonPreview->setEnabled(0);
		buttonPreview->setInheritedOpacity(0.5);
		buttonCreate->setEnabled(1);
		buttonCreate->setInheritedOpacity(1);
		buttonModify->setEnabled(1);
		buttonModify->setInheritedOpacity(1);
		buttonInsert->setEnabled(1);
		buttonInsert->setInheritedOpacity(1);
		buttonFeed->setEnabled(1);
		buttonFeed->setInheritedOpacity(1);

		ToolManager::getInstance().setActiveTool(ToolManager::Tool::SelectionMovement);
	});

	buttonCreate->connect("pressed", [=]()
	{
		mode = 2;
		buttonCreate->setEnabled(0);
		buttonCreate->setInheritedOpacity(0.5);
		buttonPreview->setEnabled(1);
		buttonPreview->setInheritedOpacity(1);
		buttonModify->setEnabled(1);
		buttonModify->setInheritedOpacity(1);
		buttonInsert->setEnabled(1);
		buttonInsert->setInheritedOpacity(1);
		buttonFeed->setEnabled(1);
		buttonFeed->setInheritedOpacity(1);

		ToolManager::getInstance().setActiveTool(ToolManager::Tool::Insertion);
	});

	buttonModify->connect("pressed", [=]()
	{
		mode = 3;
		buttonModify->setEnabled(0);
		buttonModify->setInheritedOpacity(0.5);
		buttonPreview->setEnabled(1);
		buttonPreview->setInheritedOpacity(1);
		buttonCreate->setEnabled(1);
		buttonCreate->setInheritedOpacity(1);
		buttonInsert->setEnabled(1);
		buttonInsert->setInheritedOpacity(1);
		buttonFeed->setEnabled(1);
		buttonFeed->setInheritedOpacity(1);

		ToolManager::getInstance().setActiveTool(ToolManager::Tool::SelectionMovement);
	});

	buttonInsert->connect("pressed", [=]()
	{
		mode = 4;
		buttonInsert->setEnabled(0);
		buttonInsert->setInheritedOpacity(0.5);
		buttonPreview->setEnabled(1);
		buttonPreview->setInheritedOpacity(1);
		buttonCreate->setEnabled(1);
		buttonCreate->setInheritedOpacity(1);
		buttonModify->setEnabled(1);
		buttonModify->setInheritedOpacity(1);
		buttonFeed->setEnabled(1);
		buttonFeed->setInheritedOpacity(1);

		ToolManager::getInstance().setActiveTool(ToolManager::Tool::Insertion);
	});

	buttonFeed->connect("pressed", [=]()
	{
		mode = 5;
		buttonFeed->setEnabled(0);
		buttonFeed->setInheritedOpacity(0.5);
		buttonPreview->setEnabled(1);
		buttonPreview->setInheritedOpacity(1);
		buttonInsert->setEnabled(1);
		buttonInsert->setInheritedOpacity(1);
		buttonCreate->setEnabled(1);
		buttonCreate->setInheritedOpacity(1);
		buttonModify->setEnabled(1);
		buttonModify->setInheritedOpacity(1);

		ToolManager::getInstance().setActiveTool(ToolManager::Tool::Feeder);
	});

	checkBoxFeed->connect("checked", [=]()
	{
		labelQuan->setInheritedOpacity(1);
		editBoxQuan->setEnabled(1);
		editBoxQuan->setInheritedOpacity(1);
		sliderQuan->setEnabled(1);
		sliderQuan->setInheritedOpacity(1);
		buttonQuan->setEnabled(1);
		buttonQuan->setInheritedOpacity(1);
		labelFreq->setInheritedOpacity(1);
		editBoxFreq->setEnabled(1);
		editBoxFreq->setInheritedOpacity(1);
		sliderFreq->setEnabled(1);
		sliderFreq->setInheritedOpacity(1);
		buttonFreq->setEnabled(1);
		buttonFreq->setInheritedOpacity(1);
		AutoFeederTool::getInstance().setIsActive(true);
	});

	checkBoxFeed->connect("unchecked", [=]()
	{
		labelQuan->setInheritedOpacity(0.5);
		editBoxQuan->setEnabled(0);
		editBoxQuan->setInheritedOpacity(0.5);
		sliderQuan->setEnabled(0);
		sliderQuan->setInheritedOpacity(0.5);
		buttonQuan->setEnabled(0);
		buttonQuan->setInheritedOpacity(0.5);
		labelFreq->setInheritedOpacity(0.5);
		editBoxFreq->setEnabled(0);
		editBoxFreq->setInheritedOpacity(0.5);
		sliderFreq->setEnabled(0);
		sliderFreq->setInheritedOpacity(0.5);
		buttonFreq->setEnabled(0);
		buttonFreq->setInheritedOpacity(0.5);
		AutoFeederTool::getInstance().setIsActive(false);
	});

	auto checkValue = [](std::shared_ptr<tgui::EditBox> textBox, std::string geneName, DynamicRanged<double>& gene)->bool
	{
		std::regex number(RegexPattern::Double);
		std::string text = textBox->getText();
		if (text.empty())
			text = textBox->getDefaultText();
		if (std::regex_match(text, number))
		{
			double value = std::stod(text);
			if (value >= gene.getMin() && value <= gene.getMax())
			{
				gene = value;
			}
			else
			{
				textBox->setText("");
				MessagesManager::getInstance().append(geneName + " must be between " + doubleToString(gene.getMin(), 2) + " and " + doubleToString(gene.getMax(), 2) + ".");
				return false;
			}
		}
		else
		{
			textBox->setText("");
			MessagesManager::getInstance().append(geneName + " must be a real value.");
			return false;
		}
		return true;
	};

	buttonSaveC->connect("pressed", [=]()
	{
		std::vector<bool> checkResults;
		checkResults.push_back(checkValue(sizeC, "Max Size", createCellPtr->getGenes().maxSize));
		checkResults.push_back(checkValue(speedC, "Max Speed", createCellPtr->getGenes().maxSpeed));
		checkResults.push_back(checkValue(ageC, "Max Age", createCellPtr->getGenes().maxAge));
		checkResults.push_back(checkValue(foodLevelC, "Max Food Level", createCellPtr->getGenes().foodLimit));
		checkResults.push_back(checkValue(aggresionC, "Aggresion", createCellPtr->getGenes().aggresion));
		checkResults.push_back(checkValue(divisionThresholdC, "Max Division Threshold", createCellPtr->getGenes().divisionThreshold));
		checkResults.push_back(checkValue(radarRangeC, "Max Size", createCellPtr->getGenes().radarRange));

		createCellPtr->getGenes().type = *typeC;

		std::regex word(RegexPattern::Word);
		std::string text = nameC->getText();
		if (std::regex_match(text, word))
		{
			createCellPtr->setName(text);
			checkResults.push_back(true);
		}
		else
		{
			nameC->setText(createCellPtr->getName());
			MessagesManager::getInstance().append("Cell Name must consist of letters only.");
			checkResults.push_back(false);
		}

		if (std::all_of(checkResults.begin(), checkResults.end(), [&](auto r) {return r == true; }))
		{
			auto cellNames = SaveManager::getInstance().getAvailableCellSaves();
			if (std::all_of(cellNames.begin(), cellNames.end(), [&](auto name)->bool { return name != nameC->getText(); }))
			{
				listBoxI->addItem(nameC->getText());
				SaveManager::getInstance().saveCellToFile(createCellPtr, nameC->getText());
				MessagesManager::getInstance().append("Cell saved.");
			}
			else
			{
				MessagesManager::getInstance().append("Cell name exists.");
			}
		}
	});

	buttonCreateC->connect("pressed", [=]()
	{
		std::vector<bool> checkResults;
		checkResults.push_back(checkValue(sizeC, "Max Size", createCellPtr->getGenes().maxSize));
		checkResults.push_back(checkValue(speedC, "Max Speed", createCellPtr->getGenes().maxSpeed));
		checkResults.push_back(checkValue(ageC, "Max Age", createCellPtr->getGenes().maxAge));
		checkResults.push_back(checkValue(aggresionC, "Aggresion", createCellPtr->getGenes().aggresion));
		checkResults.push_back(checkValue(foodLevelC, "Max Food Level", createCellPtr->getGenes().foodLimit));
		checkResults.push_back(checkValue(divisionThresholdC, "Max Division Threshold", createCellPtr->getGenes().divisionThreshold));
		checkResults.push_back(checkValue(radarRangeC, "Max Size", createCellPtr->getGenes().radarRange));

		if (std::all_of(checkResults.begin(), checkResults.end(), [&](auto r) {return r == true; }))
		{
			CellInsertionTool::getInstance().setCellBlueprint(createCellPtr);
		}
	});

	buttonModifyM->connect("pressed", [=]()
	{
		std::vector<bool> checkResults;
		checkResults.push_back(checkValue(sizeC, "Max Size", selectedCellPtr->getGenes().maxSize));
		checkResults.push_back(checkValue(speedC, "Max Speed", selectedCellPtr->getGenes().maxSpeed));
		checkResults.push_back(checkValue(ageC, "Max Age", selectedCellPtr->getGenes().maxAge));
		checkResults.push_back(checkValue(foodLevelC, "Max Food Level", selectedCellPtr->getGenes().foodLimit));
		checkResults.push_back(checkValue(divisionThresholdC, "Max Division Threshold", selectedCellPtr->getGenes().divisionThreshold));
		checkResults.push_back(checkValue(radarRangeC, "Max Size", selectedCellPtr->getGenes().radarRange));
		checkResults.push_back(checkValue(aggresionC, "Aggresion", createCellPtr->getGenes().aggresion));

		if (std::all_of(checkResults.begin(), checkResults.end(), [&](auto r) {return r == true; }))
		{
			CellSelectionTool::getInstance().getSelectedCell()->getGenes() = selectedCellPtr->getGenes();
		}
	});

	buttonCarnivoreC->connect("pressed", [=]()
	{
		*typeC = 2;
		buttonCarnivoreC->setEnabled(0);
		buttonCarnivoreC->setInheritedOpacity(0.5);
		buttonOmnivoreC->setEnabled(1);
		buttonOmnivoreC->setInheritedOpacity(1);
		buttonHerbivoreC->setEnabled(1);
		buttonHerbivoreC->setInheritedOpacity(1);

		createCellPtr->getGenes().type = 2;
		CellInsertionTool::getInstance().setCellBlueprint(createCellPtr);
	});

	buttonOmnivoreC->connect("pressed", [=]()
	{
		*typeC = 0;
		buttonOmnivoreC->setEnabled(0);
		buttonOmnivoreC->setInheritedOpacity(0.5);
		buttonCarnivoreC->setEnabled(1);
		buttonCarnivoreC->setInheritedOpacity(1);
		buttonHerbivoreC->setEnabled(1);
		buttonHerbivoreC->setInheritedOpacity(1);

		createCellPtr->getGenes().type = 0;
		CellInsertionTool::getInstance().setCellBlueprint(createCellPtr);
	});

	buttonHerbivoreC->connect("pressed", [=]()
	{
		*typeC = 1;
		buttonHerbivoreC->setEnabled(0);
		buttonHerbivoreC->setInheritedOpacity(0.5);
		buttonCarnivoreC->setEnabled(1);
		buttonCarnivoreC->setInheritedOpacity(1);
		buttonOmnivoreC->setEnabled(1);
		buttonOmnivoreC->setInheritedOpacity(1);

		createCellPtr->getGenes().type = 1;
		CellInsertionTool::getInstance().setCellBlueprint(createCellPtr);
	});

	buttonCarnivoreM->connect("pressed", [=]()
	{
		typeM = 1;
		buttonCarnivoreM->setEnabled(0);
		buttonCarnivoreM->setInheritedOpacity(0.5);
		buttonOmnivoreM->setEnabled(1);
		buttonOmnivoreM->setInheritedOpacity(1);
		buttonHerbivoreM->setEnabled(1);
		buttonHerbivoreM->setInheritedOpacity(1);
	});

	buttonOmnivoreM->connect("pressed", [=]()
	{
		typeM = 2;
		buttonOmnivoreM->setEnabled(0);
		buttonOmnivoreM->setInheritedOpacity(0.5);
		buttonCarnivoreM->setEnabled(1);
		buttonCarnivoreM->setInheritedOpacity(1);
		buttonHerbivoreM->setEnabled(1);
		buttonHerbivoreM->setInheritedOpacity(1);
	});

	buttonHerbivoreM->connect("pressed", [=]()
	{
		typeM = 3;
		buttonHerbivoreM->setEnabled(0);
		buttonHerbivoreM->setInheritedOpacity(0.5);
		buttonCarnivoreM->setEnabled(1);
		buttonCarnivoreM->setInheritedOpacity(1);
		buttonOmnivoreM->setEnabled(1);
		buttonOmnivoreM->setInheritedOpacity(1);
	});

	listBoxI->connect("ItemSelected", [=]()
	{
		listBoxI->getSelectedItem();
	});
	listBoxI->connect("DoubleClicked", [=]()
	{
		listBoxI->getSelectedItem();
	});
}

void GUIManager::handleEvent(sf::Event & e)
{
	if (mainGui != nullptr)
		mainGui->handleEvent(e);
	if (previewGui != nullptr && mode == 1)
		previewGui->handleEvent(e);
	if (createGui != nullptr && mode == 2)
		createGui->handleEvent(e);
	if (modifyGui != nullptr && mode == 3)
		modifyGui->handleEvent(e);
	if (insertGui != nullptr && mode == 4)
		insertGui->handleEvent(e);
	if (feedGui != nullptr && mode == 5)
		feedGui->handleEvent(e);
}

void GUIManager::update()
{
	MessagesManager::getInstance().update();

	auto view = window->getView();
	auto xFactor = view.getSize().x / window->getSize().x;
	auto yFactor = view.getSize().y / window->getSize().y;

	// gui panel position = {0,0}
	sf::FloatRect guiCollisionRect{ (view.getCenter().x - view.getSize().x / 2), (view.getCenter().y - view.getSize().y / 2), background.getSize().x*xFactor, background.getSize().y*yFactor };

	if (guiCollisionRect.contains(CellSimMouse::getPosition()))
	{
		CellSimMouse::setWheelDelta(0);
		ToolManager::getInstance().disable();
	}
	else
	{
		ToolManager::getInstance().enable();
	}

	selectedCellPtr = CellSelectionTool::getInstance().getSelectedCellCopy();
	auto cell = selectedCellPtr;

	//ENV SETTINGS
	labelCellsVar->setText(std::to_string(Environment::getInstance().getAliveCellsCount()));
	labelFoodVar->setText(std::to_string(Environment::getInstance().getFoodCount()));

	//CELL PREVIEW
	if (cell != nullptr)
	{
		setVisible(widgetsPreview, 1);
		//size
		updateValues(sizeValTT, sizeVal, "Min: " + doubleToString(cell->getGenes().maxSize.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().maxSize.get(), 2),
			doubleToString(cell->getSize(), 2), cell->getGenes().maxSize.get() * 100, cell->getGenes().maxSize.getMin() * 100, cell->getSize() * 100);
		sizeM->setDefaultText(doubleToString(cell->getGenes().maxSize.get(), 2));
		//speed
		updateValues(speedValTT, speedVal, "Min: " + doubleToString(cell->getGenes().maxSpeed.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().maxSpeed.get(), 2),
			doubleToString(cell->getCurrentSpeed(), 2), cell->getGenes().maxSpeed.get() * 100, cell->getGenes().maxSpeed.getMin() * 100, cell->getCurrentSpeed() * 100);
		speedM->setDefaultText(doubleToString(cell->getGenes().maxSpeed.get(), 2));
		//age
		updateValues(ageValTT, ageVal, "Min: " + doubleToString(cell->getGenes().maxAge.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().maxAge.get(), 2),
			doubleToString(cell->age, 2), cell->getGenes().maxAge.get() * 100, cell->getGenes().maxAge.getMin() * 100, cell->age * 100);
		ageM->setDefaultText(doubleToString(cell->getGenes().maxAge.get(), 2));
		//horniness
		updateValues(horninessValTT, horninessVal, "Min: " + doubleToString(cell->getHorniness().getMin(), 2) + "\nMax: " + doubleToString(cell->getHorniness().getMax(), 2),
			doubleToString(cell->getHorniness().get(), 2), cell->getHorniness().getMax() * 100, cell->getHorniness().getMin() * 100, cell->getHorniness().get() * 100);
		//aggresion
		updateValues(aggresionValTT, aggresionVal, "Min: " + doubleToString(cell->getGenes().aggresion.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().aggresion.getMax(), 2),
			doubleToString(cell->getGenes().aggresion.get(), 2), cell->getGenes().aggresion.getMax() * 100, cell->getGenes().aggresion.getMin() * 100, cell->getGenes().aggresion.get() * 100);
		aggresionM->setDefaultText(doubleToString(cell->getGenes().aggresion.get(), 2));
		//food level
		updateValues(foodLevelValTT, foodLevelVal, "Min: " + doubleToString(cell->getGenes().foodLimit.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().foodLimit.getMax(), 2),
			doubleToString(cell->getFoodLevel(), 2), cell->getGenes().foodLimit.get() * 100, cell->getGenes().foodLimit.getMin() * 100, cell->getFoodLevel() * 100);
		foodLevelM->setDefaultText(doubleToString(cell->getGenes().foodLimit.get(), 2));
		//divisionThreshold
		divisionThresholdVal->setText(doubleToString(cell->getGenes().divisionThreshold.get(), 2));
		divisionThresholdM->setDefaultText(doubleToString(cell->getGenes().divisionThreshold.get(), 2));
		//radarRange
		radarRangeVal->setText(doubleToString(cell->getGenes().radarRange.get(), 2));
		radarRangeM->setDefaultText(doubleToString(cell->getGenes().radarRange.get(), 2));

		switch (cell->getGenes().type.get())
		{
		case 0: 
			buttonOmnivoreM->setEnabled(0); buttonOmnivoreM->setInheritedOpacity(0.5); 
			buttonHerbivoreM->setEnabled(1); buttonHerbivoreM->setInheritedOpacity(1);
			buttonCarnivoreM->setEnabled(1); buttonCarnivoreM->setInheritedOpacity(1);
			break;

		case 1:
			buttonOmnivoreM->setEnabled(1); buttonOmnivoreM->setInheritedOpacity(1);
			buttonHerbivoreM->setEnabled(0); buttonHerbivoreM->setInheritedOpacity(0.5);
			buttonCarnivoreM->setEnabled(1); buttonCarnivoreM->setInheritedOpacity(1);
			break;

		case 2: 
			buttonOmnivoreM->setEnabled(1); buttonOmnivoreM->setInheritedOpacity(1);
			buttonHerbivoreM->setEnabled(1); buttonHerbivoreM->setInheritedOpacity(1);
			buttonCarnivoreM->setEnabled(0); buttonCarnivoreM->setInheritedOpacity(0.5); 
			break;
		}

		cell->setPosition(sf::Vector2f(175, 900));
		auto factor = cell->getOutlineThickness() / cell->getSize();
		auto typeShapeFactor = cell->getTypeShape().getOutlineThickness() / cell->getTypeShape().getRadius();
		cell->setOutlineThickness(150 * factor);
		cell->setSize(150);
		cell->setRotation(0);
		cell->getTypeShape().setOutlineThickness(150 / 2 * typeShapeFactor);
	}
	else
	{
		setVisible(widgetsPreview, 0);
		for (int i = 0; i < widgetsModify.size(); i++)
		{
			widgetsModify[i]->setDefaultText("");
			widgetsModify[i]->setText("");
		}
	}
}

void GUIManager::draw()
{
	auto defaultView = window->getView();
	window->setView(mainGui->getView());

	window->draw(background);

	if (mainGui != nullptr)
		mainGui->draw();
	switch (mode)
	{
	case 1: previewGui->draw(); break;
	case 2: createGui->draw(); break;
	case 3: modifyGui->draw(); break;
	case 4: insertGui->draw(); break;
	case 5: feedGui->draw(); break;
	}

	if (selectedCellPtr != nullptr)
	{
		if (mode == 1)
			window->draw(*selectedCellPtr);
	}

	MessagesManager::getInstance().draw(window);

	window->setView(defaultView);
}

