
#ifndef _MEMORY_BLOCK_ALLOCATOR_H_
#define _MEMORY_BLOCK_ALLOCATOR_H_

//class btAllocator;
#include "mem_alloc.h"

//block allocator class thx to Allen Chou, 2013 
class btBlockAllocator : public btAllocator
{
	struct btBlockHeader
	{
		// union-ed with data
		btBlockHeader *Next;
	};

	struct btPageHeader
	{
		// followed by blocks in this page
		btPageHeader  *Next;

		// helper function that gives the first block
		btBlockHeader *Blocks(void)
		{
			return reinterpret_cast<btBlockHeader *>(this + 1);
		}
	};

public:
	// debug patterns
	static const unsigned char PATTERN_ALIGN = 0xFC;
	static const unsigned char PATTERN_ALLOC = 0xFD;
	static const unsigned char PATTERN_FREE = 0xFE;
	
	btBlockAllocator(void);
	btBlockAllocator(size_t dataSize, size_t pageSize, size_t alignment);
	virtual ~btBlockAllocator(void);

	// deallocates all memory
	virtual void	clear(void);

	virtual size_t	size(void);
	//free memory left
	virtual size_t	free(void);

	// resets the allocator to a new configuration
	void Reset(size_t dataSize, size_t pageSize, size_t alignment );

	// allocates a block of memory
	virtual void*	memAlloc(size_t size) override;

	// deallocates a block of memory
	virtual void	memFree(void *p) override;

private:
	// fill a free page with debug patterns
	void FillFreePage(btPageHeader  *p);

	// fill a free block with debug patterns
	void FillFreeBlock(btBlockHeader *p);

	// fill an allocated block with debug patterns
	void FillAllocatedBlock(btBlockHeader *p);

	// gets the next block
	btBlockHeader *NextBlock(btBlockHeader *p);

	// the page list
	btPageHeader *m_pageList;

	// the free list
	btBlockHeader *m_freeList;

	// size-related data
	size_t m_dataSize;
	size_t m_pageSize;
	size_t m_alignmentSize;
	size_t m_blockSize;
	size_t m_blocksPerPage;

	// statistics
	size_t m_numPages;
	size_t m_numBlocks;
	size_t m_numFreeBlocks;

	// disable copy & assignment
	btBlockAllocator(const btBlockAllocator &clone);
	btBlockAllocator &operator=(const btBlockAllocator &rhs);
};

static btBlockAllocator *LookUpAllocator(size_t size);

// allocates variable-sized memory blocks
void *bt_malloc(size_t size);

// frees variable-sized memory blocks
void bt_free(void *p, size_t size);


#endif // !_MEMORY_BLOCK_ALLOCATOR_H_
