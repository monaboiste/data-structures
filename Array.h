#pragma once

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
	using value_type = T;
	using size_type = size_t;
	using pointer = T*;
	using reference = T&;
	using const_pointer = const T*;
	using const_reference = const T&;
	using iterator = RAIterator<Array<T, N>>;
	using const_iterator = RAIterator<const Array<T, N>>;

public:
	Array() = default;

	Array(const std::initializer_list<value_type>& valueList)
	{
		assert(valueList.size() <= N);
		std::copy(valueList.begin(), valueList.end(), m_data);
	}

	Array(const Array& other)
	{
		for (size_type i = 0; i < N; i++)
			m_data[i] = other.m_data[i];
	}

	Array& operator =(const Array& other)
	{
		for (size_type i = 0; i < N; i++)
			m_data[i] = other.m_data[i];
		return *this;
	}

	Array(Array&& other)
	{
		for (size_type i = 0; i < N; i++)
			m_data[i] = std::move(other.m_data[i]);
	}

	Array& operator =(Array&& other)
	{
		for (size_type i = 0; i < N; i++)
			m_data[i] = std::move(other.m_data[i]);
		return *this;
	}

	constexpr size_type Size() const
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

	constexpr const_iterator Cbegin() const
	{
		return const_iterator(&m_data[0]);
	}

	constexpr const_iterator Cend() const
	{
		return const_iterator(&m_data[N]);
	}


	constexpr reference operator[] (size_type index)
	{
		assert(index >= 0 && index < N);
		return m_data[index];
	}

	constexpr const_reference operator[] (size_type index) const
	{
		assert(index >= 0 && index < N);
		return m_data[index];
	}

private:
	value_type m_data[N];
};

// Array of size 0 is not allowed.

template <class T>
class Array<T, 0>
{
public:
	Array() = delete;
};