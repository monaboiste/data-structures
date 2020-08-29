#pragma once

///
/// Random access iterator class
/// 
/// Doesn't work with stl algorithms.
/// This class was created in order to work with
/// custom container classes.
/// 

template <class T>
class RAIterator
{
public:
	using category = std::random_access_iterator_tag;
	using valueType = T;
	using pointer = T*;
	using reference = T&;
	using constPointer = const T*;
	using constReference = const T&;
	using differenceType = std::ptrdiff_t;
public:
	RAIterator() = default;

	RAIterator(pointer parg)	// allows implicit nullptr conversion
		: m_parg(parg)
	{
	}

	explicit constexpr operator bool() const { return m_parg != nullptr; }

	constexpr reference operator *() { return *m_parg; }
	constexpr constReference operator *() const { return *m_parg; }
	constexpr pointer operator ->() { return m_parg; }

	constexpr bool operator ==(const RAIterator& other) { return m_parg == other.m_parg; }
	constexpr bool operator !=(const RAIterator& other) { return !(m_parg == other.m_parg); }

	constexpr RAIterator operator +(const differenceType& movement) { return RAIterator(m_parg + movement); }
	constexpr RAIterator operator -(const differenceType& movement) { return RAIterator(m_parg - movement); }

	constexpr RAIterator& operator +=(const differenceType& movement) { m_parg += movement; return *this; }
	constexpr RAIterator& operator -=(const std::ptrdiff_t& movement) { m_parg -= movement; return *this; }

	constexpr RAIterator& operator ++() { m_parg++; return *this; }
	constexpr RAIterator& operator --() { m_parg--; return *this; }
	constexpr RAIterator operator ++(int) { T* tempPtr = m_parg; m_parg++; return RAIterator(tempPtr); }
	constexpr RAIterator operator --(int) { T* tempPtr = m_parg; m_parg--; return RAIterator(tempPtr); }

	constexpr differenceType operator -(const RAIterator& other) { return std::distance(m_parg, other.m_parg); }

	constexpr pointer Get() { return m_parg; }
	constexpr constPointer Get() const { return m_parg; }

protected:
	pointer m_parg = nullptr;
};