#pragma once
#include <iostream>
#include <algorithm>

template <typename T, int min, int max>
class Ranged
{
public:
	Ranged();
	Ranged(T r);
	Ranged(const Ranged& v);
	Ranged& operator=(const Ranged& v);
	//operator T();

	Ranged operator+(const Ranged& v);
	Ranged operator-(const Ranged& v);
	Ranged operator*(const Ranged& v);
	Ranged operator/(const Ranged& v);

	Ranged& operator++(const int);
	Ranged& operator++();

	Ranged& operator--(const int);
	Ranged& operator--();

	bool operator==(const Ranged& v);
	bool operator!=(const Ranged& v);
	bool operator>(const Ranged& v);
	bool operator<(const Ranged& v);

	T raw();
private:

	T value;
	static Ranged check(const T& v);
};

template<typename T, int min, int max>
inline Ranged<T, min, max>::Ranged()
{
	value = min;
}

template<typename T, int min, int max>
inline Ranged<T, min, max>::Ranged(T r)
{
	value = r;
}

template<typename T, int min, int max>
inline Ranged<T, min, max> & Ranged<T, min, max>::operator=(const Ranged & v)
{
	this->value = check(v.value).raw();
	return *this;
}

//template<typename T, int min, int max>
//inline Ranged<T, min, max>::operator T()
//{
//	return T(value);
//}

template<typename T, int min, int max>
inline Ranged<T, min, max> Ranged<T, min, max>::operator+(const Ranged & v)
{
	return check(this->value + v.value);
}

template<typename T, int min, int max>
inline Ranged<T, min, max> Ranged<T, min, max>::operator-(const Ranged & v)
{
	return check(this->value - v.value);
}

template<typename T, int min, int max>
inline Ranged<T, min, max> Ranged<T, min, max>::operator*(const Ranged & v)
{
	return check(this->value * v.value);
}

template<typename T, int min, int max>
inline Ranged<T, min, max> Ranged<T, min, max>::operator/(const Ranged & v)
{
	return check(this->value / v.value);
}

template<typename T, int min, int max>
inline Ranged<T, min, max> & Ranged<T, min, max>::operator++(const int)
{
	*this = check(this->value + 1);
	return *this;
}

template<typename T, int min, int max>
inline Ranged<T, min, max>::Ranged(const Ranged & v)
{
	this->value = v.value;
}

template<typename T, int min, int max>
inline Ranged<T, min, max> Ranged<T, min, max>::check(const T & v)
{
	T temp = v;
	if (temp > max) temp = max;
	if (temp < min) temp = min;
	return Ranged<T, min, max>(temp);
}

template<typename T, int min, int max>
inline Ranged<T, min, max> & Ranged<T, min, max>::operator++()
{
	*this = check(this->value + 1);
	return *this;
}

template<typename T, int min, int max>
inline Ranged<T, min, max> & Ranged<T, min, max>::operator--(const int)
{
	*this = check(this->value - 1);
	return *this;
}

template<typename T, int min, int max>
inline Ranged<T, min, max> & Ranged<T, min, max>::operator--()
{
	*this = check(this->value - 1);
	return *this;
}

template<typename T, int min, int max>
inline bool Ranged<T, min, max>::operator==(const Ranged & v)
{
	return this->value == v.value;
}

template<typename T, int min, int max>
inline bool Ranged<T, min, max>::operator!=(const Ranged & v)
{
	return this->value != v.value;
}

template<typename T, int min, int max>
inline bool Ranged<T, min, max>::operator>(const Ranged & v)
{
	return this->value > v.value;
}

template<typename T, int min, int max>
inline bool Ranged<T, min, max>::operator<(const Ranged & v)
{
	return this->value < v.value;
}

template<typename T, int min, int max>
inline T Ranged<T, min, max>::raw()
{
	return value;
}

template<typename T, int min, int max>
std::ostream& operator<<(std::ostream& stream, const Ranged<T, min, max>& v)
{
	return stream << v.raw();
}

bool rangedTest()
{
	std::vector<bool> result;

	Ranged<int, 1, 10> a, b(3);
	Ranged<int, 1, 50> c(40);

	a = 5;
	result.push_back(a.raw() == 5);

	result.push_back((a + b).raw() == 8);
	result.push_back((b - a).raw() == 1);
	result.push_back((a - b).raw() == 2);
	result.push_back((a * b).raw() == 10);
	result.push_back((a / b).raw() == 1);

	c++;
	result.push_back(c.raw() == 41);

	c--;
	result.push_back(c.raw() == 40);

	++c;
	result.push_back(c.raw() == 41);

	--c;
	result.push_back(c.raw() == 40);

	result.push_back(c == 40);
	result.push_back(c > 39);
	result.push_back(c < 49);
	result.push_back(c != 1);

	if (std::all_of(result.begin(), result.end(), [](auto a) {return a == true; })) return true; else terminate();
}