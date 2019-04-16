#include "MessagesManager.h"
#include "Logger.h"
#include "CellSimApp.h"
#include <tuple>



MessagesManager & MessagesManager::getInstance()
{
	static MessagesManager instance;
	return instance;
}

void MessagesManager::configure()
{
	messages.clear();
	zeroPoint = { 400.0, 0.0 };

	clock.restart();
}

void MessagesManager::update()
{
	while (true)
	{
		if (messages.size() > 0)
		{
			if ((clock.getElapsedTime() - std::get<0>(messages.back())).asMilliseconds() > secBeforeMessageDelete*1000)
			{
				messages.pop_back();
			}
			else break;
		} 
		else break;
	}
}

void MessagesManager::draw(std::shared_ptr<sf::RenderWindow> window)
{
	for (auto& m : messages)
		// std::get to get text from tuple
		window->draw(std::get<1>(m));
}

void MessagesManager::append(std::string s)
{
	sf::Text t;
	t.setFont(CellSimApp::getInstance().getFont());
	t.setCharacterSize(messageSize);
	t.setFillColor(sf::Color::White);
	t.setString(s);
	messages.push_front(std::tuple<sf::Time, sf::Text>(clock.getElapsedTime(), t));
	positionMessages();
}

MessagesManager::MessagesManager()
{
}


MessagesManager::~MessagesManager()
{
}

void MessagesManager::positionMessages()
{
	int i = 0;
	auto it = messages.begin();
	for (; it != messages.end(); ++it, ++i)
	{
		// std::get to get text from tuple
		std::get<1>(*it).setPosition({ zeroPoint.x, zeroPoint.y + messageOffset + i * messageOffset });
	}
}
