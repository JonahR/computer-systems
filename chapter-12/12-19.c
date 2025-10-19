/* Global variables */
int readcnt; /* Initially = 0 */
sem_t mutex, w, wlock; /* All initially = 1 */


void reader(void)
{
  while (1) {
    P(&mutex);
    readcnt++;
    if (readcnt == 1) { /* First in */
      P(&wlock);
      P(&w);
    }
    V(&mutex);

    /* Critical section */
    /* Reading happens */

    P(&mutex);
    readcnt--;
    if (readcnt == 0) { /* Last out */
      V(&w);
      V(&wlock);
    }
  
    V(&mutex);
  }
}

void writer(void)
{
  while (1) {
    P(&w);

    /* Critical section */
    /* Writing happens */

    V(&w);

    P(&wlock); /* Wait until waiting reader unlocks */
    V(&wlock);
  }
}

/*
  How can I make it so when writer finishes, if there is a waiting reader
  it is always selected?

  Before "P(&w), I need to add a semaphore.
*/
