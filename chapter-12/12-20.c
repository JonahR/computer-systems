#define N 16

sem_t mutex; /* Initially = 1 */
sem_t cnt; /* Initially = N */

void reader(void)
{
  while (1) {
    P(&cnt);
    P(&w); /* Check if writing */
        
    /* Critical section */
    /* Reading happens */

    V(&w);
    V(&cnt);
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


