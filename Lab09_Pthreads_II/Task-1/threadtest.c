#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  double *p;
  p = (double*)malloc(5*sizeof(double));
  p[0] = 0;
  p[1] = 1.1;
  p[2] = 2.2;
  pthread_exit(p);
  //return p;
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");
  if(pthread_create(&thread, NULL, the_thread_func, NULL) != 0) {
    printf("ERROR: pthread_create failed.\n");
    return -1;
  }

  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  double *resultPtr; 
  if(pthread_join(thread, (void*)&resultPtr) != 0) {
    printf("ERROR: pthread_join failed.\n");
    return -1;
  } 
  
  printf("%f %f %f", resultPtr[0],resultPtr[1],resultPtr[2]);
  free(resultPtr); 

  return 0;
}
