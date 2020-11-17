#pragma once

#include <functional>

#include "DynamicArray.h"

///
/// Heap class
///
/// THIS IS BARELY DRAFT OF ACTUAL CLASS!
/// Eventually it's going to contain Heap implementation.
/// Whenether it's max or min heap, it will be determined by
/// predicate passed as templete parameter.
/// 

template <class T, class Pred = std::less<>>
class Heap
{
public:
	using value_type = typename DynamicArray<T>::value_type;
	using size_type = typename DynamicArray<T>::size_type;
	using pointer = typename DynamicArray<T>::pointer;
	using reference = typename DynamicArray<T>::reference;
	using const_pointer = typename DynamicArray<T>::const_pointer;
	using const_reference = typename DynamicArray<T>::const_reference;

public:
	Heap() = default;

	~Heap()
	{
		Clear();
	}

	Heap(const Heap& other)
	{
		// @TODO
	}

	Heap& operator =(const Heap& other)
	{
		// @TODO
	}

	constexpr const_reference Top() const
	{
		return m_data[0];
	}

	constexpr size_type size() const
	{
		return m_size;
	}

	constexpr void Push(value_type value)
	{
		m_size++;
		m_data.PushBack(value);
		Heapify();
	}

	constexpr void Pop()
	{
		// @TODO
	}

	constexpr void Clear()
	{
		m_data.Clear();
	}

private:
	constexpr void Heapify()
	{
		// Implements very basic idea of Max Heap
		// @TODO: Rewrite this
		for (int parent = (m_size >> 1) - 1; parent >= 0; parent--)
		{
			int leftChild = 2 * parent + 1;
			int rightChild = 2 * parent + 2;

			if (leftChild > (int)m_size - 1) leftChild = -1;
			if (rightChild > (int)m_size - 1) rightChild = -1;

			if (leftChild != -1)
			{
				if (m_data[parent] < m_data[leftChild])
					std::swap(m_data[parent], m_data[leftChild]);
			}
			if (rightChild != -1)
			{
				if (m_data[parent] < m_data[rightChild])
					std::swap(m_data[parent], m_data[rightChild]);
			}
		}
	}

private:
	DynamicArray<T> m_data;
	size_type m_size = 0;
};
