#include "EnvSettingsApp.h"
#include "Environment.h"
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
	labelTemp->setPosition(50,35);
	labelTemp->setTextSize(18);
	gui.add(labelTemp);

	auto editBoxTemp = tgui::EditBox::create();
	editBoxTemp->setRenderer(theme.getRenderer("EditBox"));
	editBoxTemp->setSize(60, 25);
	editBoxTemp->setTextSize(18);
	editBoxTemp->setPosition(220, 52);
	editBoxTemp->setDefaultText(std::to_string((int)Environment::getTemperature()));
	gui.add(editBoxTemp);

	auto sliderTemp = tgui::Slider::create();
	sliderTemp->setRenderer(theme.getRenderer("Slider"));
	sliderTemp->setPosition(10, 60);
	sliderTemp->setSize(200, 9);
	sliderTemp->setMaximum(100);
	sliderTemp->setMinimum(-100);
	sliderTemp->setValue(Environment::getTemperature());
	gui.add(sliderTemp);

	auto buttonTemp = tgui::Button::create();
	buttonTemp->setRenderer(theme.getRenderer("Button"));
	buttonTemp->setPosition(285, 52);
	buttonTemp->setText("SET");
	buttonTemp->setSize(60, 25);
	gui.add(buttonTemp);

	auto labelRad = tgui::Label::create();
	labelRad->setRenderer(theme.getRenderer("Label"));
	labelRad->setText("Radiation");
	labelRad->setPosition(70, 110);
	labelRad->setTextSize(18);
	gui.add(labelRad);

	auto editBoxRad = tgui::EditBox::create();
	editBoxRad->setRenderer(theme.getRenderer("EditBox"));
	editBoxRad->setSize(60, 25);
	editBoxRad->setTextSize(18);
	editBoxRad->setPosition(220, 127);
	editBoxRad->setDefaultText(std::to_string((int)Environment::getRadiation()));
	gui.add(editBoxRad);

	auto sliderRad = tgui::Slider::create();
	sliderRad->setRenderer(theme.getRenderer("Slider"));
	sliderRad->setPosition(10, 135);
	sliderRad->setSize(200, 9);
	sliderRad->setMaximum(100);
	sliderRad->setMinimum(0);
	sliderRad->setValue(Environment::getRadiation());
	gui.add(sliderRad);

	auto buttonRad = tgui::Button::create();
	buttonRad->setRenderer(theme.getRenderer("Button"));
	buttonRad->setPosition(285, 127);
	buttonRad->setText("SET");
	buttonRad->setSize(60, 25);
	gui.add(buttonRad);

	auto labelFeed = tgui::Label::create();
	labelFeed->setRenderer(theme.getRenderer("Label"));
	labelFeed->setText("Feed");
	labelFeed->setPosition(147, 190);
	labelFeed->setTextSize(24);
	gui.add(labelFeed);

	auto buttonFeedStart = tgui::Button::create();
	buttonFeedStart->setRenderer(theme.getRenderer("Button"));
	buttonFeedStart->setPosition(75, 220);
	buttonFeedStart->setText("START");
	buttonFeedStart->setSize(100, 40);
	buttonFeedStart->setInheritedOpacity(1);
	gui.add(buttonFeedStart);

	auto buttonFeedStop = tgui::Button::create();
	buttonFeedStop->setRenderer(theme.getRenderer("Button"));
	buttonFeedStop->setPosition(180, 220);
	buttonFeedStop->setText("STOP");
	buttonFeedStop->setSize(100, 40);
	buttonFeedStop->setInheritedOpacity(0.5);
	buttonFeedStop->setEnabled(0);
	gui.add(buttonFeedStop);

	auto checkBoxFeed = tgui::CheckBox::create();
	checkBoxFeed->setRenderer(theme.getRenderer("CheckBox"));
	checkBoxFeed->setPosition(75, 270);
	checkBoxFeed->setText("Auto feed");
	checkBoxFeed->setSize(10, 10);
	gui.add(checkBoxFeed);

	//wywo³anie eventów
	sliderTemp->connect("ValueChanged", [&]()
	{
		Environment::setTemperature(sliderTemp->getValue());
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
		Environment::setRadiation(sliderRad->getValue());
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

	buttonFeedStop->connect("pressed", [=]()
	{
		buttonFeedStop->setEnabled(0);
		buttonFeedStop->setInheritedOpacity(0.5);
		buttonFeedStart->setEnabled(1);
		buttonFeedStart->setInheritedOpacity(1);
	});

	buttonFeedStart->connect("pressed", [=]()
	{
		buttonFeedStart->setEnabled(0);
		buttonFeedStart->setInheritedOpacity(0.5);
		buttonFeedStop->setEnabled(1);
		buttonFeedStop->setInheritedOpacity(1);
	});

	sf::Event event;
	while (window->isOpen())
	{
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
