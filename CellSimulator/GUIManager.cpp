#include "GUIManager.h"
#include "Environment.h"
#include "AutoFeederTool.h"
#include "CellSelectionTool.h"
#include "DoubleToString.h"
#include "MessagesManager.h"

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
	if (!enabled)
	{
		EditBox->setEnabled(enabled);
		EditBox->setInheritedOpacity(0.5);
	}
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
	MenuBar->addMenuItem("Simulation", "Load");
	MenuBar->addMenuItem("Simulation", "Save");
	MenuBar->addMenuItem("Simulation", "Random");
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
	ListBox->setItemHeight(24);
	ListBox->setPosition(x, y);
	ListBox->addItem("Example 1");
	ListBox->addItem("Example 2");
	ListBox->addItem("Example 3");
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

GUIManager::GUIManager()
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


	//GUI OFFSET
	constexpr int offset = 400;

	//CELL PREVIEW
	createLabel(previewGui, "Size", 10, 10 + offset, 18);

	sizeValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	sizeVal = createProgressBar(previewGui, 170, 20, 150, 9 + offset, 16, sizeValTT);
	widgetsPreview.push_back(sizeVal);

	createLabel(previewGui, "Speed", 10, 40 + offset, 18);

	speedValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	speedVal = createProgressBar(previewGui, 170, 20, 150, 39 + offset, 16, speedValTT);
	widgetsPreview.push_back(speedVal);

	createLabel(previewGui, "Age", 10, 70 + offset, 18);

	ageValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	ageVal = createProgressBar(previewGui, 170, 20, 150, 69 + offset, 16, ageValTT);
	widgetsPreview.push_back(ageVal);

	createLabel(previewGui, "Fertility", 10, 100 + offset, 18);

	horninessValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	horninessVal = createProgressBar(previewGui, 170, 20, 150, 99 + offset, 16, horninessValTT);
	widgetsPreview.push_back(horninessVal);

	createLabel(previewGui, "Aggresion", 10, 130 + offset, 18);

	aggresionValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	aggresionVal = createProgressBar(previewGui, 170, 20, 150, 129 + offset, 16, aggresionValTT);
	widgetsPreview.push_back(aggresionVal);

	createLabel(previewGui, "Food level", 10, 160 + offset, 18);

	foodLevelValTT = createLabel(previewGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	foodLevelVal = createProgressBar(previewGui, 170, 20, 150, 159 + offset, 16, foodLevelValTT);
	widgetsPreview.push_back(foodLevelVal);

	divisionThresholdTT = createLabel(previewGui, "Division Threshold", 0, 0, 18, nullptr, 1, "ToolTip");

	createLabel(previewGui, "Div. th", 10, 190 + offset, 18, divisionThresholdTT);

	divisionThresholdVal = createTextBox(previewGui, 60, 20, 205, 189 + offset, 16);
	widgetsPreview.push_back(divisionThresholdVal);

	radarRangeTT = createLabel(previewGui, "Detection Range", 0, 0, 18, nullptr, 1, "ToolTip");

	createLabel(previewGui, "Detec. rg", 10, 220 + offset, 18, radarRangeTT);

	radarRangeVal = createTextBox(previewGui, 70, 20, 200, 219 + offset, 16);
	widgetsPreview.push_back(radarRangeVal);

	//CELL INSERT
	createLabel(insertGui, "Size", 10, 10 + offset, 18);

	sizeValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	sizeValI = createProgressBar(insertGui, 170, 20, 150, 9 + offset, 16, sizeValTTI);

	createLabel(insertGui, "Speed", 10, 40 + offset, 18);

	speedValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	speedValI = createProgressBar(insertGui, 170, 20, 150, 39 + offset, 16, speedValTTI);

	createLabel(insertGui, "Age", 10, 70 + offset, 18);

	ageValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	ageValI = createProgressBar(insertGui, 170, 20, 150, 69 + offset, 16, ageValTTI);

	createLabel(insertGui, "Fertility", 10, 100 + offset, 18);

	horninessValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	horninessValI = createProgressBar(insertGui, 170, 20, 150, 99 + offset, 16, horninessValTTI);

	createLabel(insertGui, "Aggresion", 10, 130 + offset, 18);

	aggresionValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	aggresionValI = createProgressBar(insertGui, 170, 20, 150, 129 + offset, 16, aggresionValTTI);

	createLabel(insertGui, "Food level", 10, 160 + offset, 18);

	foodLevelValTTI = createLabel(insertGui, "", 0, 0, 18, nullptr, 1, "ToolTip");

	foodLevelValI = createProgressBar(insertGui, 170, 20, 150, 159 + offset, 16, foodLevelValTTI);

	divisionThresholdTTI = createLabel(insertGui, "Division Threshold", 0, 0, 18, nullptr, 1, "ToolTip");

	createLabel(insertGui, "Div. th", 10, 190 + offset, 18, divisionThresholdTTI);

	divisionThresholdValI = createTextBox(insertGui, 60, 20, 205, 189 + offset, 16);

	radarRangeTTI = createLabel(insertGui, "Detection Range", 0, 0, 18, nullptr, 1, "ToolTip");

	createLabel(insertGui, "Detec. rg", 10, 220 + offset, 18, radarRangeTTI);

	radarRangeValI = createTextBox(insertGui, 70, 20, 200, 219 + offset, 16);

	listBoxI = createListBox(insertGui, 160, 72, 100, 270 + offset);

	buttonInsertI = createButton(insertGui, 80, 40, 140, 370 + offset, "Insert");

	//FEED

	createLabel(feedGui, "Radius", 75, 35+offset, 18);

	editBoxRadius = createEditBox(feedGui, 60, 25, 18, 220, 52+offset, std::to_string((int)AutoFeederTool::getInstance().getMaxThresholdValue()));

	sliderRadius = createSlider(feedGui, 200, 9, 10, 60+ offset, 100, 1, AutoFeederTool::getInstance().getMaxThresholdValue());

	buttonRadius = createButton(feedGui, 60, 25, 285, 52+ offset, "SET");

	createLabel(feedGui, "Frequency", 60, 100+ offset, 18);

	editBoxFreqF = createEditBox(feedGui, 60, 25, 18, 220, 117+ offset, std::to_string((int)AutoFeederTool::getInstance().getMaxFoodPerSec()));

	sliderFreqF = createSlider(feedGui, 200, 9, 10, 125 + offset, 250, 1, AutoFeederTool::getInstance().getMaxFoodPerSec());

	buttonFreqF = createButton(feedGui, 60, 25, 285, 117+ offset, "SET");

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
		buttonInsert->setEnabled(1);
		buttonInsert->setInheritedOpacity(1);
		buttonFeed->setEnabled(1);
		buttonFeed->setInheritedOpacity(1);
	});

	buttonInsert->connect("pressed", [=]()
	{
		mode = 4;
		buttonInsert->setEnabled(0);
		buttonInsert->setInheritedOpacity(0.5);
		buttonPreview->setEnabled(1);
		buttonPreview->setInheritedOpacity(1);
		buttonFeed->setEnabled(1);
		buttonFeed->setInheritedOpacity(1);
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
}

void GUIManager::handleEvent(sf::Event & e)
{
	if (mainGui != nullptr)
		mainGui->handleEvent(e);
	if (previewGui != nullptr)
		previewGui->handleEvent(e);
	if (createGui != nullptr)
		createGui->handleEvent(e);
	if (modifyGui != nullptr)
		modifyGui->handleEvent(e);
	if (insertGui != nullptr)
		insertGui->handleEvent(e);
	if (feedGui != nullptr)
		feedGui->handleEvent(e);
}

void GUIManager::update()
{
	MessagesManager::getInstance().update();

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
		//speed
		updateValues(speedValTT, speedVal, "Min: " + doubleToString(cell->getGenes().maxSpeed.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().maxSpeed.get(), 2),
			doubleToString(cell->getCurrentSpeed(), 2), cell->getGenes().maxSpeed.get() * 100, cell->getGenes().maxSpeed.getMin() * 100, cell->getCurrentSpeed() * 100);
		//age
		updateValues(ageValTT, ageVal, "Min: " + doubleToString(cell->getGenes().maxAge.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().maxAge.get(), 2),
			doubleToString(cell->age, 2), cell->getGenes().maxAge.get() * 100, cell->getGenes().maxAge.getMin() * 100, cell->age * 100);
		//horniness
		updateValues(horninessValTT, horninessVal, "Min: " + doubleToString(cell->getHorniness().getMin(), 2) + "\nMax: " + doubleToString(cell->getHorniness().getMax(), 2),
			doubleToString(cell->getHorniness().get(), 2), cell->getHorniness().getMax() * 100, cell->getHorniness().getMin() * 100, cell->getHorniness().get() * 100);
		//aggresion
		updateValues(aggresionValTT, aggresionVal, "Min: " + doubleToString(cell->getGenes().aggresion.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().aggresion.getMax(), 2),
			doubleToString(cell->getGenes().aggresion.get(), 2), cell->getGenes().aggresion.getMax() * 100, cell->getGenes().aggresion.getMin() * 100, cell->getGenes().aggresion.get() * 100);
		//food level
		updateValues(foodLevelValTT, foodLevelVal, "Min: " + doubleToString(cell->getGenes().foodLimit.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().foodLimit.getMax(), 2),
			doubleToString(cell->getFoodLevel(), 2), cell->getGenes().foodLimit.get() * 100, cell->getGenes().foodLimit.getMin() * 100, cell->getFoodLevel() * 100);
		//divisionThreshold
		divisionThresholdVal->setText(" " + doubleToString(cell->getGenes().divisionThreshold.get(), 2));
		//radarRange
		radarRangeVal->setText(" " + doubleToString(cell->getGenes().radarRange.get(), 2));

		cell->setPosition(sf::Vector2f(175, 900));
		auto factor = cell->getOutlineThickness() / cell->getSize();
		cell->setOutlineThickness(150 * factor);
		cell->setSize(150);
		cell->setRotation(0);
	}
	else
	{
		setVisible(widgetsPreview, 0);
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
		if(mode==1)
		window->draw(*selectedCellPtr);
	}

	MessagesManager::getInstance().draw(window);

	window->setView(defaultView);
}

