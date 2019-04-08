#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Random.h"

class BaseObj :public sf::Drawable
{
public:
	BaseObj(float size, sf::Vector2f position, sf::Color color);
	~BaseObj();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update() = 0;

	virtual float getSize();
	virtual void setSize(const float&);

	virtual float getRotation();
	virtual void setRotation(const float&);

	virtual sf::Vector2f getPosition();
	virtual void setPosition(const sf::Vector2f&);

	virtual sf::Color getBaseColor();
	virtual void setBaseColor(sf::Color);

	virtual std::string toString();

	// Marks obj to delete. Object will be deleted from vector in next loop turn.
	void markToDelete();
	bool isMarkedToDelete();

	bool collision(std::shared_ptr<BaseObj> obj);

	void setSelfPtr(std::shared_ptr<BaseObj> s);
	std::shared_ptr<BaseObj> getSelfPtr();

protected:
	sf::CircleShape shape;
	sf::Color baseColor;
private:
	bool toDelete;
	std::shared_ptr<BaseObj> self;
};

