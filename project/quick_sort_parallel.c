#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "quick_sort_parallel.h"
#include "quick_sort.h"

void merge(sortType *returnList, sortType *list1, sortType *list2, int n1, int n2, int n3);

void quick_sort_parallel(sortType* list, int n, int N, int n_el_processors[], int nthreads){
    /*
    This is the recursive part of the entire quick_sort_parallel algortihm and contains the following steps
        3.1 Select Pivot
        3.2 Divide
        3.3 Exchange
        3.4 Merge  (CODE FROM LAB 6 remember to reference)
     */

    // If we only have one thread in here to list will already be sorted since the quick_sort_parallel
    // input list will be sorted locally in each processor.
    if(nthreads == 1) return; 


  /*   printf("Hello from parallel with n = %d, N = %d, nthreads = %d\n",n,N,nthreads);
    printf("list:\t");
    for (int i = n; i < N; i++)
        printf("%d\t",list[i]); 
    printf("\n\n"); */

    

    // Check if list is single element and if true break
    if(N-n == 1) return; // TODO Implement different sorting algo for lists smaller than some number
    //if(N-n <= nthreads) return; // if true -> Already sorted (not really? ))

    // Step 3.1 Select pivot (Median in processor 0 of each processor set)
    // TODO: Investigate the 2 other pivot selection ideas 
    sortType pivot = list[n+n_el_processors[0]/2]; 
    /* printf("pivot = %d\n", pivot);  */

    // Step 3.2, 3.2 Divide and Exchange

    // -------------------- DEFINING VARIABLES NEEDED FOR STEP 3.2 & 3.3 ---------------------------------
    sortType *lowerHigerList; // New list that keeps two lists (lower and higher partition around pivot)
    lowerHigerList = (sortType*)malloc(((int)(N-n))*sizeof(sortType));

    // To keep track how we should merge the lists after dividing and exchanging
    int lowerMergeIndex[nthreads+1]; 
    int higherMergeIndex[nthreads+1]; 

    // To keep track how large lowerList and higherList are
    int lowerInd = 0, higherInd = 0; 

    // To keep track how many low and high elements (below and above or equal pivot) each processor has
    int n_low_elements[nthreads], n_high_elements[nthreads];
    for (int i = 0; i < nthreads; i++)
    {
        n_low_elements[i] = 0;
        n_high_elements[i] = 0;
    }

    int thread_index; // Keep track of which thread/processor the current elements belongs to
    int thread_el_counter;// Keep track of which element in the current thread we are at (reset if we move to new thread)
    // ---------------------------------------------------------------------------------------------------


    // Below we divide the list into lower and higher part. Since we don't know
    // the exact size of the individual lists but only that length(lower + higher) = N-n
    // we malloc one large chunck memory for this. This means we need two separate for-loops
    // to build the lower than the higher. We can build the higher list when we know how large
    // the lower list is. What is also important and done is to keep track of which elements
    // belongs to which processor and where the sorted lists starts (see PDF) to correctly
    // merge so that each processor has a sorted list for the next step. 

    sortType *lowerList = lowerHigerList; 
    thread_index = 0; 
    thread_el_counter = 0;
    lowerMergeIndex[0] = 0;
    for (int i = n; i < N; i++)
    {
        // Check if we need to move to the next thread, while-loop to check if next thread
        // has zero elements 
        while (thread_el_counter == n_el_processors[thread_index]) {
            thread_index++; // Move to the next processor
            thread_el_counter = 0; 
        }

        int current_element = list[i]; // Cache the current element value so we do not look up several times

        if(current_element < pivot){
            lowerList[lowerInd++] = current_element; // Update lowerList then add 1 to lowerInd
            n_low_elements[thread_index]++; // Increment the value in n_low_elements based on the current processor index
        }  
    thread_el_counter++; 
    }

    sortType *higherList = lowerHigerList + lowerInd; // Point to place after number of lower elements
    thread_index = 0; 
    thread_el_counter = 0;
    higherMergeIndex[0] = 0;
    for (int i = n; i < N; i++)
    {

        // While loop in case next thread has zero elements 
        while (thread_el_counter == n_el_processors[thread_index]) {
            thread_index++; // Move to the next processor
            thread_el_counter = 0; // Reset el_counter for new processor
        }

        int current_element = list[i]; // Cache the current element value so we do not look up several times
        
        if(current_element >= pivot){
            higherList[higherInd++] = current_element; 
            n_high_elements[thread_index]++; // Increment the value in n_high_elements based on the current processor index     
        }
    thread_el_counter ++; 
    }

     // Print values
    /* printf("(%d) n_el_threads:    ",tid);
    for (int i = 0; i < nthreads; i++)
        printf("%d\t",n_el_processors[i]); 
    printf("\n");
    printf("(%d) n_low_elements:  ",tid);
    for (int i = 0; i < nthreads; i++)
        printf("%d\t",n_low_elements[i]); 
    printf("\n");
    printf("(%d) n_high_elements: ",tid);
    for (int i = 0; i < nthreads; i++)
        printf("%d\t",n_high_elements[i]); 
    printf("\n\n"); */

    
    // Build the mergeIndex arrays to find out how we should merge. 
    for (int i = 0; i < nthreads; i++)
    {
        lowerMergeIndex[i+1] = lowerMergeIndex[i] + n_el_processors[i] - n_high_elements[i];
        higherMergeIndex[i+1] = higherMergeIndex[i] + n_el_processors[i] - n_low_elements[i];
    }

    // Print values
    /* printf("(%d) MergeIndex:\t",tid);
    for (int i = 0; i < nthreads+1; i++)
        printf("%d\t",lowerMergeIndex[i]); 
    printf("\n");
    printf("(%d) lowerList:\t",tid);
    for (int i = 0; i < lowerInd; i++)
        printf("%d\t",lowerList[i]); 
    printf("\n\n"); */
     

    // Print values
    /* printf("(%d) mergeIndex:\t",tid);
    for (int i = 0; i < nthreads+1; i++)
        printf("%d\t",higherMergeIndex[i]); 
    printf("\n");
    printf("(%d) higherList:\t",tid);
    for (int i = 0; i < higherInd; i++)
        printf("%d\t",higherList[i]); 
    printf("\n\n");
    
*/
  /*   printf(" BeforeMerge:\t");
    for (int i = 0; i < N-n; i++)
        printf("%d\t",lowerHigerList[i]); 
    printf("\n");  */
    

    // Step 3.4 merge
    #pragma omp parallel num_threads(nthreads)
    {
        // i = loop index to get mergeIndex  
        // lowMerge: (thread_id,i) = (0,0), (2,1), (4,2), (6,3) 
        // highMerge (thread_id,i) = (1,0), (3,1), (5,2), (7,3)
        int thread_id = omp_get_thread_num();
        int i = thread_id/2;

        if (thread_id % 2 == 0) {
            // merge lower list
            int k = 2*i; 
            int n1 = lowerMergeIndex[k];
            int n2 = lowerMergeIndex[k+1];
            int n3 = lowerMergeIndex[k+2];
            merge(list, lowerList+n1, lowerList+n2, n1+n, n2+n, n3+n);
    } else {
            // merge higher list
            int k = 2*i; 
            int n1 = higherMergeIndex[k];
            int n2 = higherMergeIndex[k+1];
            int n3 = higherMergeIndex[k+2];
            merge(list, higherList+n1, higherList+n2, n1+n+lowerInd, n2+n+lowerInd, n3+n+lowerInd);
    }
    }

   /*  printf("(%d) AfterMerge:\t",tid);
    for (int i = n; i < N; i++)
        printf("%d\t",list[i]); 
    printf("\n\n");  */

    int n_el_processors_low[nthreads/2];  // To keep track of how many low elements each processor handles for next recursive call
    int n_el_processors_high[nthreads/2];  // To keep track of how many high elements each processor handles for next recursive call

    int k = 0;
    for (int i = 0; i < nthreads; i += 2)
    {
        n_el_processors_low[k] = n_low_elements[i] + n_low_elements[i+1];
        n_el_processors_high[k] = n_high_elements[i] + n_high_elements[i+1];
        k++; 
    }
    

    // We don't have to worry that we are using 2 threads if only ony thread is available since
    // this functions returns automatically if we only use 1 thread (already sorted).
    #pragma omp parallel sections firstprivate(n_el_processors_low,n_el_processors_high) num_threads(2)
    {
        #pragma omp section
        {
            quick_sort_parallel(list, n, n+lowerInd, n_el_processors_low, nthreads/2);
        }
        #pragma omp section
        {
            quick_sort_parallel(list, n+lowerInd, N, n_el_processors_high, nthreads/2);  
        }
    }
     
    /* quick_sort_parallel(list, n, n+lowerInd, n_el_processors_low, nthreads/2);
    quick_sort_parallel(list, n+lowerInd, N, n_el_processors_high, nthreads/2); */  
    

    free(lowerHigerList); 
} 

