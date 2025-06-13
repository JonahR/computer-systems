static void *find_fit(size_t asize) {
  void *curr = NEXT_BLKP(heap_listp);
  size_t s;
  
  // Checks if the current block is the Epilogue block hdr
  while ((s = GET_SIZE(HDRP((curr))) != 0) {
      if (!GET_ALLOC(HDRP(curr)) && s > asize) {
	return curr;
      }
      curr = NEXT_BLKP(curr);
  }
  return NULL;
}

