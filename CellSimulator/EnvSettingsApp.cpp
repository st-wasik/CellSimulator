#include "EnvSettingsApp.h"
#include "Environment.h"
#include "AutoFeederTool.h"
#include "MainApp.h"
#include "Logger.h"
#include <TGUI/TGUI.hpp>
#include <iostream>

std::shared_ptr<sf::RenderWindow> EnvSettingsApp::window;

sf::VideoMode EnvSettingsApp::windowVideoMode;

std::string EnvSettingsApp::windowTitle;

void EnvSettingsApp::configure()
{
	window = std::make_shared<sf::RenderWindow>();
	windowVideoMode = sf::VideoMode(350, 768/2 - 5);
	windowTitle = "Environment Settings";

	Logger::log(windowTitle + " - build " + __DATE__ + " " + __TIME__);

	window->create(windowVideoMode, windowTitle, sf::Style::Titlebar);
	window->setFramerateLimit(60);
}

void EnvSettingsApp::run()
{

	tgui::Gui gui(*window);
	tgui::Theme theme{ "../../CellSimulator/TGUI-0.8/themes/TransparentGrey.txt" };

	//elementy GUI

	auto labelTemp = tgui::Label::create();
	labelTemp->setRenderer(theme.getRenderer("Label"));
	labelTemp->setText("Temperature");
	labelTemp->setPosition(50,15);
	labelTemp->setTextSize(18);
	gui.add(labelTemp);

	auto editBoxTemp = tgui::EditBox::create();
	editBoxTemp->setRenderer(theme.getRenderer("EditBox"));
	editBoxTemp->setSize(60, 25);
	editBoxTemp->setTextSize(18);
	editBoxTemp->setPosition(220, 32);
	editBoxTemp->setDefaultText(std::to_string((int)Environment::getInstance().getTemperature()));
	gui.add(editBoxTemp);

	auto sliderTemp = tgui::Slider::create();
	sliderTemp->setRenderer(theme.getRenderer("Slider"));
	sliderTemp->setPosition(10, 40);
	sliderTemp->setSize(200, 9);
	sliderTemp->setMaximum(100);
	sliderTemp->setMinimum(-100);
	sliderTemp->setValue(Environment::getInstance().getTemperature());
	gui.add(sliderTemp);

	auto buttonTemp = tgui::Button::create();
	buttonTemp->setRenderer(theme.getRenderer("Button"));
	buttonTemp->setPosition(285, 32);
	buttonTemp->setText("SET");
	buttonTemp->setSize(60, 25);
	gui.add(buttonTemp);

	auto labelRad = tgui::Label::create();
	labelRad->setRenderer(theme.getRenderer("Label"));
	labelRad->setText("Radiation");
	labelRad->setPosition(70, 60);
	labelRad->setTextSize(18);
	gui.add(labelRad);

	auto editBoxRad = tgui::EditBox::create();
	editBoxRad->setRenderer(theme.getRenderer("EditBox"));
	editBoxRad->setSize(60, 25);
	editBoxRad->setTextSize(18);
	editBoxRad->setPosition(220, 77);
	editBoxRad->setDefaultText(std::to_string((int)Environment::getInstance().getRadiation()));
	gui.add(editBoxRad);

	auto sliderRad = tgui::Slider::create();
	sliderRad->setRenderer(theme.getRenderer("Slider"));
	sliderRad->setPosition(10, 85);
	sliderRad->setSize(200, 9);
	sliderRad->setMaximum(100);
	sliderRad->setMinimum(0);
	sliderRad->setValue(Environment::getInstance().getRadiation());
	gui.add(sliderRad);

	auto buttonRad = tgui::Button::create();
	buttonRad->setRenderer(theme.getRenderer("Button"));
	buttonRad->setPosition(285, 77);
	buttonRad->setText("SET");
	buttonRad->setSize(60, 25);
	gui.add(buttonRad);

	auto labelQuan = tgui::Label::create();
	labelQuan->setRenderer(theme.getRenderer("Label"));
	labelQuan->setText("Food limit");
	labelQuan->setPosition(68, 125);
	labelQuan->setTextSize(18);
	labelQuan->setEnabled(0);
	labelQuan->setInheritedOpacity(0.5);
	gui.add(labelQuan);

	auto editBoxQuan = tgui::EditBox::create();
	editBoxQuan->setRenderer(theme.getRenderer("EditBox"));
	editBoxQuan->setSize(60, 25);
	editBoxQuan->setTextSize(18);
	editBoxQuan->setPosition(220, 142);
	editBoxQuan->setDefaultText(std::to_string((int)AutoFeederTool::getInstance().getMaxThresholdValue()));
	editBoxQuan->setEnabled(0);
	editBoxQuan->setInheritedOpacity(0.5);
	gui.add(editBoxQuan);

	auto sliderQuan = tgui::Slider::create();
	sliderQuan->setRenderer(theme.getRenderer("Slider"));
	sliderQuan->setPosition(10, 150);
	sliderQuan->setSize(200, 9);
	sliderQuan->setMaximum(100);
	sliderQuan->setMinimum(1);
	sliderQuan->setValue(AutoFeederTool::getInstance().getMaxThresholdValue());
	sliderQuan->setEnabled(0);
	sliderQuan->setInheritedOpacity(0.5);
	gui.add(sliderQuan);

	auto buttonQuan = tgui::Button::create();
	buttonQuan->setRenderer(theme.getRenderer("Button"));
	buttonQuan->setPosition(285, 142);
	buttonQuan->setText("SET");
	buttonQuan->setSize(60, 25);
	buttonQuan->setEnabled(0);
	buttonQuan->setInheritedOpacity(0.5);
	gui.add(buttonQuan);

	auto labelFreq = tgui::Label::create();
	labelFreq->setRenderer(theme.getRenderer("Label"));
	labelFreq->setText("Feed frequency");
	labelFreq->setPosition(38, 170);
	labelFreq->setTextSize(18);
	labelFreq->setEnabled(0);
	labelFreq->setInheritedOpacity(0.5);
	gui.add(labelFreq);

	auto editBoxFreq = tgui::EditBox::create();
	editBoxFreq->setRenderer(theme.getRenderer("EditBox"));
	editBoxFreq->setSize(60, 25);
	editBoxFreq->setTextSize(18);
	editBoxFreq->setPosition(220, 187);
	editBoxFreq->setDefaultText(std::to_string((int)AutoFeederTool::getInstance().getMaxFoodPerSec()));
	editBoxFreq->setEnabled(0);
	editBoxFreq->setInheritedOpacity(0.5);
	gui.add(editBoxFreq);

	auto sliderFreq = tgui::Slider::create();
	sliderFreq->setRenderer(theme.getRenderer("Slider"));
	sliderFreq->setPosition(10, 195);
	sliderFreq->setSize(200, 9);
	sliderFreq->setMaximum(100);
	sliderFreq->setMinimum(1);
	sliderFreq->setValue(AutoFeederTool::getInstance().getMaxFoodPerSec());
	sliderFreq->setEnabled(0);
	sliderFreq->setInheritedOpacity(0.5);
	gui.add(sliderFreq);

	auto buttonFreq = tgui::Button::create();
	buttonFreq->setRenderer(theme.getRenderer("Button"));
	buttonFreq->setPosition(285, 187);
	buttonFreq->setText("SET");
	buttonFreq->setSize(60, 25);
	buttonFreq->setEnabled(0);
	buttonFreq->setInheritedOpacity(0.5);
	gui.add(buttonFreq);

	auto buttonFeed = tgui::Button::create();
	buttonFeed->setRenderer(theme.getRenderer("Button"));
	buttonFeed->setPosition(75, 230);
	buttonFeed->setText("Feed");
	buttonFeed->setSize(100, 40);
	buttonFeed->setInheritedOpacity(1);
	gui.add(buttonFeed);

	auto buttonSelect = tgui::Button::create();
	buttonSelect->setRenderer(theme.getRenderer("Button"));
	buttonSelect->setPosition(180, 230);
	buttonSelect->setText("Select");
	buttonSelect->setSize(100, 40);
	buttonSelect->setInheritedOpacity(0.5);
	buttonSelect->setEnabled(0);
	gui.add(buttonSelect);

	auto checkBoxFeed = tgui::CheckBox::create();
	checkBoxFeed->setRenderer(theme.getRenderer("CheckBox"));
	checkBoxFeed->setPosition(75, 275);
	checkBoxFeed->setText("Auto-feed");
	checkBoxFeed->setSize(15, 15);
	checkBoxFeed->setTextSize(14);
	gui.add(checkBoxFeed);

	auto labelCells = tgui::Label::create();
	labelCells->setRenderer(theme.getRenderer("Label"));
	labelCells->setText("Cells:");
	labelCells->setPosition(10, 310);
	labelCells->setTextSize(18);
	gui.add(labelCells);

	auto labelFood = tgui::Label::create();
	labelFood->setRenderer(theme.getRenderer("Label"));
	labelFood->setText("Food:");
	labelFood->setPosition(10, 340);
	labelFood->setTextSize(18);
	gui.add(labelFood);

	auto labelCellsVar = tgui::Label::create();
	labelCellsVar->setRenderer(theme.getRenderer("Label"));
	labelCellsVar->setText(std::to_string(Environment::getInstance().getAliveCellsCount()));
	labelCellsVar->setPosition(75, 310);
	labelCellsVar->setTextSize(18);
	gui.add(labelCellsVar);

	auto labelFoodVar = tgui::Label::create();
	labelFoodVar->setRenderer(theme.getRenderer("Label"));
	labelFoodVar->setText(std::to_string(Environment::getInstance().getFoodCount()));
	labelFoodVar->setPosition(75, 340);
	labelFoodVar->setTextSize(18);
	gui.add(labelFoodVar);

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

	sf::Event event;
	while (window->isOpen())
	{
		labelCellsVar->setText(std::to_string(Environment::getInstance().getAliveCellsCount()));
		labelFoodVar->setText(std::to_string(Environment::getInstance().getFoodCount()));
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				MainApp::close();

			gui.handleEvent(event); // Pass the event to the widgets
		}

		window->clear(sf::Color(0, 0, 0));
		gui.draw(); // Draw all widgets
		window->display();
	}
}

void EnvSettingsApp::close()
{
	window->close();
}

std::shared_ptr<sf::RenderWindow> EnvSettingsApp::getWindowHandle()
{
	return window;
}
