/*
 * Simple memory allocator code
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Harry Bovik",
    /* First member's email address */
    "bovik@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

static void *find_block(size_t s);
static void *coalesce(void *bp);
static void *extend_heap(size_t size);
static void *split_block(void *bp, size_t size);
static int is_block_splitable(void *bp, size_t size);
static void *allocate_block(void *bp, size_t size);

// size
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)
#define SIZE_T_SIZE sizeof(size_t)

// flags
#define ALLOCATED 1
#define PREV_ALLOCATED 2

// block pointer
#define HDRP(bp) ((char *)(bp)) - SIZE_T_SIZE
#define FTRP(bp) ((char *)(bp)) + (GET_SIZE(HDRP(bp)) - (2 * SIZE_T_SIZE))
#define PREV(bp) ((char *)bp) - GET_SIZE( ( (char *)bp ) - (2 * SIZE_T_SIZE) )
#define NEXT(bp) ((char *)bp) + GET_SIZE(HDRP(bp))

// pointer
#define GET(p) (*(size_t *)(p))
#define SET(p, val) (*(size_t *)(p)) = (val)
#define PACK(size, flags) ((size) | (flags)) 

#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_FLAGS(p) (GET(p) & 0x7)
#define SET_SIZE(p, val) GET(p) = ((GET(p) & 0x7) | val)
#define ADD_FLAGS(p, val) GET(p) |= val
#define REMOVE_FLAGS(p, val) GET(p) &= ~val
#define CHECK_FLAGS(p, flags) (GET(p) & flags) == flags

// Internal

// Points to the heap's prologue header
static char *start;

// Points to the last allocated block
static char *curr;

void mm_check() {
    void *bp = start;
    printf("Prologue header size: %zu\n", GET_SIZE(HDRP(bp)));
    printf("Prologue header flags: %zu\n", GET_FLAGS(HDRP(bp)));
    printf("Prologue header address: %p\n", HDRP(bp));
    bp = NEXT(bp);
    while(GET_SIZE(HDRP(bp)) != 0) {
	printf("Block size: %zu\n", GET_SIZE(HDRP(bp)));
	printf("Block flags: %zu\n", GET_FLAGS(HDRP(bp)));

	if(!(CHECK_FLAGS(HDRP(bp), ALLOCATED))) {
	    printf("Block footer size: %zu\n", GET_SIZE(FTRP(bp)));
	}
        bp = NEXT(bp);
    }

    printf("Epilogue header size: %zu\n", GET_SIZE(HDRP(bp)));
    printf("Epilogue header flags: %zu\n", GET_FLAGS(HDRP(bp)));
    printf("Epilogue header address: %p\n", HDRP(bp));
}

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    // Allocate enough for spacing, prologue header, and epilogue header
    size_t size = ALIGN(2 * SIZE_T_SIZE);
    int padding = size - (2 * SIZE_T_SIZE);

    start = mem_sbrk(size);
    
    if (start == NULL) {
	return -1;
    }

    // set prologue header
    SET(start + padding, PACK(SIZE_T_SIZE, 3));

    // Set start
    start += padding + SIZE_T_SIZE;
    curr = start;
    
    // Set epilogue header
    SET(start, PACK(0, 3));

    return 0;
}

/* 
 * Returns a pointer to a block of size "size". Returns NULL if the
 * heap cannot support a block of size "size".
 */
void *mm_malloc(size_t size)
{
    if (size == 0) {
	return NULL;
    }
    
    int newsize = ALIGN(size + SIZE_T_SIZE);

    void *bp;
    while ((bp = find_block(newsize)) == NULL) {
	if (extend_heap(mem_pagesize()) == NULL) {
	    return NULL;
	}
    }

    bp = allocate_block(bp, newsize);

    return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    REMOVE_FLAGS(HDRP(ptr), ALLOCATED);
    REMOVE_FLAGS(HDRP(NEXT(ptr)), PREV_ALLOCATED);

    SET(FTRP(ptr), PACK(GET_SIZE(HDRP(ptr)), 0));
    
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{  
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    
    newptr = mm_malloc(size);
    if (newptr == NULL)
	return NULL;
    copySize = *(size_t *)((char *)oldptr);
    if (size < copySize)
	copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}

/*
 * Helper function: find a free block that satisfies the size requirement starting at bp.
 *
 * Returns: NULL if no block found
 */
static void *find_block(size_t s) {
    char *initial = curr;
    do {
	if (GET_SIZE(HDRP(curr)) >= s && !(CHECK_FLAGS(HDRP(curr), ALLOCATED))) {
	    return curr;
	}
	if (GET_SIZE(HDRP(curr)) != 0) {
	    curr = NEXT(curr);
	} else {
	    curr = start;
	}
    } while (curr != initial);

    return NULL;
}

static void *allocate_block(void *bp, size_t size) {
    
    ADD_FLAGS(HDRP(bp), ALLOCATED);
    ADD_FLAGS(HDRP(NEXT(bp)), PREV_ALLOCATED);
    
        
    if (is_block_splitable(bp, size)) {
	split_block(bp, size);
    }

    return bp;
}

static int is_block_splitable(void *bp, size_t size) {
    size_t min_free_block_size = 2 * SIZE_T_SIZE;
    size_t orig_size = GET_SIZE(HDRP(bp));

    size_t diff = orig_size - size;
    if (diff >= min_free_block_size) {
	return 1;
    } else {
	return 0;
    }
}

static void *split_block(void *bp, size_t size) {
    size_t next_size = GET_SIZE(HDRP(bp)) - size;

    // Update header size
    SET_SIZE(HDRP(bp), size);

    void *next = NEXT(bp);

    // Create new block header and footer
    SET(HDRP(next), PACK(next_size, PREV_ALLOCATED));
    SET(FTRP(next), PACK(next_size, 0));

    // Set the following block as free
    REMOVE_FLAGS(HDRP(NEXT(next)), PREV_ALLOCATED);
    
    return bp;
}



static void *extend_heap(size_t size) {
    
    // Align the size
    int new_size = ALIGN(size);

    char *new = mem_sbrk(new_size);
    
    if (new == NULL) {
	return NULL;
    }
    // Convert epilogue footer to new block header
    REMOVE_FLAGS(HDRP(new), ALLOCATED);
    SET_SIZE(HDRP(new), new_size);
    // Create new block's footer

    SET(FTRP(new), PACK(new_size, 0));

    // Make new epilogue header
    SET(HDRP(NEXT(new)), PACK(0, 1));


    new = coalesce(new);

     return new;
}

static void *coalesce(void *bp) {
    if (!(CHECK_FLAGS(HDRP(bp), PREV_ALLOCATED))) {
	fflush(stdout);
	
	void *prev = PREV(bp);

	size_t combined_size = GET_SIZE(HDRP(bp)) + GET_SIZE(HDRP(prev));

	SET_SIZE(HDRP(prev), combined_size);
	SET_SIZE(FTRP(prev), combined_size);

	bp = prev;
    }

    void *next = NEXT(bp);
    if ( !(CHECK_FLAGS(HDRP(next), ALLOCATED)) ) {
	size_t combined_size = GET_SIZE(HDRP(next)) + GET_SIZE(HDRP(bp));

	SET_SIZE(HDRP(bp), combined_size);
	SET_SIZE(FTRP(bp), combined_size);

	REMOVE_FLAGS(HDRP(NEXT(bp)), PREV_ALLOCATED);
    }

    return bp;
}
		   
	
