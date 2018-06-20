
#ifndef _MEM_ALLOC_H_
#define _MEM_ALLOC_H_

class btAllocator
{
public:
	btAllocator(void) {};
	virtual ~btAllocator(void) {};
	//total alocator memory
	virtual size_t	size(void) = 0;
	//free memory left
	virtual size_t	free(void) = 0;
	//clear the allocated memory
	virtual void	clear(void) =0;

	virtual void*	memAlloc(size_t size) { return nullptr; };
	virtual void	memFree(void *p ) { p = nullptr; };
	
	template<typename U> U*	memAlloc(void) { memAlloc(sizeof(U)); };
	template<typename U> U*	memAlloc(size_t num) { memAlloc(sizeof(U) * num); };
	template<typename U> void	memFree(U * p) { memFree(p); };

private:

};

#ifndef new
#undef new
#endif // !new

//new operation whit SDL_malloc
extern void* SDLCALL operator new(size_t size);

//delete operation using SDL_free
extern void SDLCALL operator delete(void* p);

//new operator allocate a array 
extern void* SDLCALL operator new[](size_t size);

//array delete operator 
extern void SDLCALL operator delete[](void* p);

extern void SDLCALL operator delete(void*  p, size_t size);

//new whit initializer 
template<typename T>
inline void* SDLCALL operator new(size_t size, T t)
{
	void *ptr = SDL_malloc(size);
#if 0
	if (!ptr)
		abort();
#else
	SDL_assert(ptr);
#endif

	*ptr = t;
	return ptr;
}

template<typename T>
inline void* SDLCALL operator new[](size_t size, T t)
{
	void *p = SDL_calloc(size, sizeof(T));
	if (!p)
		abort();

	return p;
}

template<typename T>
inline void SDLCALL operator delete(void* ptr, T t)
{
	reinterpret_cast<T *>(ptr)->~T();
	if (ptr != nullptr)
		SDL_free(ptr);

	ptr = nullptr;
}

//allocale a new poiter using memory from a allocator
extern void* SDLCALL operator new(size_t s, btAllocator *Allocator);

//delete a pointer using memory from a allocator
extern void SDLCALL operator delete(void* p, btAllocator *Allocator);

//allocate a array using memory from a allocator
extern void* SDLCALL operator new[](size_t s, btAllocator *Allocator);

//clear memory using pointer from a allocator
extern void operator delete[](void* p, btAllocator *Allocator);

#endif // !_MEM_ALLOC_H_