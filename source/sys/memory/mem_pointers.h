
#ifndef _MEM_POINTERS_H_
#define _MEM_POINTERS_H_

/*
*/


/*
===================================================================================
btSmartPtr
smart pointer to Scope-Based Resource Management (RAII) 
based on Allen Chou, October 1, 2014, 
http://allenchou.net/2014/10/scope-based-resource-management-raii/
===================================================================================
*/
template <typename T>
class btSmartPtr
{
public:
	btSmartPtr(T *ptr);
	~btSmartPtr(void);

	//
	bool	validade(void);

	//acess operators
	inline T &operator*(void);
	inline T *operator->(void);

	// helpers
	inline T*		getInternalPtr(void) const;
	inline size_t	getInternalSize(void) const;

	//casting
	template <typename U> inline btSmartPtr<U> dynamicCast(void) const;
	template <typename U> inline btSmartPtr<U> staticCast(void) const;

private:
	T * m_ptr;
};

template<typename T>
inline btSmartPtr<T>::btSmartPtr(T * ptr) : m_ptr(ptr)
{
}

template<typename T>
inline btSmartPtr<T>::~btSmartPtr(void)
{
	if (m_ptr != nullptr)
	{
		delete m_ptr;
		m_ptr = nullptr;
	}
}

template<typename T>
inline bool btSmartPtr<T>::validade(void)
{
	return m_ptr != nullptr;
}

template<typename T>
inline T & btSmartPtr<T>::operator*(void)
{
	return *m_ptr;
}

template<typename T>
inline T * btSmartPtr<T>::operator->(void)
{
	return m_ptr;
}

template<typename T>
inline T * btSmartPtr<T>::getInternalPtr(void) const
{
	return m_ptr;
}

template<typename T>
inline size_t btSmartPtr<T>::getInternalSize(void) const
{
	return sizeof(m_ptr);
}

template<typename T>
template<typename U>
inline btSmartPtr<U> btSmartPtr<T>::dynamicCast(void) const
{
	return btSmartPtr<U>(dynamic_cast<U*>(m_ptr));
}

template<typename T>
template<typename U>
inline btSmartPtr<U> btSmartPtr<T>::staticCast(void) const
{
	return btSmartPtr<U>(static_cast<U*>(m_ptr));
}

/*
===================================================================================
btIntrusivePtr
Intrusive smart pointer, whit atomic counter,
Based on Sergey Kosarevsky and Viktor Latypov, from Linderdaum Engine 
http://www.linderdaum.com
===================================================================================
*/
template <typename T>
class btIntrusivePtr
{
public:
	//default constructor
	btIntrusivePtr(void);
	// copy constructor
	btIntrusivePtr(const btIntrusivePtr& Ptr);
	template <typename U>
	btIntrusivePtr(const btIntrusivePtr<U>& Ptr);
	//type constructor
	btIntrusivePtr(T* const Object);

	~btIntrusivePtr(void);

	// check if the pointer is valid
	bool	validate(void) const;

	//manualy clear the ptr
	void clear(void);

	//acess operators
	inline T &operator*(void);
	inline const T &operator*(void) const;
	inline T *operator->(void);
	inline const T *operator->(void) const;

	// assignment of clPtr
	inline btIntrusivePtr& operator = (const btIntrusivePtr& Ptr);

	// helper
	inline T* getInternalPtr(void) const;

	//casting
	template <typename U> inline btIntrusivePtr<U> dynamicCast(void) const;
	template <typename U> inline const U* dynamicCastType(void) const;
	template <typename U> inline const btIntrusivePtr<U> staticCast(void) const;
	template <typename U> inline btIntrusivePtr<U> staticCast(void);
	template <typename U> inline const U* staticCastType(void) const;

private:
	T * m_ptr;
};

template<typename T>
inline btIntrusivePtr<T>::btIntrusivePtr(void) : m_ptr(nullptr)
{
}

template<typename T>
inline btIntrusivePtr<T>::btIntrusivePtr(const btIntrusivePtr & Ptr) : m_ptr(Ptr.m_ptr)
{
	btRefObj::IncRef(m_ptr);
}

template<typename T>
inline btIntrusivePtr<T>::btIntrusivePtr(T * const Object) : m_ptr(Object)
{
	btRefObj::IncRef(m_ptr);
}

template<typename T>
inline btIntrusivePtr<T>::~btIntrusivePtr(void)
{
	btRefObj::DecRef(m_ptr);
}

template<typename T>
inline bool btIntrusivePtr<T>::validate(void) const
{
	return m_ptr != nullptr;
}

template<typename T>
inline void btIntrusivePtr<T>::clear(void)
{
	delete m_ptr;
	m_ptr = nullptr;
}

template<typename T>
inline T & btIntrusivePtr<T>::operator*(void)
{
	return *m_ptr;
}

template<typename T>
inline const T & btIntrusivePtr<T>::operator*(void) const
{
	return *m_ptr;
}

template<typename T>
inline T * btIntrusivePtr<T>::operator->(void)
{
	return m_ptr;
}

template<typename T>
inline const T * btIntrusivePtr<T>::operator->(void) const
{
	return m_ptr;
}

template<typename T>
inline btIntrusivePtr<T> & btIntrusivePtr<T>::operator=(const btIntrusivePtr<T> & Ptr)
{
	T* Temp = m_ptr;
	m_ptr = Ptr.m_ptr;

	btRefObj::IncRef(Ptr.m_ptr);
	btRefObj::DecRef(Temp);

	return *this;
}

template<typename T>
inline T * btIntrusivePtr<T>::getInternalPtr(void) const
{
	return m_ptr;
}

template<typename T>
template<typename U>
inline btIntrusivePtr<U> btIntrusivePtr<T>::dynamicCast(void) const
{
	return btIntrusivePtr<U>(dynamic_cast<U*>(m_ptr));
}

template<typename T>
template<typename U>
inline const U * btIntrusivePtr<T>::dynamicCastType(void) const
{
	return dynamic_cast<const U*>(m_ptr);
}

template<typename T>
template<typename U>
inline const btIntrusivePtr<U> btIntrusivePtr<T>::staticCast(void) const
{
	return btIntrusivePtr<U>(static_cast<U*>(m_ptr));
}

template<typename T>
template<typename U>
inline btIntrusivePtr<U> btIntrusivePtr<T>::staticCast(void)
{
	return btIntrusivePtr<U>(static_cast<U*>(m_ptr));
}

template<typename T>
template<typename U>
inline const U * btIntrusivePtr<T>::staticCastType(void) const
{
	return static_cast<const U*>(m_ptr);
}

#endif // !_MEM_POINTERS_H_