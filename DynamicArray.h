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
	using value_type = T;
	using size_type = size_t;
	using pointer = T*;
	using reference = T&;
	using const_pointer = const T*;
	using const_reference = const T&;
	using iterator = RAIterator<T>;
	using const_iterator = RAIterator<const T>;

public:
	DynamicArray() = default;

	DynamicArray(size_type size)
		: m_capacity(size)
		, m_size(m_capacity)
		, m_data(new value_type[m_capacity])
	{
	}

	DynamicArray(const std::initializer_list<value_type>& valueList)
		: m_capacity(valueList.size())
		, m_size(m_capacity)
		, m_data(new value_type[m_capacity])
	{
		std::copy(valueList.begin(), valueList.end(), m_data);
	}

	DynamicArray(const DynamicArray& other)
		: m_capacity(other.m_capacity)
		, m_size(other.m_size)
		, m_data(new value_type[other.m_capacity])
	{
		for (size_type i = 0; i < m_size; i++)
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
			m_data = new value_type[other.m_capacity];

			for (int i = 0; i < m_size; i++)
				m_data[i] = other.m_data[i];
		}
		return *this;
	}

	DynamicArray(const DynamicArray&& other)
		: m_capacity(std::move(other.m_capacity))
		, m_size(std::move(other.m_size))
		, m_data(new value_type[other.m_capacity])
	{
		for (size_type i = 0; i < m_size; i++)
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
			m_data = new value_type[other.m_capacity];

			for (size_type i = 0; i < m_size; i++)
				m_data[i] = std::move(other.m_data[i]);

			other.m_capacity = 0;
			other.m_size = 0;
			other.m_data = nullptr;
		}
		return *this;
	}

	constexpr void PushBack(const_reference value)
	{
		size_type newSize = m_size + 1;
		ReallocAndCopyData(newSize);
		m_data[m_size] = value;
		m_size = newSize;
	}

	template <typename ...Args>
	reference EmplaceBack(Args&& ...args)
	{
		size_type oldSize = m_size;
		size_type newSize = m_size + 1;
		ReallocAndCopyData(newSize);
		m_data[m_size] = value_type(std::forward<Args>(args)...);
		m_size = newSize;
		return m_data[oldSize];
	}

	constexpr void PopBack()
	{
		if (m_size > 0)
		{
			m_size--;
			m_data[m_size].~value_type();
		}
	}

	constexpr void Clear()
	{
		for (int i = 0; i < m_size; i++)
			m_data[i].~value_type();
		m_size = 0;
	}

	constexpr bool Empty() const
	{
		return (m_size == 0);
	}


	constexpr size_type Size() const
	{
		return m_size;
	}

	constexpr size_type Capacity() const
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

	constexpr const_iterator Cbegin() const
	{
		return constIterator(&m_data[0]);
	}

	constexpr const_iterator Cend() const
	{
		return constIterator(&m_data[m_size]);
	}


	constexpr reference operator[] (size_type index)
	{
		assert(index >= 0 && index < m_size);
		return m_data[index];
	}

	constexpr const_reference operator[] (size_type index) const
	{
		assert(index >= 0 && index < m_size);
		return m_data[index];
	}

private:
	constexpr void ReallocAndCopyData(size_type newSize)
	{
		if (Empty())
		{
			m_capacity = 2;
			m_data = new value_type[m_capacity];
		}

		size_type growth = CalculateGrowth(newSize);
		if (growth > m_capacity)
		{
			m_capacity = growth;
			pointer newMemoryBlock = new value_type[m_capacity];

			for (size_type i = 0; i < m_size; i++)
				newMemoryBlock[i] = std::move(m_data[i]);

			delete[] m_data;
			m_data = newMemoryBlock;
		}
	}

	constexpr size_type CalculateGrowth(size_type newSize)
	{
		size_type oldCapacity = m_capacity;
		if (oldCapacity >= newSize)
			return oldCapacity;

		size_type newCapacity = m_capacity + m_capacity / 2;
		return newCapacity;
	}

private:
	size_type m_capacity = 0;
	size_type m_size = 0;
	pointer m_data = nullptr;
};