
#ifndef _THREADING_CRITICAL_SECTION_H_
#define _THREADING_CRITICAL_SECTION_H_

/*
===============================================================================
btMutex
===============================================================================
*/
class btMutex
{
public:
	btMutex(void);
	~btMutex(void);

	bool	tryLock(void) const;
	void	lock(void) const;
	void	unlock(void) const;

private:
	SDL_mutex*	m_mtxHandle;

	//to give acess to the mutex handler
	friend class btCondition;
};

//mutex auto Lock 
//Resource Acquisition Is Initilization, based on Allen Chou
//Scope - Based Resource Management(RAII), tips
class btMutexLock
{
public:
	btMutexLock(btMutex* mtx);
	~btMutexLock(void);

private:
	btMutex*	m_mutex;
};


#endif // !_THREADING_CRITICAL_SECTION_H_
