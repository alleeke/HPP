#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "quick_sort.h"


static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

// Comparison function for qsort implemented by https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
// Used as reference result to compare with the implemented version here
sortType compare(const void *a, const void *b) {
    return (*(sortType *)a - *(sortType *)b);
}

int main(int argc, char const *argv[]) {


    if (argc != 2)
    {
        printf("ERROR: Run as %s N\n", argv[0]);
        return -1; 
    }

    int N = atoi(argv[1]); 

    sortType *myList, *myRefList;  // myRefList is used to check result (stdlib qsort is implemented for this)
    myList = (sortType*)malloc(N*sizeof(sortType)); 
    myRefList = (sortType*)malloc(N*sizeof(sortType)); 

    // Generate random list 
    for (int i = 0; i < N; i++)
        myList[i] = rand()%100;/* code */
    
    /*  // Print values
    for (int i = 0; i < N; i++)
        printf("%d\t",myList[i]); 
    */

    // Deep copy
    for (int i = 0; i < N; i++) 
        myRefList[i] = myList[i];
    
    
    double t1 = get_wall_seconds();
    quick_sort(myList,0,N);
    printf("quick_sort() took %fs\n", get_wall_seconds()-t1);

    t1 = get_wall_seconds();
    qsort(myRefList, N, sizeof(sortType), compare); 
    printf("ref_qsort() took %fs\n", get_wall_seconds()-t1);

    double difference = 0;
    for (int i = 0; i < N; i++)
        difference += abs(myList[i] - myRefList[i]); 
    
    
    printf("qsort[i]-ref_qsort[i] = %f\n", difference); 

    free(myList);
    free(myRefList); 
    
    return 0; 
}