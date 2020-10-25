#pragma once

#include <iterator>
#include <compare>

///
/// Random access iterator class
/// 
/// This class was created in order to work with
/// custom container classes.
/// 

template <class TContainer>
class RAIterator
{
public:
	// @NOTE: stl algorithms expects exactly named traits such as below.
	using iterator_category = std::random_access_iterator_tag;
	using value_type = typename TContainer::value_type;
	using pointer = typename TContainer::pointer;
	using reference = typename TContainer::reference;
	using const_pointer = typename TContainer::const_pointer;
	using const_reference = typename TContainer::const_reference;
	using difference_type = std::ptrdiff_t;
public:
	RAIterator() = default;

	RAIterator(pointer parg)	// allows implicit nullptr conversion
		: m_parg(parg)
	{
	}

	explicit constexpr operator bool() const { return m_parg != nullptr; }

	constexpr reference operator *() { return *m_parg; }
	constexpr const_reference operator *() const { return *m_parg; }
	constexpr pointer operator ->() { return m_parg; }

	constexpr std::strong_ordering operator <=>(const RAIterator& other) const = default;

	constexpr RAIterator operator +(const difference_type& movement) { return RAIterator(m_parg + movement); }
	constexpr RAIterator operator -(const difference_type& movement) { return RAIterator(m_parg - movement); }

	constexpr RAIterator& operator +=(const difference_type& movement) { m_parg += movement; return *this; }
	constexpr RAIterator& operator -=(const difference_type& movement) { m_parg -= movement; return *this; }

	constexpr RAIterator& operator ++() { m_parg++; return *this; }
	constexpr RAIterator& operator --() { m_parg--; return *this; }
	constexpr RAIterator operator ++(int) { pointer tempPtr = m_parg; m_parg++; return RAIterator(tempPtr); }
	constexpr RAIterator operator --(int) { pointer tempPtr = m_parg; m_parg--; return RAIterator(tempPtr); }

	constexpr difference_type operator -(const RAIterator& other) { return std::distance(m_parg, other.m_parg); }

	constexpr pointer Get() { return m_parg; }
	constexpr const_pointer Get() const { return m_parg; }

protected:
	pointer m_parg = nullptr;
};

template<typename T>
typename RAIterator<T>::difference_type operator -(
	const RAIterator<T>& lhs,
	const RAIterator<T>& rhs)
{
	return lhs.Get() - rhs.Get();
}