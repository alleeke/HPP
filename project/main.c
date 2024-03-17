#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include "quick_sort.h"
#include "quick_sort_parallel.h"

int DEFAULT_NTHREADS = 4;

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

// Comparison function for qsort implemented by https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
// Used as reference result to compare with the implemented version here
int compare(const void *a, const void *b) {
    return (*(sortType *)a - *(sortType *)b);
}

int is_power_of_2(int number){
    int r = 1;
    while (number > 1)
    {
        if(number%2 != 0){
            r = 0;
            return r; 
        }
        number = number/2; 
    }
    return r; 
}

int main(int argc, char const *argv[]) {


    if (argc != 3)
    {
        printf("ERROR: Run as %s N nthreads\n", argv[0]);
        return -1; 
    }

    int N = atoi(argv[1]); 
    int nthreads = atoi(argv[2]);

    if(2*nthreads > N)
    {
        printf("ERROR: N >= 2*nthreads not fulfilled\n");
        printf("ERROR: Algorithm has not implemented a complete merge algorithm for this case you provided\n");
        printf("ERROR: Please rerun with N >= 2* nthreads\n\n");
        return -1;
    }

    // if nthreads is not a factor of 2 we will have suboptimal load balance (assuming small and large datas are equally random)
    if(!is_power_of_2(nthreads)) {
        printf("WARNING: nthreads is not a power of 2. Algorithm not optimal for other number of cores\n");
        printf("WARNING: Running with %d threads instead\n\n", DEFAULT_NTHREADS); 
        nthreads = DEFAULT_NTHREADS; 
        }

    // Nested parallelism is required for the recursive call of the quick_sort_parallel function 
    if(!omp_get_nested()) 
    {
        printf("Nested parallelism disabled, enabling...\n");
        omp_set_nested(1);
    }
    
    sortType *myList, *myRefList;  // myRefList is used to check result (stdlib qsort is implemented for this)
    myList = (sortType*)malloc(N*sizeof(sortType)); 
    myRefList = (sortType*)malloc(N*sizeof(sortType)); 

    // Generate random list 
    for (int i = 0; i < N; i++)
        myList[i] = rand()%100; // Generates integers between 0 and 100
        //myList[i] = (double)rand() / RAND_MAX; // Generates doubles between 0 and 1
    
    // Print values
  /*   for (int i = 0; i < N; i++){
        if(i%(N/nthreads) == 0 && i != 0)
            printf("--|--\t");
        printf("%d\t",myList[i]); }
    printf("\n"); */

    // Deep copy
    for (int i = 0; i < N; i++) 
        myRefList[i] = myList[i];
    

    // --- Quick Sort Parallel ---

    // Step 1. Divide data into p equal parts and sort locally 
    double t1 = get_wall_seconds();
    int n_el_thread[nthreads];  // To keep track of how many elements each thread handles (takes in account, the rest)
    int elements_per_thread = N/nthreads; 
    int rest = N%nthreads; 
    int start_index = 0;
    int end_index;

    // find start and end index to put in array to make iterations independent for step 2 
    int start_index_list[nthreads];
    int end_index_list[nthreads];

    for (int i = 0; i < nthreads; i++)
    {
        end_index = start_index + elements_per_thread;
        if (rest > 0) {
            end_index++;
            rest--;
        }
        start_index_list[i] = start_index; 
        end_index_list[i] = end_index;
        start_index = end_index; 
    }

    // Step 2 (Locally sort in each processor)
    #pragma omp parallel for num_threads(nthreads)
    for (int i = 0; i < nthreads; i++){
        quick_sort(myList, start_index_list[i],end_index_list[i]);
        n_el_thread[i] = end_index_list[i]-start_index_list[i]; 
    }

    // Step 3 (recursively)
    quick_sort_parallel(myList,0,N,n_el_thread,nthreads);
    printf("quick_sort() took %fs\n", get_wall_seconds()-t1); 

    t1 = get_wall_seconds();
    qsort(myRefList, N, sizeof(sortType), compare); 
    printf("ref_qsort() took %fs\n", get_wall_seconds()-t1);

      // Print values
   /*  printf("quick_sort(): \t");
    for (int i = 0; i < N; i++)
        printf("%f\t",myList[i]); 
    printf("\n");     

    // Print values
    printf("ref_qsort(): \t");
    for (int i = 0; i < N; i++)
        printf("%f\t",myRefList[i]); 
    printf("\n");  */

    double difference = 0;
    for (int i = 0; i < N; i++)
        difference += abs(myList[i] - myRefList[i]); 
    
    
    if(difference < 1e-10)
        printf("quick_sort implemented correct\n"); 
    else 
        printf("ERROR: qsort[i]-ref_qsort[i] = %f\n", difference); 


    free(myList);
    free(myRefList); 
    
    return 0; 
}