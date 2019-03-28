#include "GUIManager.h"
#include "EnvSettingsApp.h"
#include "CellPreviewApp.h"
#include "CellListApp.h"

void GUIManager::configure()
{
	EnvSettingsApp::getInstance().configure();
	CellListApp::getInstance().configure();
	CellPreviewApp::getInstance().configure();
}

void GUIManager::run()
{
	while (
		EnvSettingsApp::getInstance().getWindowHandle()->isOpen() ||
		CellPreviewApp::getInstance().getWindowHandle()->isOpen() ||
		CellListApp::getInstance().getWindowHandle()->isOpen()
		)
	{
		EnvSettingsApp::getInstance().update();
		CellListApp::getInstance().update();
		CellPreviewApp::getInstance().update();
	}
}

void GUIManager::close()
{
	EnvSettingsApp::getInstance().close();
	CellListApp::getInstance().close();
	CellPreviewApp::getInstance().close();
}