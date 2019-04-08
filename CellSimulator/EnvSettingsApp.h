#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <map>
#include <atomic>
class EnvSettingsApp
{
public:
	~EnvSettingsApp();

	static EnvSettingsApp& getInstance();

	void update();

	void close();

	void configure();

	std::shared_ptr<sf::RenderWindow> getWindowHandle();

private:
	EnvSettingsApp();
	EnvSettingsApp(const EnvSettingsApp&) = delete;
	EnvSettingsApp& operator=(const EnvSettingsApp&) = delete;


	std::shared_ptr<sf::RenderWindow> window;

	sf::VideoMode windowVideoMode;

	std::string windowTitle;

	std::shared_ptr<tgui::Gui> gui;

	tgui::Theme theme;

	//gui elements
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
};

