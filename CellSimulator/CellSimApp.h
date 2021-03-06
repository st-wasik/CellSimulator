#pragma once
#include <SFML/Graphics.hpp>
#include <atomic>

class CellSimMouse;

class CellSimApp final
{
public:
	friend class CellSimMouse;

	static CellSimApp& getInstance();

	~CellSimApp();

	 void run();

	 void configure();

	 void close();

	 std::shared_ptr<sf::RenderWindow> getWindowHandle();

	 const float& getDeltaTime();

	 const sf::Font& getFont();

	 sf::View& getView();

private:
	CellSimApp();
	CellSimApp(const CellSimApp&) = delete;
	CellSimApp& operator=(const CellSimApp&) = delete;

	std::shared_ptr<sf::RenderWindow> window;

	sf::View view;
	sf::VideoMode windowVideoMode;

	sf::Font font;

	std::string windowTitle;

	void updateViewZoom();

	void updateViewCenter();

	double _currentZoom;
	int _expectedZoom;
	static constexpr int _maxZoom = -7;
	static constexpr int _minZoom = 7;

	bool zoomByOneStep;

	float deltaTime;
	float fps;
};