void merge(sortType *returnList, sortType *list1, sortType *list2, int n1, int n2, int n3){
    /* 
    
    THIS CODE IS COPIED FROM LAB06_MemUsage Task-2 in the file sort_func.c AND THEN MODIFIED
    

    INPUT:
        returnList: where to store the merged list
        list1 & list2: lists you want to merge
        int n1, int n2, int n3: to know which part to merge

        actually list1 & list2 are the same memory chunks but points to different places. This is done
        to no (malloc) for another array. n1 n2 n3 tells us which parts of the array we should merge.
        we are merging the two sublists [n1,n2) <-> [n2,n3). 

        list1 points to element at place n1
        list2 points to element at place n2

        since the lists we are merging are next to eachother 
        n2-n1 gives the length of list1
        n3-n2 gives the length of list2 
        
     */

    int i1 = 0;
    int i2 = 0;

    int i = n1;
    int len1 = n2-n1;
    int len2 = n3-n2;

    i = n1; 
    while(i1 < len1 && i2 < len2) {
        if(list1[i1] < list2[i2]) {
            returnList[i] = list1[i1];
            i1++;
        }
        else {
            returnList[i] = list2[i2];
            i2++;
        }
    i++;
  }
  while(i1 < len1)
    returnList[i++] = list1[i1++];
  while(i2 < len2)
    returnList[i++] = list2[i2++];
}