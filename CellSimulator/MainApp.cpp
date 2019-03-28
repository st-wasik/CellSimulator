#include "MainApp.h"
#include "CellSimApp.h"
#include "EnvSettingsApp.h"
#include "CellPreviewApp.h"
#include "CellListApp.h"
#include "GUIManager.h"
#include <thread>
#include <atomic>

std::atomic_bool MainApp::appRun(true);

void MainApp::run()
{
	// SFML DOCS
	//Events must be polled in the window's thread
	//This is an important limitation of most operating systems :
	//the event loop(more precisely, the pollEvent or waitEvent function) 
	//must be called in the same thread that created the window.This 
	//means that if you want to create a dedicated thread for event 
	//handling, you'll have to make sure that the window is created 
	//in this thread too. If you really want to split things between 
	//threads, it is more convenient to keep event handling in the main 
	//thread and move the rest (rendering, physics, logic, ...) to a 
	//separate thread instead. This configuration will also be 
	//compatible with the other limitation described below.

	CellSimApp::getInstance().configure();

	std::thread gui([]() {
		GUIManager::configure();

		auto envW = EnvSettingsApp::getInstance().getWindowHandle();

		//set in c-tor
		//envW->setPosition({ 10,10 });

		auto preW = CellPreviewApp::getInstance().getWindowHandle();
		preW->setPosition(envW->getPosition()+ sf::Vector2i(0, envW->getSize().y + 45));

		auto lstW = CellListApp::getInstance().getWindowHandle();
		lstW->setPosition(preW->getPosition() + sf::Vector2i(0, preW->getSize().y + 45));

		GUIManager::run();
	});

	auto envPos = EnvSettingsApp::getInstance().getWindowHandle()->getPosition();
	auto envSize = EnvSettingsApp::getInstance().getWindowHandle()->getSize();
	CellSimApp::getInstance().getWindowHandle()->setPosition(envPos + sf::Vector2i(envSize.x + 10, 0));

	CellSimApp::getInstance().run();

	gui.join();
}

void MainApp::close()
{
	appRun = false;
}
