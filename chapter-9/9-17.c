#include <stdlib.h>

// Develop an allocator that performs a next-fit search instead of first-fit

// heap_listp: always points to the prologue block
// GET_SIZE: reads size for current block
// HDRP: Given bp, gives the address of the header
// NEXT_BLKP: Given bp, gives the address of the next bp
// GET_ALLOC: Gives if bp is currently allocated

// Need to create our own prev_bp variable.

static char *prev_bp = heap_listp;

static void *find_fit(size_t asize)
{
	void *bp = NEXT_BLCK(bp);

	while (bp != prev_bp) {
		if (!GET_ALLOC(HDPR(bp)) && asize <= GET_SIZE(HDRP(bp))) {
			prev_bp = bp;
			return bp;
		}

		if (GET_SIZE(HDPR(bp)) > 0) {
			bp = NEXT_BLCK(bp);
		} else {
			bp = NEXT_BLCK(heap_listp);
		}

	}
	return NULL;
}