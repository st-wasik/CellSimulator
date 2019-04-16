#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <tuple>

class MessagesManager
{
public:

	static MessagesManager& getInstance();

	void configure();

	void update();

	void draw(std::shared_ptr<sf::RenderWindow> window);

	void append(std::string s);

private:
	MessagesManager();
	~MessagesManager();
	MessagesManager(const MessagesManager&) = delete;
	MessagesManager& operator=(const MessagesManager&) = delete;

	void positionMessages();

	std::list<std::tuple<sf::Time, sf::Text>> messages;

	sf::Vector2f zeroPoint;

	sf::Clock clock;

	static constexpr int messageOffset = 25; //px
	static constexpr int messageSize = 20; //px
	static constexpr int secBeforeMessageDelete = 5; 
};

