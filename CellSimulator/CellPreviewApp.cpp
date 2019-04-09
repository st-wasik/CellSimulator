#include "CellPreviewApp.h"
#include "CellSelectionTool.h"
#include "MainApp.h"
#include "Logger.h"
#include "DoubleToString.h"
#include <TGUI/TGUI.hpp>
#include <iostream>

CellPreviewApp::CellPreviewApp()
{
	window = std::make_shared<sf::RenderWindow>();
	windowVideoMode = sf::VideoMode(350, 768 / 2 - 5);
	windowTitle = "Cell Preview";

	Logger::log(windowTitle + " - build " + __DATE__ + " " + __TIME__);

	window->create(windowVideoMode, windowTitle, sf::Style::Titlebar);
	window->setFramerateLimit(60);

	gui = std::make_shared<tgui::Gui>(*window);

	theme.load("../../CellSimulator/TGUI-0.8/themes/TransparentGrey.txt");
}


CellPreviewApp::~CellPreviewApp()
{
}

CellPreviewApp & CellPreviewApp::getInstance()
{
	static CellPreviewApp instance;
	return instance;
}

void CellPreviewApp::configure()
{
	size = tgui::Label::create();
	size->setRenderer(theme.getRenderer("Label"));
	size->setText("Size");
	size->setPosition(10, 10);
	size->setTextSize(18);
	gui->add(size);

	sizeValTT = tgui::Label::create();
	sizeValTT->setRenderer(theme.getRenderer("ToolTip"));
	sizeValTT->setText("");
	sizeValTT->setPosition(0,0);
	sizeValTT->setTextSize(18);

	sizeVal = tgui::ProgressBar::create();
	sizeVal->setRenderer(theme.getRenderer("ProgressBar"));
	sizeVal->setPosition(150, 9);
	sizeVal->setSize(170, 20);
	sizeVal->setTextSize(16);
	sizeVal->setVisible(0);
	sizeVal->setToolTip(sizeValTT);
	gui->add(sizeVal);

	speed = tgui::Label::create();
	speed->setRenderer(theme.getRenderer("Label"));
	speed->setText("Speed");
	speed->setPosition(10, 40);
	speed->setTextSize(18);
	gui->add(speed);

	speedValTT = tgui::Label::create();
	speedValTT->setRenderer(theme.getRenderer("ToolTip"));
	speedValTT->setText("");
	speedValTT->setPosition(0, 0);
	speedValTT->setTextSize(18);

	speedVal = tgui::ProgressBar::create();
	speedVal->setRenderer(theme.getRenderer("ProgressBar"));
	speedVal->setPosition(150, 39);
	speedVal->setSize(170, 20);
	speedVal->setTextSize(16);
	speedVal->setVisible(0);
	speedVal->setToolTip(speedValTT);
	gui->add(speedVal);

	age = tgui::Label::create();
	age->setRenderer(theme.getRenderer("Label"));
	age->setText("Age");
	age->setPosition(10, 70);
	age->setTextSize(18);
	gui->add(age);

	ageValTT = tgui::Label::create();
	ageValTT->setRenderer(theme.getRenderer("ToolTip"));
	ageValTT->setText("");
	ageValTT->setPosition(0, 0);
	ageValTT->setTextSize(18);

	ageVal = tgui::ProgressBar::create();
	ageVal->setRenderer(theme.getRenderer("ProgressBar"));
	ageVal->setPosition(150, 69);
	ageVal->setSize(170, 20);
	ageVal->setTextSize(16);
	ageVal->setVisible(0);
	ageVal->setToolTip(ageValTT);
	gui->add(ageVal);

	horniness = tgui::Label::create();
	horniness->setRenderer(theme.getRenderer("Label"));
	horniness->setText("Fertility");
	horniness->setPosition(10, 100);
	horniness->setTextSize(18);
	gui->add(horniness);

	horninessValTT = tgui::Label::create();
	horninessValTT->setRenderer(theme.getRenderer("ToolTip"));
	horninessValTT->setText("");
	horninessValTT->setPosition(0, 0);
	horninessValTT->setTextSize(18);

	horninessVal = tgui::ProgressBar::create();
	horninessVal->setRenderer(theme.getRenderer("ProgressBar"));
	horninessVal->setPosition(150, 99);
	horninessVal->setSize(170, 20);
	horninessVal->setTextSize(16);
	horninessVal->setVisible(0);
	horninessVal->setToolTip(horninessValTT);
	gui->add(horninessVal);

	aggresion = tgui::Label::create();
	aggresion->setRenderer(theme.getRenderer("Label"));
	aggresion->setText("Aggresion");
	aggresion->setPosition(10, 130);
	aggresion->setTextSize(18);
	gui->add(aggresion);

	aggresionValTT = tgui::Label::create();
	aggresionValTT->setRenderer(theme.getRenderer("ToolTip"));
	aggresionValTT->setText("");
	aggresionValTT->setPosition(0, 0);
	aggresionValTT->setTextSize(18);

	aggresionVal = tgui::ProgressBar::create();
	aggresionVal->setRenderer(theme.getRenderer("ProgressBar"));
	aggresionVal->setPosition(150, 129);
	aggresionVal->setSize(170, 20);
	aggresionVal->setTextSize(16);
	aggresionVal->setVisible(0);
	aggresionVal->setToolTip(aggresionValTT);
	gui->add(aggresionVal);

	foodLevel = tgui::Label::create();
	foodLevel->setRenderer(theme.getRenderer("Label"));
	foodLevel->setText("Food level");
	foodLevel->setPosition(10, 160);
	foodLevel->setTextSize(18);
	gui->add(foodLevel);

	foodLevelValTT = tgui::Label::create();
	foodLevelValTT->setRenderer(theme.getRenderer("ToolTip"));
	foodLevelValTT->setText("");
	foodLevelValTT->setPosition(0, 0);
	foodLevelValTT->setTextSize(18);

	foodLevelVal = tgui::ProgressBar::create();
	foodLevelVal->setRenderer(theme.getRenderer("ProgressBar"));
	foodLevelVal->setPosition(150, 159);
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
	divisionThreshold->setPosition(10, 190);
	divisionThreshold->setTextSize(18);
	divisionThreshold->setToolTip(divisionThresholdTT);
	gui->add(divisionThreshold);

	divisionThresholdVal = tgui::TextBox::create();
	divisionThresholdVal->setRenderer(theme.getRenderer("TextBox"));
	divisionThresholdVal->setPosition(210, 189);
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
	radarRange->setPosition(10, 220);
	radarRange->setTextSize(18);
	radarRange->setToolTip(radarRangeTT);
	gui->add(radarRange);

	radarRangeVal = tgui::TextBox::create();
	radarRangeVal->setRenderer(theme.getRenderer("TextBox"));
	radarRangeVal->setPosition(210, 219);
	radarRangeVal->setSize(50, 20);
	radarRangeVal->setTextSize(16);
	radarRangeVal->setVisible(0);
	radarRangeVal->setReadOnly(1);
	radarRangeVal->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
	gui->add(radarRangeVal);

}

