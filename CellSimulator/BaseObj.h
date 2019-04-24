#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Random.h"

class BaseObj :public sf::Drawable
{
public:
	explicit BaseObj();
	BaseObj(float size, sf::Vector2f position, sf::Color color);
	~BaseObj();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update() = 0;

	float getSize();
	void setSize(const float&);

	float getRotation();
	void setRotation(const float&);

	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f&);

	sf::Color getBaseColor();
	void setBaseColor(sf::Color, bool updateShapeColor = false);

	float getOutlineThickness();
	void setOutlineThickness(float value);

	virtual std::string toString();

	virtual std::string getSaveString() = 0;

	// Marks obj to delete. Object will be deleted from vector in next loop turn.
	void markToDelete();
	bool isMarkedToDelete();

	bool collision(std::shared_ptr<BaseObj> obj);

	void setSelfPtr(std::shared_ptr<BaseObj> s);
	std::shared_ptr<BaseObj> getSelfPtr();

protected:
	sf::CircleShape shape;

	struct VarAbbrv final
	{
		static constexpr const char *const currentRotation = "Rt";
		static constexpr const char *const currentPosition = "Ps";
		static constexpr const char *const color = "C";
		static constexpr const char *const currentSize = "Si";
		static constexpr const char *const markedToDelete = "TD";
		static constexpr const char *const texture = "Tx";
		static constexpr const char *const textureRect = "TxR";
	private:
		VarAbbrv() = delete;
		VarAbbrv(const VarAbbrv&) = delete;
		VarAbbrv& operator=(const VarAbbrv&) = delete;
		virtual ~VarAbbrv() = 0;
	};

private:
	bool toDelete;
	std::shared_ptr<BaseObj> self;
	sf::Color baseColor;
};

