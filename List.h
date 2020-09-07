#include <cstddef>
#include <cstdint>
#include <cassert>
#include <initializer_list>

#include "BDIterator.h"

///
/// List class
///
/// Class is basically implementation of doubly link list.
/// Objects of this class have non-fixed modifiable size.
/// Every node is created on the heap. Nodes store data.
///

template <class T>
class List
{
	template <class>
	friend class BDIterator;
public:
	using value_type = T;
	using size_type = size_t;
	using pointer = T*;
	using reference = T&;
	using const_pointer = const T*;
	using const_reference = const T&;
	using iterator = BDIterator<T>;
	using const_iterator = BDIterator<const T>;

public:
	List() = default;

	List(const std::initializer_list<value_type>& valueList)
	{
		for (auto& value : valueList)
			PushBack(value);
	}

	~List()
	{
		Clear();
	}

	void PushFront(value_type value)
	{
		Insert(value, 0);
	}

	void PushBack(value_type value)
	{
		Insert(value, m_nodeCount);
	}

	void Insert(value_type value, uint32_t position)
	{
		m_nodeCount++;
		assert(position < m_nodeCount);
		Node* newNode = new Node;
		newNode->record = value;

		// At beginning
		if (position == 0)
		{
			// If list is empty
			if (m_head == nullptr)
			{
				m_head = newNode;
				m_tail = m_head;
			}
			else
			{
				newNode->next = m_head;
				m_head->prev = newNode;
				m_head = newNode;
			}
		}
		// At end
		else if (position == m_nodeCount - 1)
		{
			m_tail->next = newNode;
			newNode->prev = m_tail;
			m_tail = newNode;
		}
		// In the middle
		else
		{
			Node* temp = m_head;
			// Traverse
			for (uint32_t i = 1; i < position; i++)
				temp = temp->next;

			newNode->next = temp->next;
			newNode->prev = temp;

			temp->next->prev = newNode;
			temp->next = newNode;
		}
	}

	void Clear()
	{
		if (m_head != nullptr)
		{
			Node* traverseNode = m_head;
			for (size_type i = 0; i < m_nodeCount; i++)
			{
				Node* memoryToDealloc = traverseNode;
				traverseNode = traverseNode->next;
				delete memoryToDealloc;
			}
			m_nodeCount = 0;
			m_head = nullptr;
			m_tail = m_head;
		}
	}

	reference Front()
	{
		assert(m_head != nullptr);
		return m_head->record;
	}

	const_reference Front() const
	{
		assert(m_head != nullptr);
		return m_head->record;
	}

	reference Back()
	{
		assert(m_tail != nullptr);
		return m_tail->record;
	}

	const_reference Back() const
	{
		assert(m_tail != nullptr);
		return m_tail->record;
	}

	iterator Begin()
	{
		assert(m_head != nullptr);
		return BDIterator<value_type>(m_head);
	}

	const_iterator Begin() const
	{
		assert(m_head != nullptr);
		return BDIterator<value_type>(m_head);
	}

	iterator End()
	{
		assert(m_tail != nullptr);
		return BDIterator<value_type>(m_tail->next);
	}

	const_iterator End() const
	{
		assert(m_tail != nullptr);
		return BDIterator<value_type>(m_tail->next);
	}

private:
	struct Node
	{
		Node* next = nullptr;
		Node* prev = nullptr;
		value_type record;
	};

	Node* m_head = nullptr;
	Node* m_tail = m_head;
	size_type m_nodeCount = 0;
};