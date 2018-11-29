/*
 * Physical memory allocator
 * Bitmap based
 * Marcos Medeiros
 */
#ifdef USE_MM_C
/*
 * pf - page frame
 * pfbb - page frame bitmap block
 */
#include "Std_Types.h"
#include "io.h"
#include "mm.h"

#define PAGE_SIZE_MSK (PAGE_SIZE-1)
#define BITMAP_PAGES	((MEMORY_SIZE / PAGE_SIZE) / 8)

static uint8_t pf_bitmap[BITMAP_PAGES];		/* 4kb frames */
static uint32_t __next_page = 0;
static const uint32_t total_frames = (MEMORY_SIZE / PAGE_SIZE);
static uint32_t n_alloc_pages = 0;
extern int _start;
extern int _end;
/*
 * Find first free page in whole pf_bitmap
 */
uint32_t pf_find_free()
{
	uint32_t page = 0;
	for (page = 0; page < BITMAP_PAGES; page++) {
		uint8_t blk_info = pf_bitmap[page];
		if (blk_info != 0xff) {
			uint32_t bit = 0;
			for (bit = 0; bit < 8; bit++) {
				if (!(blk_info & 0x80)) {
					return ((page << 3) | (bit & 7));
				}
				blk_info <<= 1;
			}
		}
	}
	return 0xffffffff;
}


uint32_t pf_state(uint32_t page)
{
	int pfblk_addr = 0;
	int pfblk_bit = 0;
	uint8_t blk_info = 0;

	if (page >= BITMAP_PAGES)
		return 0;

	pfblk_addr = page >> 3;
	pfblk_bit = 7 ^ (page & 7);

	blk_info = pf_bitmap[pfblk_addr];
	
	return (blk_info >> pfblk_bit) & 1;
}

/* 
 * Mark one page as free or allocated
 */
uint32_t pf_mark(uint32_t page, uint32_t is_free)
{
	int pfblk_addr = 0;
	int pfblk_bit = 0;
	uint8_t blk_info = 0;
	uint32_t result = 0;

	if (page >= BITMAP_PAGES)
		return result;

	pfblk_addr = page >> 3;
	pfblk_bit = 7 ^ (page & 7);

	blk_info = pf_bitmap[pfblk_addr];
	if (is_free) {
		/* Check if the page is allocated */
		if ((blk_info & (1 << pfblk_bit)))
			result = 1;

		/* If the page is at position less than current next free page
		 * then we set this as next free page.
		 */
		if (page < __next_page)
			__next_page = page;
		if (result) {
			blk_info &= ~(1 << pfblk_bit);
			pf_bitmap[pfblk_addr] = blk_info;
		}
	}
	else {
		/* Check if the page is free */
		if (!(blk_info & (1 << pfblk_bit)))
			result = 1;

		if (result) {
			blk_info |= (1 << pfblk_bit);
			pf_bitmap[pfblk_addr] = blk_info;
			/* If the current page that is being marked as allocated is the current
			 * next free page, then we find another next free page and mark
			 * this as allocated.
			 */
			if (page == __next_page)
				__next_page = pf_find_free();
		}
	}

	return result;
}



void *pf_alloc()
{
	/* Out of memory */
	if (__next_page == 0xffffffff)
		return NULL;

	void *ptr = (void *) (__next_page * PAGE_SIZE);
	if (pf_mark(__next_page, 0))
		n_alloc_pages++;

	return ptr;
}

/*
 * Slow =/
 */
void *page_alloc_align(uint32_t align, uint32_t pages)
{
	uint32_t pg = 0;
	uint32_t fit = 0;
	uint32_t res = 0;

	/* no alignment */
	if (align == 0)
		align = 1;

	for (; pg < total_frames; pg += align) {
		if (pf_state(pg))
			continue;
		res = 1;
		for (fit = 1; fit < pages; fit++) {
			if (pf_state(pg + fit)) {
				res = 0;
				break;
			}
		}
		if (res) {
			for (fit = 0; fit < pages; fit++)
				pf_mark(pg + fit, 0);
			return (void *) (pg * PAGE_SIZE);
		}
	}

	return NULL;
}

void *page_frame_alloc()
{
	return pf_alloc();
}

void pf_free(void *ptr)
{
	uint32_t addr = (uint32_t) ptr;
	/* We can't free kernel pages */
	if (addr <= (uint32_t)(&_end))
		return;
	addr >>= 12;
	if (pf_mark(addr, 1)) {
		if (n_alloc_pages)
			--n_alloc_pages;
	}
}

/*
 * Allocate kernel pages
 */
void pf_mark_kernel()
{
	uint32_t kpages = 0;
	uint32_t end = (uint32)(&_end);
	uint32_t i = 0;
	/* Align end to page frame boundary 4kb */
	if (end & PAGE_SIZE_MSK) {
		end += PAGE_SIZE;
		end &= ~PAGE_SIZE_MSK;
	}
	
	kpages = (end / PAGE_SIZE);// >> 12;
	/* Just allocate first 'kpages' */
	for (i = 0; i < kpages; i++)
		pf_alloc();
}


void mm_init()
{
	memclr(pf_bitmap, BITMAP_PAGES);

	pf_mark_kernel();

	kmalloc_init();
	paging_init();

}

#endif
