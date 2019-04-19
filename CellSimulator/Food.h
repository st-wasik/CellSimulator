#pragma once
#include <SFML/Graphics.hpp>
#include "BaseObj.h"
#include <memory>

class Food : public BaseObj
{
public:
	template <typename ... T>
	static std::shared_ptr<Food> create(T ... values);

	~Food();

	void update();

	std::string getSaveString();

private:
	Food(float size, sf::Vector2f position, sf::Color color);
	Food(std::string formattedFoodString);

	void modifyValueFromString(std::string valueName, std::string value);
	void modifyValueFromVector(std::string valueName, const std::vector<std::string>& value);
};

template<typename ...T>
inline std::shared_ptr<Food> Food::create(T ... values)
{
	auto result = std::make_shared<Food>(Food(values ...));
	result->setSelfPtr(result);
	return result;
}
