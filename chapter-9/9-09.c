static void place(void *bp, size_t asize) {
  size_t s = GET_SIZE(HDRP(bp));
  
  // disregard bad input
  if(s < asize) {
      return;
  }

  // no block splitting
  if(s - asize < 2 * DSIZE) {
    PUT(HDRP(bp), PACK(s, 1));
    PUT(FTRP(bp), PACK(s, 1));
    return;
  }
  // allocated block header
  PUT(HDRP(bp), PACK(asize, 1));
  // allocated block footer
  PUT(FTRP(bp), PACK(asize, 1));

  bp = NEXT_BLKP(bp);
  
  // free block header
  PUT(HDRP(bp), PACK(s - asize, 0));
  // free block footer
  PUT(FTRP(bp), PACK(s - asize, 0));

  return;
}

  
