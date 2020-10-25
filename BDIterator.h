#pragma once

#include <iterator>

///
/// Bidirectional iterator class
/// 
/// This class was created in order to work with
/// list container class.
/// 

template <class TList>
class BDIterator
{
	template <class>
	friend class List;
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = typename TList::value_type;
	using pointer = typename TList::pointer;
	using reference = typename TList::reference;
	using const_pointer = typename TList::const_pointer;
	using const_reference = typename TList::const_reference;
	using difference_type = std::ptrdiff_t;
	using node_pointer = typename List<value_type>::Node*;
public:
	BDIterator() = default;

	BDIterator(node_pointer node)
		: m_node(node)
	{
	}

	explicit constexpr operator bool() const { return m_node != nullptr; }

	constexpr reference operator *() { return m_node->record; }
	constexpr const_reference operator *() const { return m_node->record; }
	constexpr pointer operator ->() { return &(m_node->record); }

	constexpr bool operator ==(const BDIterator& other) const = default;
	constexpr bool operator !=(const BDIterator& other) const = default;

	constexpr BDIterator& operator ++() { m_node = m_node->next; return *this; }
	constexpr BDIterator& operator --() { m_node = m_node->prev; return *this; }
	constexpr BDIterator operator ++(int) { BDIterator tempNode = m_node; m_node = m_node->next; return BDIterator(tempNode); }
	constexpr BDIterator operator --(int) { BDIterator tempNode = m_node; m_node = m_node->prev; return BDIterator(tempNode); }

	constexpr pointer Get() { return &(m_node->record); }
	constexpr const_pointer Get() const { return &(m_node->record); }

protected:
	node_pointer m_node = nullptr;
};