/**********************************************************************
 * This program calculates pi using C
 *
 **********************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

#define NUM_TRHEAD 4 
double sum = 0.0;
const int intervals = 500000000;
const double dx  = 1.0/intervals;
pthread_mutex_t m; 

void *thread_func(void *arg){
  double *inData = (double*)arg;
  int startIndex = (int)inData[0];
  int endIndex = (int)inData[1];
 
  int i; double x;
  for (i = startIndex; i < endIndex; i++) { 
    x = dx*(i - 0.5);
    inData[2] += dx*4.0/(1.0 + x*x);
    //sum += dx*4.0/(1.0 + x*x);
  }
  return NULL;
}

int main(int argc, char *argv[]) {

  double time1 = get_wall_seconds();
  pthread_t threads[NUM_TRHEAD];
  double inData[NUM_TRHEAD][3];
  for (int i = 0; i < NUM_TRHEAD; i++)
  { 
    inData[i][0] = 1+(i)*(intervals/NUM_TRHEAD);
    inData[i][1] = inData[i][0]+(intervals/NUM_TRHEAD);
    inData[i][2] = 0; 

    pthread_create(&threads[i],NULL,thread_func,inData[i]);
  }

  for (int i = 0; i < NUM_TRHEAD; i++)
    pthread_join(threads[i],NULL);
  
  for (size_t i = 0; i < NUM_TRHEAD; i++)
  {
    sum += inData[i][2]; 
  }
  printf("PI (parallel) is approx. %.16f took %7.3f wall seconds.\n", sum,get_wall_seconds()-time1);
 
  
  time1 = get_wall_seconds();
  int i; double x;
  sum = 0.0;
  for (i = 1; i <= intervals; i++) { 
    x = dx*(i - 0.5);
    sum += dx*4.0/(1.0 + x*x);
  } 
  printf("PI (serial)   is approx. %.16f took %7.3f wall seconds.\n", sum,get_wall_seconds()-time1);

  printf("PI is actually \t\t 3.141592653589793\n");
  

  return 0;
}
