#pragma once
#include <iostream>
#include "Random.h"

template <typename T>
class DynamicRanged
{
public:
	DynamicRanged(T min, T max, T value);
	DynamicRanged(const DynamicRanged& v);
	DynamicRanged& operator=(const T& v);

	DynamicRanged operator+(const T& v);
	DynamicRanged operator-(const T& v);
	DynamicRanged operator*(const T& v);
	DynamicRanged operator/(const T& v);

	DynamicRanged& operator++(const int);
	DynamicRanged& operator++();

	DynamicRanged& operator--(const int);
	DynamicRanged& operator--();

	T get() const;
	void randomize();
	bool isMax() const;
	bool isMin() const;

	T getMin() const;
	T getMax() const;
	T getRange() const;

	void setMin(const T& min);
	void setMax(const T& max);

private:
	void check();

	T value;
	T min;
	T max;
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const DynamicRanged<T>& v)
{
	return stream << v.get();
}

template<typename T>
inline DynamicRanged<T>::DynamicRanged(T min, T max, T value)
{
	this->min = min;
	this->max = max;
	this->value = value;
	check();
}

template<typename T>
inline DynamicRanged<T>::DynamicRanged(const DynamicRanged & r)
{
	this->min = r.min;
	this->max = r.max;
	this->value = r.value;
	check();
}

template<typename T>
inline DynamicRanged<T> & DynamicRanged<T>::operator=(const T & v)
{
	this->value = v;
	check();
	return *this;
}

template<typename T>
inline DynamicRanged<T> DynamicRanged<T>::operator+(const T & v)
{
	this->value = value + v;
	check();
	return *this;
}

template<typename T>
inline DynamicRanged<T> DynamicRanged<T>::operator-(const T & v)
{
	this->value = value - v;
	check();
	return *this;
}

template<typename T>
inline DynamicRanged<T> DynamicRanged<T>::operator*(const T & v)
{
	this->value = value * v;
	check();
	return *this;
}

template<typename T>
inline DynamicRanged<T> DynamicRanged<T>::operator/(const T & v)
{
	this->value = value / v;
	check();
	return *this;
}

template<typename T>
inline DynamicRanged<T> & DynamicRanged<T>::operator++(const int)
{
	this->value = value + 1;
	check();
	return *this;
}

template<typename T>
inline DynamicRanged<T> & DynamicRanged<T>::operator++()
{
	this->value = value + 1;
	check();
	return *this;
}

template<typename T>
inline DynamicRanged<T> & DynamicRanged<T>::operator--(const int)
{
	this->value = value - 1;
	check();
	return *this;
}

template<typename T>
inline DynamicRanged<T> & DynamicRanged<T>::operator--()
{
	this->value = value - 1;
	check();
	return *this;
}

template<typename T>
inline T DynamicRanged<T>::get() const
{
	return value;
}

template<typename T>
inline void DynamicRanged<T>::randomize()
{
	value = randomReal(min, max);
}

template<typename T>
inline bool DynamicRanged<T>::isMax() const
{
	return value == max;
}

template<typename T>
inline bool DynamicRanged<T>::isMin() const
{
	return value == min;
}

template<typename T>
inline T DynamicRanged<T>::getMin() const
{
	return min;
}

template<typename T>
inline T DynamicRanged<T>::getMax() const
{
	return max;
}

template<typename T>
inline T DynamicRanged<T>::getRange() const
{
	return max - min;
}

template<typename T>
inline void DynamicRanged<T>::setMin(const T & min)
{
	this->min = min;
}

template<typename T>
inline void DynamicRanged<T>::setMax(const T & max)
{
	this->max = max;
}

template<typename T>
inline void DynamicRanged<T>::check()
{
	if (value > max) value = max;
	if (value < min) value = min;
}
