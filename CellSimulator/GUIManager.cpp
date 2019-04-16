#include "GUIManager.h"
#include "Environment.h"
#include "AutoFeederTool.h"
#include "CellSelectionTool.h"
#include "DoubleToString.h"
#include "MessagesManager.h"

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
	gui = std::make_shared<tgui::Gui>(*window);
	theme.load("../../CellSimulator/TGUI-0.8/themes/TransparentGrey.txt");

	background.setSize(sf::Vector2f( 360, window->getSize().y ));
	background.setFillColor(sf::Color(32, 32, 32, 128));
	background.setPosition({ 0,0 });
	background.setOutlineColor(sf::Color(32, 32, 16));
	background.setOutlineThickness(7);

	/*backgroundPanel = tgui::Panel::create();
	backgroundPanel->setRenderer(theme.getRenderer("Panel"));
	backgroundPanel->setSize(350, sf::VideoMode::getDesktopMode().height);
	backgroundPanel->setPosition({ 0,0 });
	gui->add(backgroundPanel);
*/

	//ENV SETTINGS
	labelTemp = tgui::Label::create();
	labelTemp->setRenderer(theme.getRenderer("Label"));
	labelTemp->setText("Temperature");
	labelTemp->setPosition(50, 15);
	labelTemp->setTextSize(18);
	gui->add(labelTemp);

	editBoxTemp = tgui::EditBox::create();
	editBoxTemp->setRenderer(theme.getRenderer("EditBox"));
	editBoxTemp->setSize(60, 25);
	editBoxTemp->setTextSize(18);
	editBoxTemp->setPosition(220, 32);
	editBoxTemp->setDefaultText(std::to_string((int)Environment::getInstance().getTemperature()));
	gui->add(editBoxTemp);

	sliderTemp = tgui::Slider::create();
	sliderTemp->setRenderer(theme.getRenderer("Slider"));
	sliderTemp->setPosition(10, 40);
	sliderTemp->setSize(200, 9);
	sliderTemp->setMaximum(100);
	sliderTemp->setMinimum(-100);
	sliderTemp->setValue(Environment::getInstance().getTemperature());
	gui->add(sliderTemp);

	buttonTemp = tgui::Button::create();
	buttonTemp->setRenderer(theme.getRenderer("Button"));
	buttonTemp->setPosition(285, 32);
	buttonTemp->setText("SET");
	buttonTemp->setSize(60, 25);
	gui->add(buttonTemp);

	labelRad = tgui::Label::create();
	labelRad->setRenderer(theme.getRenderer("Label"));
	labelRad->setText("Radiation");
	labelRad->setPosition(70, 60);
	labelRad->setTextSize(18);
	gui->add(labelRad);

	editBoxRad = tgui::EditBox::create();
	editBoxRad->setRenderer(theme.getRenderer("EditBox"));
	editBoxRad->setSize(60, 25);
	editBoxRad->setTextSize(18);
	editBoxRad->setPosition(220, 77);
	editBoxRad->setDefaultText(std::to_string((int)Environment::getInstance().getRadiation()));
	gui->add(editBoxRad);

	sliderRad = tgui::Slider::create();
	sliderRad->setRenderer(theme.getRenderer("Slider"));
	sliderRad->setPosition(10, 85);
	sliderRad->setSize(200, 9);
	sliderRad->setMaximum(100);
	sliderRad->setMinimum(0);
	sliderRad->setValue(Environment::getInstance().getRadiation());
	gui->add(sliderRad);

	buttonRad = tgui::Button::create();
	buttonRad->setRenderer(theme.getRenderer("Button"));
	buttonRad->setPosition(285, 77);
	buttonRad->setText("SET");
	buttonRad->setSize(60, 25);
	gui->add(buttonRad);

	labelQuan = tgui::Label::create();
	labelQuan->setRenderer(theme.getRenderer("Label"));
	labelQuan->setText("Food limit [%]");
	labelQuan->setPosition(45, 125);
	labelQuan->setTextSize(18);
	labelQuan->setEnabled(0);
	labelQuan->setInheritedOpacity(0.5);
	gui->add(labelQuan);

	editBoxQuan = tgui::EditBox::create();
	editBoxQuan->setRenderer(theme.getRenderer("EditBox"));
	editBoxQuan->setSize(60, 25);
	editBoxQuan->setTextSize(18);
	editBoxQuan->setPosition(220, 142);
	editBoxQuan->setDefaultText(std::to_string((int)AutoFeederTool::getInstance().getMaxThresholdValue()));
	editBoxQuan->setEnabled(0);
	editBoxQuan->setInheritedOpacity(0.5);
	gui->add(editBoxQuan);

	sliderQuan = tgui::Slider::create();
	sliderQuan->setRenderer(theme.getRenderer("Slider"));
	sliderQuan->setPosition(10, 150);
	sliderQuan->setSize(200, 9);
	sliderQuan->setMaximum(100);
	sliderQuan->setMinimum(1);
	sliderQuan->setValue(AutoFeederTool::getInstance().getMaxThresholdValue());
	sliderQuan->setEnabled(0);
	sliderQuan->setInheritedOpacity(0.5);
	gui->add(sliderQuan);

	buttonQuan = tgui::Button::create();
	buttonQuan->setRenderer(theme.getRenderer("Button"));
	buttonQuan->setPosition(285, 142);
	buttonQuan->setText("SET");
	buttonQuan->setSize(60, 25);
	buttonQuan->setEnabled(0);
	buttonQuan->setInheritedOpacity(0.5);
	gui->add(buttonQuan);

	labelFreq = tgui::Label::create();
	labelFreq->setRenderer(theme.getRenderer("Label"));
	labelFreq->setText("Feed frequency");
	labelFreq->setPosition(38, 170);
	labelFreq->setTextSize(18);
	labelFreq->setEnabled(0);
	labelFreq->setInheritedOpacity(0.5);
	gui->add(labelFreq);

	editBoxFreq = tgui::EditBox::create();
	editBoxFreq->setRenderer(theme.getRenderer("EditBox"));
	editBoxFreq->setSize(60, 25);
	editBoxFreq->setTextSize(18);
	editBoxFreq->setPosition(220, 187);
	editBoxFreq->setDefaultText(std::to_string((int)AutoFeederTool::getInstance().getMaxFoodPerSec()));
	editBoxFreq->setEnabled(0);
	editBoxFreq->setInheritedOpacity(0.5);
	gui->add(editBoxFreq);

	sliderFreq = tgui::Slider::create();
	sliderFreq->setRenderer(theme.getRenderer("Slider"));
	sliderFreq->setPosition(10, 195);
	sliderFreq->setSize(200, 9);
	sliderFreq->setMaximum(250);
	sliderFreq->setMinimum(1);
	sliderFreq->setValue(AutoFeederTool::getInstance().getMaxFoodPerSec());
	sliderFreq->setEnabled(0);
	sliderFreq->setInheritedOpacity(0.5);
	gui->add(sliderFreq);

	buttonFreq = tgui::Button::create();
	buttonFreq->setRenderer(theme.getRenderer("Button"));
	buttonFreq->setPosition(285, 187);
	buttonFreq->setText("SET");
	buttonFreq->setSize(60, 25);
	buttonFreq->setEnabled(0);
	buttonFreq->setInheritedOpacity(0.5);
	gui->add(buttonFreq);

	buttonFeed = tgui::Button::create();
	buttonFeed->setRenderer(theme.getRenderer("Button"));
	buttonFeed->setPosition(75, 230);
	buttonFeed->setText("Feed");
	buttonFeed->setSize(100, 40);
	buttonFeed->setInheritedOpacity(1);
	gui->add(buttonFeed);

	buttonSelect = tgui::Button::create();
	buttonSelect->setRenderer(theme.getRenderer("Button"));
	buttonSelect->setPosition(180, 230);
	buttonSelect->setText("Select");
	buttonSelect->setSize(100, 40);
	buttonSelect->setInheritedOpacity(0.5);
	buttonSelect->setEnabled(0);
	gui->add(buttonSelect);

	checkBoxFeed = tgui::CheckBox::create();
	checkBoxFeed->setRenderer(theme.getRenderer("CheckBox"));
	checkBoxFeed->setPosition(75, 275);
	checkBoxFeed->setText("Auto-feed");
	checkBoxFeed->setSize(15, 15);
	checkBoxFeed->setTextSize(14);
	gui->add(checkBoxFeed);

	labelCells = tgui::Label::create();
	labelCells->setRenderer(theme.getRenderer("Label"));
	labelCells->setText("Cells:");
	labelCells->setPosition(10, 310);
	labelCells->setTextSize(18);
	gui->add(labelCells);

	labelFood = tgui::Label::create();
	labelFood->setRenderer(theme.getRenderer("Label"));
	labelFood->setText("Food:");
	labelFood->setPosition(10, 340);
	labelFood->setTextSize(18);
	gui->add(labelFood);

	labelCellsVar = tgui::Label::create();
	labelCellsVar->setRenderer(theme.getRenderer("Label"));
	labelCellsVar->setText(std::to_string(Environment::getInstance().getAliveCellsCount()));
	labelCellsVar->setPosition(75, 310);
	labelCellsVar->setTextSize(18);
	gui->add(labelCellsVar);

	labelFoodVar = tgui::Label::create();
	labelFoodVar->setRenderer(theme.getRenderer("Label"));
	labelFoodVar->setText(std::to_string(Environment::getInstance().getFoodCount()));
	labelFoodVar->setPosition(75, 340);
	labelFoodVar->setTextSize(18);
	gui->add(labelFoodVar);

	//wywo³anie eventów
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

	buttonSelect->connect("pressed", [=]()
	{
		buttonSelect->setEnabled(0);
		buttonSelect->setInheritedOpacity(0.5);
		buttonFeed->setEnabled(1);
		buttonFeed->setInheritedOpacity(1);
	});

	buttonFeed->connect("pressed", [=]()
	{
		buttonFeed->setEnabled(0);
		buttonFeed->setInheritedOpacity(0.5);
		buttonSelect->setEnabled(1);
		buttonSelect->setInheritedOpacity(1);
	});

	checkBoxFeed->connect("checked", [=]()
	{
		labelQuan->setEnabled(1);
		labelQuan->setInheritedOpacity(1);
		editBoxQuan->setEnabled(1);
		editBoxQuan->setInheritedOpacity(1);
		sliderQuan->setEnabled(1);
		sliderQuan->setInheritedOpacity(1);
		buttonQuan->setEnabled(1);
		buttonQuan->setInheritedOpacity(1);
		labelFreq->setEnabled(1);
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
		labelQuan->setEnabled(0);
		labelQuan->setInheritedOpacity(0.5);
		editBoxQuan->setEnabled(0);
		editBoxQuan->setInheritedOpacity(0.5);
		sliderQuan->setEnabled(0);
		sliderQuan->setInheritedOpacity(0.5);
		buttonQuan->setEnabled(0);
		buttonQuan->setInheritedOpacity(0.5);
		labelFreq->setEnabled(0);
		labelFreq->setInheritedOpacity(0.5);
		editBoxFreq->setEnabled(0);
		editBoxFreq->setInheritedOpacity(0.5);
		sliderFreq->setEnabled(0);
		sliderFreq->setInheritedOpacity(0.5);
		buttonFreq->setEnabled(0);
		buttonFreq->setInheritedOpacity(0.5);
		AutoFeederTool::getInstance().setIsActive(false);
	});

	constexpr int offset = 400;

	//CELL PREVIEW
	size = tgui::Label::create();
	size->setRenderer(theme.getRenderer("Label"));
	size->setText("Size");
	size->setPosition(10, 10 + offset);
	size->setTextSize(18);
	gui->add(size);

	sizeValTT = tgui::Label::create();
	sizeValTT->setRenderer(theme.getRenderer("ToolTip"));
	sizeValTT->setText("");
	sizeValTT->setPosition(0, 0);
	sizeValTT->setTextSize(18);

	sizeVal = tgui::ProgressBar::create();
	sizeVal->setRenderer(theme.getRenderer("ProgressBar"));
	sizeVal->setPosition(150, 9 + offset);
	sizeVal->setSize(170, 20);
	sizeVal->setTextSize(16);
	sizeVal->setVisible(0);
	sizeVal->setToolTip(sizeValTT);
	gui->add(sizeVal);

	speed = tgui::Label::create();
	speed->setRenderer(theme.getRenderer("Label"));
	speed->setText("Speed");
	speed->setPosition(10, 40 + offset);
	speed->setTextSize(18);
	gui->add(speed);

	speedValTT = tgui::Label::create();
	speedValTT->setRenderer(theme.getRenderer("ToolTip"));
	speedValTT->setText("");
	speedValTT->setPosition(0, 0);
	speedValTT->setTextSize(18);

	speedVal = tgui::ProgressBar::create();
	speedVal->setRenderer(theme.getRenderer("ProgressBar"));
	speedVal->setPosition(150, 39 + offset);
	speedVal->setSize(170, 20);
	speedVal->setTextSize(16);
	speedVal->setVisible(0);
	speedVal->setToolTip(speedValTT);
	gui->add(speedVal);

	age = tgui::Label::create();
	age->setRenderer(theme.getRenderer("Label"));
	age->setText("Age");
	age->setPosition(10, 70 + offset);
	age->setTextSize(18);
	gui->add(age);

	ageValTT = tgui::Label::create();
	ageValTT->setRenderer(theme.getRenderer("ToolTip"));
	ageValTT->setText("");
	ageValTT->setPosition(0, 0);
	ageValTT->setTextSize(18);

	ageVal = tgui::ProgressBar::create();
	ageVal->setRenderer(theme.getRenderer("ProgressBar"));
	ageVal->setPosition(150, 69 + offset);
	ageVal->setSize(170, 20);
	ageVal->setTextSize(16);
	ageVal->setVisible(0);
	ageVal->setToolTip(ageValTT);
	gui->add(ageVal);

	horniness = tgui::Label::create();
	horniness->setRenderer(theme.getRenderer("Label"));
	horniness->setText("Fertility");
	horniness->setPosition(10, 100 + offset);
	horniness->setTextSize(18);
	gui->add(horniness);

	horninessValTT = tgui::Label::create();
	horninessValTT->setRenderer(theme.getRenderer("ToolTip"));
	horninessValTT->setText("");
	horninessValTT->setPosition(0, 0);
	horninessValTT->setTextSize(18);

	horninessVal = tgui::ProgressBar::create();
	horninessVal->setRenderer(theme.getRenderer("ProgressBar"));
	horninessVal->setPosition(150, 99 + offset);
	horninessVal->setSize(170, 20);
	horninessVal->setTextSize(16);
	horninessVal->setVisible(0);
	horninessVal->setToolTip(horninessValTT);
	gui->add(horninessVal);

	aggresion = tgui::Label::create();
	aggresion->setRenderer(theme.getRenderer("Label"));
	aggresion->setText("Aggresion");
	aggresion->setPosition(10, 130 + offset);
	aggresion->setTextSize(18);
	gui->add(aggresion);

	aggresionValTT = tgui::Label::create();
	aggresionValTT->setRenderer(theme.getRenderer("ToolTip"));
	aggresionValTT->setText("");
	aggresionValTT->setPosition(0, 0 + offset);
	aggresionValTT->setTextSize(18);

	aggresionVal = tgui::ProgressBar::create();
	aggresionVal->setRenderer(theme.getRenderer("ProgressBar"));
	aggresionVal->setPosition(150, 129 + offset);
	aggresionVal->setSize(170, 20);
	aggresionVal->setTextSize(16);
	aggresionVal->setVisible(0);
	aggresionVal->setToolTip(aggresionValTT);
	gui->add(aggresionVal);

	foodLevel = tgui::Label::create();
	foodLevel->setRenderer(theme.getRenderer("Label"));
	foodLevel->setText("Food level");
	foodLevel->setPosition(10, 160 + offset);
	foodLevel->setTextSize(18);
	gui->add(foodLevel);

	foodLevelValTT = tgui::Label::create();
	foodLevelValTT->setRenderer(theme.getRenderer("ToolTip"));
	foodLevelValTT->setText("");
	foodLevelValTT->setPosition(0, 0);
	foodLevelValTT->setTextSize(18);

	foodLevelVal = tgui::ProgressBar::create();
	foodLevelVal->setRenderer(theme.getRenderer("ProgressBar"));
	foodLevelVal->setPosition(150, 159 + offset);
	foodLevelVal->setSize(170, 20);
	foodLevelVal->setTextSize(16);
	foodLevelVal->setVisible(0);
	foodLevelVal->setToolTip(foodLevelValTT);
	gui->add(foodLevelVal);

	divisionThresholdTT = tgui::Label::create();
	divisionThresholdTT->setRenderer(theme.getRenderer("ToolTip"));
	divisionThresholdTT->setText("Division Threshold");
	divisionThresholdTT->setPosition(0, 0);
	divisionThresholdTT->setTextSize(18);

	divisionThreshold = tgui::Label::create();
	divisionThreshold->setRenderer(theme.getRenderer("Label"));
	divisionThreshold->setText("Div. th");
	divisionThreshold->setPosition(10, 190 + offset);
	divisionThreshold->setTextSize(18);
	divisionThreshold->setToolTip(divisionThresholdTT);
	gui->add(divisionThreshold);

	divisionThresholdVal = tgui::TextBox::create();
	divisionThresholdVal->setRenderer(theme.getRenderer("TextBox"));
	divisionThresholdVal->setPosition(210, 189 + offset);
	divisionThresholdVal->setSize(50, 20);
	divisionThresholdVal->setTextSize(16);
	divisionThresholdVal->setVisible(0);
	divisionThresholdVal->setReadOnly(1);
	divisionThresholdVal->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
	gui->add(divisionThresholdVal);

	radarRangeTT = tgui::Label::create();
	radarRangeTT->setRenderer(theme.getRenderer("ToolTip"));
	radarRangeTT->setText("Detection Range");
	radarRangeTT->setPosition(0, 0);
	radarRangeTT->setTextSize(18);

	radarRange = tgui::Label::create();
	radarRange->setRenderer(theme.getRenderer("Label"));
	radarRange->setText("Detec. rg");
	radarRange->setPosition(10, 220 + offset);
	radarRange->setTextSize(18);
	radarRange->setToolTip(radarRangeTT);
	gui->add(radarRange);

	radarRangeVal = tgui::TextBox::create();
	radarRangeVal->setRenderer(theme.getRenderer("TextBox"));
	radarRangeVal->setPosition(210, 219 + offset);
	radarRangeVal->setSize(50, 20);
	radarRangeVal->setTextSize(16);
	radarRangeVal->setVisible(0);
	radarRangeVal->setReadOnly(1);
	radarRangeVal->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
	gui->add(radarRangeVal);
}

