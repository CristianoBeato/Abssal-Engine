/*
*/


#ifndef _ATOMIC_H_
#define _ATOMIC_H_

//reference-countable class structure
class btReferenceCounter
{
public:
	btReferenceCounter(void);
	virtual ~btReferenceCounter(void);

	virtual void	IncRefCount(void);
	virtual void    DecRefCount(void);
	virtual void	SetRefCount(int val);
	virtual int		GetRefCount(void);

private:
	SDL_atomic_t	RefCounter;
};

// Intrusive reference-countable object for garbage collection
class btRefObj : public btReferenceCounter
{
public:
	btRefObj(void) : btReferenceCounter(){};
	virtual ~btRefObj(void) {};

	virtual void	IncRefCount(void);
	virtual void    DecRefCount(void);

	//utils for reference counter
	static void IncRef(void* p);
	static void DecRef(void* p);
private:

};



#endif // !_ATOMIC_H_
