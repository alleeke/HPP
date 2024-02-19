#include <stdio.h>
#include <stdlib.h>
/*
Write a C program which reads a number n from the standard input and then reads n integer 
numbers into an array. Remove all prime numbers from the array putting the results in a
new array. Output the elements of the new array and its size. The program should work for any number 
n, no maximum array size should be assumed. Hint. Use malloc and realloc from the header <stdlib.h>. 
 */

int* removePrimes(int*,int,int*);
void print_array(int*, int);

int main (){

    printf("Input # elements for you array: ");
    int n; int a; 
    int* arr; 

    // Read n (size of array)
    scanf("%d", &n); 

    // Allocate space for array
    arr = (int *)malloc(n*sizeof(int));

    // Better to do this? Even though we need to dynamically update it later? 
    // int arr[10];

    // In loop, read each number that should be inputed in the array
    printf("Input the elements of your array: ");
    for (size_t i = 0; i < n; i++)
    { 
        scanf("%d", &a);
        arr[i] = a; 
    }
    
    print_array(arr,n);

    int newSize = 0; 
    int* arrWithoutPrimes = removePrimes(arr,n,&newSize); 
    print_array(arrWithoutPrimes, newSize);

    return 0; 
}

int* removePrimes(int* arr, int n, int *newSize){
    // Naive implementation (check if divisible with numbers)
    int* arrWithoutPrimes; 
    arrWithoutPrimes = (int *)malloc(10*sizeof(int)); 
    for (size_t i = 0; i < n; i++)
    // Loop through each number
    {
        int isPrime = 1;
        int j = 2; 
        while(isPrime == 1 && j < arr[i]) // Check if number is prime, stop if we already know it is not a prime 
        { 
            if(arr[i] % j == 0) 
            {
                isPrime = 0;
                printf("%d is not a prime and will be added to the new vector\n",arr[i]);
                arrWithoutPrimes[*newSize] = arr[i];
                (*newSize)++;
                

                // Check if we need to reallocate more memory
                if(*newSize % 10 == 0) 
                {
                    arrWithoutPrimes = (int *)realloc(arrWithoutPrimes, (*newSize+10) * sizeof(int));
                    printf("Allocated more memory\n");

                    if (arrWithoutPrimes == NULL) {
                        printf("Memory reallocation failed\n");
                        exit(1);
                    }
                }
            
            } 
            j++; 
        }
    }

    arrWithoutPrimes = (int *)realloc(arrWithoutPrimes, (*newSize) * sizeof(int));
    printf("Removed extra memory not used\n");

     if (arrWithoutPrimes == NULL) {
        printf("Memory reallocation failed\n");
         exit(1);
    }

    return arrWithoutPrimes; 
}

void print_array(int* arr, int n){
    for (int i = 0; i<n; i++){
        printf("%d, ",arr[i]);
    }
    printf("\n");  
}