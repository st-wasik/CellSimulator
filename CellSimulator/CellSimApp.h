#pragma once
#include <SFML/Graphics.hpp>

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

private:
	CellSimApp();
	CellSimApp(const CellSimApp&) = delete;
	CellSimApp& operator=(const CellSimApp&) = delete;

	std::shared_ptr<sf::RenderWindow> window;

	sf::View view;
	sf::VideoMode windowVideoMode;

	std::string windowTitle;

	void updateViewZoom();

	void updateViewCenter();

	double _currentZoom;
	int _expectedZoom;
	static constexpr int _maxZoom = -7;
	static constexpr int _minZoom = 7;

	float deltaTime;
};

