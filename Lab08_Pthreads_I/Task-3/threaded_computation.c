#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

const long int N1 = 400000000;
const long int N2 = 400000000;

void* the_thread_func(void* arg) {
  long int i;
  long int sum = 0;
  double time1 = get_wall_seconds();  
  for(i = 0; i < N2; i++)
    sum += 7;
  /* OK, now we have computed sum. Now copy the result to the location given by arg. */
  printf("%s work took %7.3f wall seconds.\n", __func__, get_wall_seconds()-time1);
  long int * resultPtr;
  resultPtr = (long int *)arg;
  *resultPtr = sum;
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  long int thread_result_value = 0;

  double time0 = get_wall_seconds();  

  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, &thread_result_value);

  printf("This is the main() function after pthread_create()\n");

  long int i;
  long int sum = 0;
  double time1 = get_wall_seconds();  
  for(i = 0; i < N1; i++)
    sum += 7;
  printf("%s work took %7.3f wall seconds.\n", __func__,get_wall_seconds()-time1);
  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);

  printf("Entire %s took %7.3f wall seconds.\n", __func__,get_wall_seconds()-time0);

  printf("sum computed by main() : %ld\n", sum);
  printf("sum computed by thread : %ld\n", thread_result_value);
  long int totalSum = sum + thread_result_value;
  printf("totalSum : %ld\n", totalSum);

  return 0;
}
