#include <cstddef>
#include <initializer_list>
#include <cassert>

#include "RAIterator.h"

///
/// DynamicArray class
///
/// Objects of this class have modifiable size.
/// Data is stored on the heap.
///

template <class T>
class DynamicArray
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
	DynamicArray() = default;

	DynamicArray(sizeType size)
		: m_capacity(size)
		, m_size(m_capacity)
		, m_data(new T[m_capacity])
	{
	}

	DynamicArray(const std::initializer_list<valueType>& valueList)
		: m_capacity(valueList.size())
		, m_size(m_capacity)
		, m_data(new T[m_capacity])
	{
		std::copy(valueList.begin(), valueList.end(), m_data);
	}

	DynamicArray(const DynamicArray& other)
		: m_capacity(other.m_capacity)
		, m_size(other.m_size)
		, m_data(new T[other.m_capacity])
	{
		for (size_t i = 0; i < m_size; i++)
			m_data[i] = other.m_data[i];
	}

	~DynamicArray()
	{
		if (m_data != nullptr)
			delete[] m_data;
	}

	DynamicArray operator =(const DynamicArray& other)
	{
		if (&other != this)
		{
			if (m_data != nullptr)
				delete[] m_data;

			m_capacity = other.m_capacity;
			m_size = other.m_size;
			m_data = new T[other.m_capacity];

			for (int i = 0; i < m_size; i++)
				m_data[i] = other.m_data[i];
		}
		return *this;
	}

	DynamicArray(const DynamicArray&& other)
		: m_capacity(std::move(other.m_capacity))
		, m_size(std::move(other.m_size))
		, m_data(new T[other.m_capacity])
	{
		for (size_t i = 0; i < m_size; i++)
			m_data[i] = std::move(other.m_data[i]);

		other.m_capacity = 0;
		other.m_size = 0;
		other.m_data = nullptr;
	}

	DynamicArray operator =(const DynamicArray&& other)
	{
		if (&other != this)
		{
			if (m_data != nullptr)
				delete m_data;

			m_capacity = std::move(other.m_capacity);
			m_size = std::move(other.m_size);
			m_data = new T[other.m_capacity];

			for (size_t i = 0; i < m_size; i++)
				m_data[i] = std::move(other.m_data[i]);

			other.m_capacity = 0;
			other.m_size = 0;
			other.m_data = nullptr;
		}
		return *this;
	}

	constexpr void PushBack(const T& value)
	{
		sizeType newSize = m_size + 1;
		ReallocAndCopyData(newSize);
		m_data[m_size] = value;
		m_size = newSize;
	}

	constexpr void PopBack()
	{
		m_size--;
	}

	constexpr bool Empty() const
	{
		return (m_size == 0);
	}


	constexpr sizeType Size() const
	{
		return m_size;
	}

	constexpr sizeType Capacity() const
	{
		return m_capacity;
	}

	constexpr iterator Begin()
	{
		return iterator(&m_data[0]);
	}

	constexpr iterator End()
	{
		return iterator(&m_data[m_size]);
	}

	constexpr constIterator Cbegin() const
	{
		return constIterator(&m_data[0]);
	}

	constexpr constIterator Cend() const
	{
		return constIterator(&m_data[m_size]);
	}


	constexpr reference operator[] (size_t index)
	{
		assert(index >= 0 && index < m_size);
		return m_data[index];
	}

	constexpr constReference operator[] (size_t index) const
	{
		assert(index >= 0 && index < m_size);
		return m_data[index];
	}

private:
	constexpr void ReallocAndCopyData(sizeType newSize)
	{
		sizeType growth = CalculateGrowth(newSize);
		if (growth > m_capacity)
		{
			m_capacity = growth;
			T* newMemoryBlock = new T[m_capacity];

			for (size_t i = 0; i < m_size; i++)
				newMemoryBlock[i] = m_data[i];

			delete[] m_data;
			m_data = newMemoryBlock;
		}
	}

	constexpr sizeType CalculateGrowth(sizeType newSize)
	{
		sizeType oldCapacity = m_capacity;
		if (oldCapacity >= newSize)
			return oldCapacity;

		sizeType newCapacity = m_capacity + m_capacity / 2;
		return newCapacity;
	}

private:
	sizeType m_capacity = 0;
	sizeType m_size = 0;
	pointer m_data = nullptr;
};