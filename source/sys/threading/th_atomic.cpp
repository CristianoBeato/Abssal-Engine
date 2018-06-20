#include "precompiled.h"
#pragma hdrstop

#include "th_atomic.h"

btReferenceCounter::btReferenceCounter(void)
{
	SDL_AtomicSet(&RefCounter, 1);
}

btReferenceCounter::~btReferenceCounter(void)
{
}

void btReferenceCounter::IncRefCount(void)
{
	SDL_AtomicIncRef(&RefCounter);
}

void btReferenceCounter::DecRefCount(void)
{
	SDL_AtomicDecRef(&RefCounter);
}

void btReferenceCounter::SetRefCount(int val)
{
	SDL_AtomicSet(&RefCounter, val);
}

int btReferenceCounter::GetRefCount(void)
{
	return SDL_AtomicGet(&RefCounter);
}

void btRefObj::IncRefCount(void)
{
	btReferenceCounter::IncRefCount();
}

void btRefObj::DecRefCount(void)
{
	btReferenceCounter::DecRefCount();

	//clear pointer
	int count = GetRefCount();
	if (count < 1)
	{
		delete this;
	}
}

void btRefObj::IncRef(void * p)
{
	if (p != nullptr)
		reinterpret_cast<btRefObj*>(p)->IncRefCount();
}

void btRefObj::DecRef(void * p)
{
	if (p != nullptr)
		reinterpret_cast<btRefObj*>(p)->DecRefCount();
}