void CellPreviewApp::update()
{
	sf::Event event;
	if (window->isOpen())
	{
		auto cell = CellSelectionTool::getInstance().getSelectedCellCopy();
		if (cell != nullptr)
		{
			//size
			sizeValTT->setText("Min: " + doubleToString(cell->getGenes().maxSize.getMin(),2) + "\nMax: " + doubleToString(cell->getGenes().maxSize.get(),2));
			sizeVal->setVisible(1);
			sizeVal->setText(doubleToString(cell->getSize(),2));
			sizeVal->setMaximum(cell->getGenes().maxSize.get());
			sizeVal->setMinimum(cell->getGenes().maxSize.getMin());
			sizeVal->setValue(cell->getSize());
			//speed
			speedValTT->setText("Min: " + doubleToString(cell->getGenes().maxSpeed.getMin(),2) + "\nMax: " + doubleToString(cell->getGenes().maxSpeed.get(),2));
			speedVal->setVisible(1);
			speedVal->setText(doubleToString(cell->getCurrentSpeed(),2));
			speedVal->setMaximum(cell->getGenes().maxSpeed.get()*100);
			speedVal->setMinimum(cell->getGenes().maxSpeed.getMin()*100);
			speedVal->setValue(cell->getCurrentSpeed()*100);
			//age
			ageValTT->setText("Min: " + doubleToString(cell->getGenes().maxAge.getMin(),2) + "\nMax: " + doubleToString(cell->getGenes().maxAge.get(),2));
			ageVal->setVisible(1);
			ageVal->setText(doubleToString(cell->age,2));
			ageVal->setMaximum(cell->getGenes().maxAge.get() * 100);
			ageVal->setMinimum(cell->getGenes().maxAge.getMin() * 100);
			ageVal->setValue(cell->age * 100);
			//horniness
			horninessValTT->setText("Min: " + doubleToString(cell->getHorniness().getMin(),2) + "\nMax: " + doubleToString(cell->getHorniness().getMax(),2));
			horninessVal->setVisible(1);
			horninessVal->setText(doubleToString(cell->getHorniness().get(),2));
			horninessVal->setMaximum(cell->getHorniness().getMax() * 100);
			horninessVal->setMinimum(cell->getHorniness().getMin() * 100);
			horninessVal->setValue(cell->getHorniness().get() * 100);
			//aggresion
			aggresionValTT->setText("Min: " + doubleToString(cell->getGenes().aggresion.getMin(),2) + "\nMax: " + doubleToString(cell->getGenes().aggresion.getMax(),2));
			aggresionVal->setVisible(1);
			aggresionVal->setText(doubleToString(cell->getGenes().aggresion.get(),2));
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

			cell->setPosition(sf::Vector2f( 175, window->getSize().y  - 60 ));
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
		if (!MainApp::appRun)
		{
			window->close();
		}
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				MainApp::close();

			gui->handleEvent(event); // Pass the event to the widgets
		}

		window->clear(sf::Color(0, 0, 0));
		if (cell != nullptr)
		{
			cell->setSize(50);
			cell->setRotation(0);
			window->draw(*cell);
		}
		gui->draw(); // Draw all widgets
		window->display();
	}
}

void CellPreviewApp::close()
{
	window->close();
}

std::shared_ptr<sf::RenderWindow> CellPreviewApp::getWindowHandle()
{
	return window;
}
