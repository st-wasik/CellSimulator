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
	CellSimApp::getInstance().run();
}

void MainApp::close()
{
	appRun = false;
}
