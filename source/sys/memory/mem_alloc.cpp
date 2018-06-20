
#include "precompiled.h"
#pragma hdrstop

#include "mem_alloc.h"

void * operator new(size_t size)
{
	void *ptr = SDL_malloc(size);
#if 0
	if (!ptr)
		abort();
#else
	SDL_assert(ptr);
#endif
	return ptr;
}

void operator delete(void * ptr)
{
	if (ptr != nullptr)
		SDL_free(ptr);

	ptr = nullptr;
}

void * operator new[](size_t size)
{
	//void *ptr = SDL_calloc(size, );
	void *ptr = SDL_malloc(size);
#if 0
	if (!ptr)
		abort();
#else
	SDL_assert(ptr);
#endif

	return ptr;
}

void operator delete[](void * ptr)
{
	if (ptr != nullptr)
		SDL_free(ptr);

	ptr = nullptr;
}

void operator delete(void * ptr, size_t size)
{
	if (ptr != nullptr)
		SDL_free(ptr);

	ptr = nullptr;
}

#if 1
void *SDLCALL operator new(size_t s, btAllocator * Allocator)
{
	SDL_assert(Allocator);
	SDL_assert(Allocator->size() < s);
	return Allocator->memAlloc(s);
}

void SDLCALL operator delete(void * p, btAllocator * Allocator)
{
	SDL_assert(Allocator);
	if (p)
		Allocator->memFree(p);
}

void *SDLCALL operator new[](size_t s, btAllocator * Allocator)
{
	SDL_assert(Allocator);
	SDL_assert(Allocator->size() < s);
	return Allocator->memAlloc(s);
}

void operator delete[](void * p, btAllocator * Allocator)
{
	SDL_assert(Allocator);
	if (p)
		Allocator->memFree(p);
}
#endif