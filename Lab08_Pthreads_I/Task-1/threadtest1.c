#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  long int i;
  double sum;
  printf("%s tarting doing some work.\n", __func__);
  for(i = 0; i < 1000000000; i++)
    sum += 1e-7;
  printf("Result of work in %s: sum = %f\n", __func__,sum);
  return NULL;
}
void* the_thread_funcB(void* arg) {
  long int i;
  double sum;
  printf("%s tarting doing some work.\n", __func__);
  for(i = 0; i < 1000000000; i++)
    sum += 1e-7;
  printf("Result of work in %s: sum = %f\n", __func__,sum);
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t thread;
  pthread_t threadB;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, NULL);
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&threadB, NULL, the_thread_funcB, NULL);
  printf("%s tarting doing some work.\n", __func__);
  long int i;
  double sum;
  for(i = 0; i < 1000000000; i++)
    sum += 1e-7;
  printf("Result of work in %s: sum = %f\n", __func__,sum);

  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);
  pthread_join(threadB, NULL);

  return 0;
}
