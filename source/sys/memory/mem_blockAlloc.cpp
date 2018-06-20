
#include "precompiled.h"
#pragma hdrstop

#include "mem_blockAlloc.h"

// sorted from smallest to largest
static const unsigned k_blockSizes[] =
{
	//4 - increments
	4, 8, 12, 16,
	//8- increments
	24, 32, 40, 48,
	//16 - increments
	64, 80, 96, 112,
	//32 - increments
	128, 160, 192, 224,
	// 64 - increments
	256, 320, 384, 448,
	// 128 - increments
	512, 640, 768, 896,
	// 256 - increments
	1024, 1280, 1536, 1792,
	// 512 - increments
	2048, 2560, 3072, 3584,
	// 
	4096
};

static const unsigned k_pageSize = 8192;
static const unsigned k_alignment = 4;

// number of elements in the block size array
static const unsigned k_numBlockSizes = sizeof(k_blockSizes) / sizeof(k_blockSizes[0]);

// largest valid block size
static const unsigned k_maxBlockSize = k_blockSizes[k_numBlockSizes - 1];

static unsigned *s_blockSizeLookup = nullptr;
static btBlockAllocator s_allocators[k_numBlockSizes];

btBlockAllocator *LookUpAllocator(size_t size)
{
	// one-time initialization
	static bool s_initialized = false;
	if (!s_initialized)
	{
		// initialize block size lookup
		s_blockSizeLookup =	new size_t[k_maxBlockSize + 1];
		size_t j = 0;
		for (size_t i = 0; i <= k_maxBlockSize; ++i)
		{
			if (i > k_blockSizes[j])
				++j;

			s_blockSizeLookup[i] = j;
		}

		// initialize allocators
		for (size_t i = 0; i < k_numBlockSizes; ++i)
		{
			s_allocators[i].Reset
			(k_blockSizes[i], k_pageSize, k_alignment);
		}

		s_initialized = true;
	}

	// check eligibility for lookup
	if (size <= k_maxBlockSize)
		return s_allocators + s_blockSizeLookup[size];
	else
		return nullptr;
}

btBlockAllocator::btBlockAllocator(void):
	btAllocator(),
	m_pageList(nullptr),
	m_freeList(nullptr)
{
}

btBlockAllocator::btBlockAllocator(const size_t dataSize, const size_t pageSize, const size_t alignment):
	btAllocator(),
	m_pageList(nullptr),
	m_freeList(nullptr)
{
	Reset(dataSize, pageSize, alignment);
}

btBlockAllocator::~btBlockAllocator(void)
{
	clear();
}

void btBlockAllocator::clear(void)
{
	// free all pages
	btPageHeader *pageWalker = m_pageList;
	while (pageWalker)
	{
		btPageHeader *currPage = pageWalker;
		pageWalker = pageWalker->Next;

		delete[] reinterpret_cast<char *>(currPage);
	}

	// release pointers
	m_pageList = nullptr;
	m_freeList = nullptr;

	// re-init stats
	m_numPages = 0;
	m_numBlocks = 0;
	m_numFreeBlocks = 0;
}

size_t btBlockAllocator::size(void)
{
	return size_t();
}

size_t btBlockAllocator::free(void)
{
	return size_t();
}

void btBlockAllocator::Reset(const size_t dataSize, const size_t pageSize, const size_t alignment)
{
	clear();

	m_dataSize = dataSize;
	m_pageSize = pageSize;

	size_t maxHeaderData = SDL_max(sizeof(btBlockHeader), m_dataSize);

	m_alignmentSize = (maxHeaderData % alignment) ? (alignment - maxHeaderData % alignment) : (0);

	m_blockSize = maxHeaderData + m_alignmentSize;

	m_blocksPerPage = (m_pageSize - sizeof(btPageHeader)) / m_blockSize;
}

void * btBlockAllocator::memAlloc(size_t size)
{
	// free list empty, create new page
	if (!m_freeList)
	{
		// allocate new page
		btPageHeader *newPage = reinterpret_cast<btPageHeader *>(new char[m_pageSize]);
		++m_numPages;
		m_numBlocks += m_blocksPerPage;
		m_numFreeBlocks += m_blocksPerPage;

		FillFreePage(newPage);

		// page list not empty, link new page
		if (m_pageList)
			newPage->Next = m_pageList;

		// push new page
		m_pageList = newPage;

		// link new free blocks
		btBlockHeader *currBlock = newPage->Blocks();
		for (unsigned i = 0; i < m_blocksPerPage - 1; ++i)
		{
			currBlock->Next = NextBlock(currBlock);
			currBlock = NextBlock(currBlock);
		}
		currBlock->Next = nullptr; // last block

								   // push new blocks
		m_freeList = newPage->Blocks();
	}

	// pop free block
	btBlockHeader *freeBlock = m_freeList;
	m_freeList = m_freeList->Next;
	--m_numFreeBlocks;

	FillAllocatedBlock(freeBlock);

	return freeBlock;
}

void btBlockAllocator::memFree(void * p)
{
	// retrieve block header
	btBlockHeader *block = reinterpret_cast<btBlockHeader *>(p);

	FillFreeBlock(block);

	// push block
	block->Next = m_freeList;
	m_freeList = block;
	++m_numFreeBlocks;
}

void btBlockAllocator::FillFreePage(btPageHeader * p)
{
	// page header
	p->Next = nullptr;

	// blocks
	btBlockHeader *currBlock = p->Blocks();
	for (unsigned i = 0; i < m_blocksPerPage; ++i)
	{
		FillFreeBlock(currBlock);
		currBlock = NextBlock(currBlock);
	}
}

void btBlockAllocator::FillFreeBlock(btBlockHeader * p)
{
	// block header + data
	//std::memset(p, PATTERN_FREE, m_blockSize - m_alignmentSize);
	SDL_memset(p, PATTERN_FREE, m_blockSize - m_alignmentSize);

	// alignment
	//std::memset(reinterpret_cast<char *>(p)+ m_blockSize - m_alignmentSize, PATTERN_ALIGN, m_alignmentSize);
	SDL_memset(reinterpret_cast<char *>(p) + m_blockSize - m_alignmentSize, PATTERN_ALIGN, m_alignmentSize);
}

void btBlockAllocator::FillAllocatedBlock(btBlockHeader * p)
{
	// block header + data
	//std::memset(p,	PATTERN_ALLOC, m_blockSize - m_alignmentSize);
	SDL_memset(p, PATTERN_ALLOC, m_blockSize - m_alignmentSize);

	// alignment
	//std::memset(reinterpret_cast<char *>(p)+ m_blockSize - m_alignmentSize, PATTERN_ALIGN, m_alignmentSize);
	SDL_memset(reinterpret_cast<char *>(p) + m_blockSize - m_alignmentSize, PATTERN_ALIGN, m_alignmentSize);
}

btBlockAllocator::btBlockHeader * btBlockAllocator::NextBlock(btBlockHeader * p)
{
	return nullptr;
}

/*
btBlockAllocator & btBlockAllocator::operator=(const btBlockAllocator & rhs)
{
	// TODO: insert return statement here
	return btBlockAllocator(0,0 ,0);
}
*/

void * bt_malloc(size_t size)
{
	btBlockAllocator *alloc = LookUpAllocator(size);
	if (alloc)
		return alloc->memAlloc(0);
	else
		return SDL_malloc(size);
}

void bt_free(void * p, size_t size)
{
	btBlockAllocator *alloc = LookUpAllocator(size);
	if (alloc)
		alloc->memFree(p);
	else
		SDL_free(p);
}
