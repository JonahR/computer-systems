static char *heap_lastp = NULL;

static void *next_fit(size_t asize) {
  // First call to next_fit.
  if (heap_lastp == NULL) {
    heap_lastp = heap_listp;
  }
  void *next = NEXT_BLKP(heap_lastp);

  /*
    We need to write code that treats the Heap as a circular
    buffer. If we can't find space before the end (epilogue)
    we will start the search at the beginning (prologue). Only
    if we wrap around back the to heap_lastp block we should
    return NULL, and the memory allocator will take care of
    extending the HEAP
  */
  
  while (next != heap_lastp) {
    // We are at the epilogue block. We want to start at the beginning
    if (GET_SIZE(HDRP(next)) == 0) {
      next = NEXT_BLKP(heap_listp);
      continue;
    }

    // Match. Block is not allocated and can fit the requested size.
    // We assume each block has WSIZE overhead for the header
    // Set heap_lasp to the match
    if (!GET_ALLOC(HDRP(next)) && (GET_SIZE(HDRP(next)) >= asize)) {
      heap_lastp = next;
      return next;
    }

    next = NEXT_BLKP(next);
  }

  // No match found
  return NULL;
}
