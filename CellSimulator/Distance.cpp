#include "Distance.h"

double getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
auto v = a - b;
return sqrt(v.x*v.x + v.y*v.y);
}