void GUIManager::handleEvent(sf::Event & e)
{
	if (gui != nullptr)
		gui->handleEvent(e);
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
		//size
		sizeValTT->setText("Min: " + doubleToString(cell->getGenes().maxSize.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().maxSize.get(), 2));
		sizeVal->setVisible(1);
		sizeVal->setText(doubleToString(cell->getSize(), 2));
		sizeVal->setMaximum(cell->getGenes().maxSize.get());
		sizeVal->setMinimum(cell->getGenes().maxSize.getMin());
		sizeVal->setValue(cell->getSize());
		//speed
		speedValTT->setText("Min: " + doubleToString(cell->getGenes().maxSpeed.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().maxSpeed.get(), 2));
		speedVal->setVisible(1);
		speedVal->setText(doubleToString(cell->getCurrentSpeed(), 2));
		speedVal->setMaximum(cell->getGenes().maxSpeed.get() * 100);
		speedVal->setMinimum(cell->getGenes().maxSpeed.getMin() * 100);
		speedVal->setValue(cell->getCurrentSpeed() * 100);
		//age
		ageValTT->setText("Min: " + doubleToString(cell->getGenes().maxAge.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().maxAge.get(), 2));
		ageVal->setVisible(1);
		ageVal->setText(doubleToString(cell->age, 2));
		ageVal->setMaximum(cell->getGenes().maxAge.get() * 100);
		ageVal->setMinimum(cell->getGenes().maxAge.getMin() * 100);
		ageVal->setValue(cell->age * 100);
		//horniness
		horninessValTT->setText("Min: " + doubleToString(cell->getHorniness().getMin(), 2) + "\nMax: " + doubleToString(cell->getHorniness().getMax(), 2));
		horninessVal->setVisible(1);
		horninessVal->setText(doubleToString(cell->getHorniness().get(), 2));
		horninessVal->setMaximum(cell->getHorniness().getMax() * 100);
		horninessVal->setMinimum(cell->getHorniness().getMin() * 100);
		horninessVal->setValue(cell->getHorniness().get() * 100);
		//aggresion
		aggresionValTT->setText("Min: " + doubleToString(cell->getGenes().aggresion.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().aggresion.getMax(), 2));
		aggresionVal->setVisible(1);
		aggresionVal->setText(doubleToString(cell->getGenes().aggresion.get(), 2));
		aggresionVal->setMaximum(cell->getGenes().aggresion.getMax() * 100);
		aggresionVal->setMinimum(cell->getGenes().aggresion.getMin() * 100);
		aggresionVal->setValue(cell->getGenes().aggresion.get() * 100);
		//food level
		foodLevelValTT->setText("Min: " + doubleToString(cell->getGenes().foodLimit.getMin(), 2) + "\nMax: " + doubleToString(cell->getGenes().foodLimit.getMax(), 2));
		foodLevelVal->setVisible(1);
		foodLevelVal->setText(doubleToString(cell->getFoodLevel(), 2));
		foodLevelVal->setMaximum(cell->getGenes().foodLimit.getMax() * 100);
		foodLevelVal->setMinimum(cell->getGenes().foodLimit.getMin() * 100);
		foodLevelVal->setValue(cell->getFoodLevel() * 100);
		//divisionThreshold
		divisionThresholdVal->setVisible(1);
		divisionThresholdVal->setText(" " + doubleToString(cell->getGenes().divisionThreshold.get(), 2));
		//radarRange
		radarRangeVal->setVisible(1);
		radarRangeVal->setText(" " + doubleToString(cell->getGenes().radarRange.get(), 2));

		cell->setPosition(sf::Vector2f(175, 900));
		cell->setSize(150);
		cell->setRotation(0);
	}
	else
	{
		sizeVal->setVisible(0);
		speedVal->setVisible(0);
		ageVal->setVisible(0);
		horninessVal->setVisible(0);
		aggresionVal->setVisible(0);
		foodLevelVal->setVisible(0);
		divisionThresholdVal->setVisible(0);
		radarRangeVal->setVisible(0);
	}
}

void GUIManager::draw()
{
	auto defaultView = window->getView();
	window->setView(gui->getView());

	window->draw(background);

	if (gui != nullptr)
		gui->draw();

	if (selectedCellPtr != nullptr)
	{
		window->draw(*selectedCellPtr);
	}

	MessagesManager::getInstance().draw(window);

	window->setView(defaultView);
}

