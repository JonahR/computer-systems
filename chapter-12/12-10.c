/* Global variables */
int readcnt; /* Initially = 0 */
sem_t mutex, w; /* Both initially = 1 */

void reader(void)
{
  while (1) {
    P(&mutex);
    readcnt++;
    if (readcnt == 1) /* First in */
      P(&w);
    V(&mutex);

    /* Critical section */
    /* Reading happens */

    P(&mutex);
    readcnt--;
    if (readcnt == 0) /* Last out */
      V(&w);
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
  }
}

/*
  When a writer finishes its critical section, it increments the w semaphore.
  If a large number of threads executing the writer method are scheduled in
  front of a thread executing the reader method, all those writing threads
  must complete before the reader can begin execution. This is because when
  the writer completes, the next writer can immediately begin.
*/
