#include "precompiled.h"
#pragma hdrstop

#include "th_criticalSection.h"

btMutex::btMutex(void)
{
	m_mtxHandle = SDL_CreateMutex();
	SDL_assert(m_mtxHandle);
}

btMutex::~btMutex(void)
{
	SDL_DestroyMutex(m_mtxHandle);
	m_mtxHandle = nullptr;
}

bool btMutex::tryLock(void) const
{
	return (SDL_TryLockMutex(m_mtxHandle) != -1);
}

void btMutex::lock(void) const
{
	SDL_assert(SDL_LockMutex(m_mtxHandle) != -1);
}

void btMutex::unlock(void) const
{
	SDL_assert(SDL_UnlockMutex(m_mtxHandle) != -1);
}

btMutexLock::btMutexLock(btMutex * mtx) : m_mutex(mtx)
{
	m_mutex->lock();
}

btMutexLock::~btMutexLock(void)
{
	m_mutex->unlock();
}
