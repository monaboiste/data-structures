#include <cstddef>
#include <initializer_list>
#include <cassert>

#include "RAIterator.h"

///
/// Array class
///
/// Objects of this class have fixed non-modifiable size.
/// Data is stored on the stack.
///

template <class T, size_t N>
class Array
{
public:
	using valueType = T;
	using sizeType = size_t;
	using pointer = T*;
	using reference = T&;
	using constPointer = const T*;
	using constReference = const T&;
	using iterator = RAIterator<T>;
	using constIterator = RAIterator<const T>;
	using differenceType = std::ptrdiff_t;

public:
	Array() = default;

	Array(const std::initializer_list<valueType>& valueList)
	{
		assert(valueList.size() <= N);
		std::copy(valueList.begin(), valueList.end(), m_data);
	}

	Array(const Array& other)
	{
		for (size_t i = 0; i < N; i++)
			m_data[i] = other.m_data[i];
	}

	Array operator =(const Array& other)
	{
		for (int i = 0; i < N; i++)
			m_data[i] = other.m_data[i];
		return *this;
	}

	Array(const Array&& other)
	{
		for (size_t i = 0; i < N; i++)
			m_data[i] = std::move(other.m_data[i]);
	}

	Array operator =(const Array&& other)
	{
		for (int i = 0; i < N; i++)
			m_data[i] = std::move(other.m_data[i]);
		return *this;
	}

	constexpr sizeType Size() const
	{
		return N;
	}

	constexpr iterator Begin()
	{
		return iterator(&m_data[0]);
	}

	constexpr iterator End()
	{
		return iterator(&m_data[N]);
	}

	constexpr constIterator Cbegin() const
	{
		return constIterator(&m_data[0]);
	}

	constexpr constIterator Cend() const
	{
		return constIterator(&m_data[N]);
	}


	constexpr reference operator[] (size_t index)
	{
		assert(index >= 0 && index < N);
		return m_data[index];
	}

	constexpr constReference operator[] (size_t index) const
	{
		assert(index >= 0 && index < N);
		return m_data[index];
	}

private:
	valueType m_data[N];
};

// Array of size 0 is not allowed.

template <class T>
class Array<T, 0>
{
public:
	Array() = delete;
};
