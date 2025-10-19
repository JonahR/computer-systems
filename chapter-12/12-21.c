/* Globals */
int pendingwrites; /* Initially = 0 */
sem_t mutex, w;

void reader(void)
{
  while (1) {
    if (pendingwrites > 0) { /* Give writes priority */
      continue;

    P(&w);
    /* Critical section */
    /* Reading happens */
    V(&w);
    
    }
}


void writer(void)
{
  while (1) {
    P(&mutex);
    pendingwrites++;
    V(&mutex);
    
    P(&w);

    P(&mutex);
    pendingwrites--;
    V(&mutex);

    /* Critical section */
    /* Writing happens */

    V(&w);

  }
}
