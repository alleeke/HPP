#include <stdio.h>
#include "quick_sort.h"

void swap(sortType *a, sortType*b){
    sortType temp = *a; 
    *a = *b; // updates the value at the adress of a to value of b
    *b = temp; // updates the value at the adress of b to the value at a (temp) 
}

int partition(sortType* list, int n, int N){
    /*  
    Partitions the list between n1 and n2 into two sub arrays
    based on the pivot element. The pivot element can be chosen
    in different ways. Here we chose the last element as pivot. 

    The code is from https://www.geeksforgeeks.org/quick-sort/

    Output: 
        returns index of the pivot element after the partioning is
        completed

    Input:
        list to partition
        size of list
    */ 

    int pivot = list[N-1]; 

    int i = n-1;
    for (int j = n; j < N; j++)
    {
    if(list[j] < pivot){
        i++; 
        swap(&list[i],&list[j]); 
    }
    }
    swap(&list[i+1],&list[N-1]); 
    
    return i+1; 
}

void quick_sort(sortType* list, int n, int N){
    if(n < N){
        int k  = partition(list,n,N);
        quick_sort(list,n,k); // Sort lower partition
        quick_sort(list,k+1,N); // Sort higher partition    
    } 
   
}