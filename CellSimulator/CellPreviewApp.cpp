#include "CellPreviewApp.h"
#include "CellSelectionTool.h"
#include "MainApp.h"
#include "Logger.h"
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
	maxSpeed = tgui::Label::create();
	maxSpeed->setRenderer(theme.getRenderer("Label"));
	maxSpeed->setText("Max speed:");
	maxSpeed->setPosition(10, 10);
	maxSpeed->setTextSize(18);
	gui->add(maxSpeed);

	maxSpeedVal = tgui::Label::create();
	maxSpeedVal->setRenderer(theme.getRenderer("Label"));
	maxSpeedVal->setPosition(200, 10);
	maxSpeedVal->setTextSize(18);
	gui->add(maxSpeedVal);

	aggresion = tgui::Label::create();
	aggresion->setRenderer(theme.getRenderer("Label"));
	aggresion->setText("Aggresion:");
	aggresion->setPosition(10, 30);
	aggresion->setTextSize(18);
	gui->add(aggresion);

	aggresionVal = tgui::Label::create();
	aggresionVal->setRenderer(theme.getRenderer("Label"));
	aggresionVal->setPosition(200, 30);
	aggresionVal->setTextSize(18);
	gui->add(aggresionVal);

	radarRange = tgui::Label::create();
	radarRange->setRenderer(theme.getRenderer("Label"));
	radarRange->setText("Radar range:");
	radarRange->setPosition(10, 50);
	radarRange->setTextSize(18);
	gui->add(radarRange);

	radarRangeVal = tgui::Label::create();
	radarRangeVal->setRenderer(theme.getRenderer("Label"));
	radarRangeVal->setPosition(200, 50);
	radarRangeVal->setTextSize(18);
	gui->add(radarRangeVal);

	divisionThreshold = tgui::Label::create();
	divisionThreshold->setRenderer(theme.getRenderer("Label"));
	divisionThreshold->setText("Division threshold:");
	divisionThreshold->setPosition(10, 70);
	divisionThreshold->setTextSize(18);
	gui->add(divisionThreshold);

	divisionThresholdVal = tgui::Label::create();
	divisionThresholdVal->setRenderer(theme.getRenderer("Label"));
	divisionThresholdVal->setPosition(200, 70);
	divisionThresholdVal->setTextSize(18);
	gui->add(divisionThresholdVal);

	foodLimit = tgui::Label::create();
	foodLimit->setRenderer(theme.getRenderer("Label"));
	foodLimit->setText("Food limit:");
	foodLimit->setPosition(10, 90);
	foodLimit->setTextSize(18);
	gui->add(foodLimit);

	foodLimitVal = tgui::Label::create();
	foodLimitVal->setRenderer(theme.getRenderer("Label"));
	foodLimitVal->setPosition(200, 90);
	foodLimitVal->setTextSize(18);
	gui->add(foodLimitVal);

	maxSize = tgui::Label::create();
	maxSize->setRenderer(theme.getRenderer("Label"));
	maxSize->setText("Max size:");
	maxSize->setPosition(10, 110);
	maxSize->setTextSize(18);
	gui->add(maxSize);

	maxSizeVal = tgui::Label::create();
	maxSizeVal->setRenderer(theme.getRenderer("Label"));
	maxSizeVal->setPosition(200, 110);
	maxSizeVal->setTextSize(18);
	gui->add(maxSizeVal);

	age = tgui::Label::create();
	age->setRenderer(theme.getRenderer("Label"));
	age->setText("Age:");
	age->setPosition(10, 130);
	age->setTextSize(18);
	gui->add(age);

	ageVal = tgui::Label::create();
	ageVal->setRenderer(theme.getRenderer("Label"));
	ageVal->setPosition(200, 130);
	ageVal->setTextSize(18);
	gui->add(ageVal);

	foodLevel = tgui::Label::create();
	foodLevel->setRenderer(theme.getRenderer("Label"));
	foodLevel->setText("Food level:");
	foodLevel->setPosition(10, 150);
	foodLevel->setTextSize(18);
	gui->add(foodLevel);

	foodLevelVal = tgui::Label::create();
	foodLevelVal->setRenderer(theme.getRenderer("Label"));
	foodLevelVal->setPosition(200, 150);
	foodLevelVal->setTextSize(18);
	gui->add(foodLevelVal);

	currentSpeed = tgui::Label::create();
	currentSpeed->setRenderer(theme.getRenderer("Label"));
	currentSpeed->setText("Current speed:");
	currentSpeed->setPosition(10, 170);
	currentSpeed->setTextSize(18);
	gui->add(currentSpeed);

	currentSpeedVal = tgui::Label::create();
	currentSpeedVal->setRenderer(theme.getRenderer("Label"));
	currentSpeedVal->setPosition(200, 170);
	currentSpeedVal->setTextSize(18);
	gui->add(currentSpeedVal);

	size = tgui::Label::create();
	size->setRenderer(theme.getRenderer("Label"));
	size->setText("Size:");
	size->setPosition(10, 190);
	size->setTextSize(18);
	gui->add(size);

	sizeVal = tgui::Label::create();
	sizeVal->setRenderer(theme.getRenderer("Label"));
	sizeVal->setPosition(200, 190);
	sizeVal->setTextSize(18);
	gui->add(sizeVal);
}

void CellPreviewApp::update()
{
	sf::Event event;
	if (window->isOpen())
	{
		auto cell = CellSelectionTool::getInstance().getSelectedCellCopy();
		if (cell != nullptr)
		{
			maxSpeedVal->setText(std::to_string(cell->getGenes().maxSpeed.get()));
			aggresionVal->setText(std::to_string(cell->getGenes().aggresion.get()));
			radarRangeVal->setText(std::to_string(cell->getGenes().radarRange.get()));
			divisionThresholdVal->setText(std::to_string(cell->getGenes().divisionThreshold.get()));
			foodLimitVal->setText(std::to_string(cell->getGenes().foodLimit.get()));
			maxSizeVal->setText(std::to_string(cell->getGenes().maxSize.get()));
			ageVal->setText(std::to_string(cell->age));
			foodLevelVal->setText(std::to_string(cell->getFoodLevel()));
			currentSpeedVal->setText(std::to_string(cell->getCurrentSpeed()));
			sizeVal->setText(std::to_string(cell->getSize()));

			cell->setPosition(sf::Vector2f( 175, window->getSize().y  - 100 ));
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
		else
		{
			Logger::log("NULL " + std::to_string(i));
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
