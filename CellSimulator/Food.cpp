#include "Food.h"
#include "RegexPattern.h"
#include "Logger.h"
#include <sstream>
#include <regex>

Food::Food(float size, sf::Vector2f position, sf::Color color) : BaseObj(size, position, color)
{
}

Food::Food(std::string formattedFoodString) : Food(0, { 0,0 }, sf::Color::Transparent)
{
	std::string doubleRegex(RegexPattern::Double);
	std::string vectorRegex(RegexPattern::Vector);
	std::string word(RegexPattern::Word);

	std::regex foodRegex("FOOD->( " + word + ":(" + doubleRegex + "|" + vectorRegex + "))* ");
	if (!std::regex_match(formattedFoodString.begin(), formattedFoodString.end(), foodRegex))
	{
		throw std::exception("Cell string wrong format!");
	}

	std::regex settingRegex(" " + word + ":((" + doubleRegex + ")|(" + vectorRegex + "))");

	auto settingsBegin = std::sregex_iterator(formattedFoodString.begin(), formattedFoodString.end(), settingRegex);
	auto settingsEnd = std::sregex_iterator();

	for (auto i = settingsBegin; i != settingsEnd; ++i)
	{
		std::string settingStr = i->str();
		std::regex type(word);
		std::regex value(doubleRegex);
		std::regex vectorValue(vectorRegex);

		auto type_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), type);
		auto vector_value_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), vectorValue);

		if (type_i != std::sregex_iterator() && vector_value_i != std::sregex_iterator())
		{
			std::regex value(RegexPattern::Double);
			auto vector_value_s = vector_value_i->str();
			auto valuesBegin = std::sregex_iterator(vector_value_s.begin(), vector_value_s.end(), value);
			std::vector<std::string> values_vect;
			for (auto it = valuesBegin; it != std::sregex_iterator(); it++)
			{
				values_vect.push_back(it->str());
			}
			modifyValueFromVector(type_i->str(), values_vect);
		}
		else
		{
			auto value_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), value);
			if (type_i != std::sregex_iterator() && value_i != std::sregex_iterator())
				modifyValueFromString(type_i->str(), value_i->str());
		}
		
		//TODO: add cell name
	}
}

void Food::modifyValueFromString(std::string valueName, std::string value)
{
	//Logger::log("Setting '" + valueName + "' to " + value);
	auto& v = valueName;

	if (v == VarAbbrv::currentRotation)			this->setRotation(std::stod(value));
	else if (v == VarAbbrv::currentSize)		this->setSize((std::stod(value)));
	else if (v == BaseObj::VarAbbrv::markedToDelete)
	{
		if (std::stod(value)) this->markToDelete();
	}
	else Logger::log(std::string("Unknown food var name '" + v + "' with value '" + value + "'!"));
}

void Food::modifyValueFromVector(std::string valueName, const std::vector<std::string>& values)
{
	//Logger::log("Setting '" + valueName + "'.");
	auto& v = valueName;

	if (v == VarAbbrv::currentPosition)
	{
		if (values.size() != 2)
		{
			Logger::log("Wrong values count for " + std::string(VarAbbrv::currentPosition) + ": " + std::to_string(values.size()) + ".");
			return;
		}
		this->setPosition(sf::Vector2f(std::stod(values[0]), std::stod(values[1])));
	}
	else if (v == VarAbbrv::color)
	{
		if (values.size() != 4)
		{
			Logger::log("Wrong values count for " + std::string(VarAbbrv::color) + ": " + std::to_string(values.size()) + ".");
			return;
		}
		this->setBaseColor(sf::Color(std::stod(values[0]), std::stod(values[1]), std::stod(values[2]), std::stod(values[3])));
	}
}

Food::~Food()
{
}

void Food::update()
{
}

std::string Food::getSaveString()
{
	std::ostringstream result;

	result << "FOOD-> " <<
		VarAbbrv::currentRotation << ":" << this->getRotation() << " " <<
		VarAbbrv::currentPosition << ":{" << this->getPosition().x << ", " << this->getPosition().y << "} " <<
		VarAbbrv::color << ":{" <<
		static_cast<int>(this->getBaseColor().r) << ", " <<
		static_cast<int>(this->getBaseColor().g) << ", " <<
		static_cast<int>(this->getBaseColor().b) << ", " <<
		static_cast<int>(this->getBaseColor().a) << "} " <<
		VarAbbrv::currentSize << ":" << this->getSize() << " " <<
		VarAbbrv::markedToDelete << ":" << this->isMarkedToDelete() << " ";

	return result.str();
}
