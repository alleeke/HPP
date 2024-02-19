/* Write a C program which reads numbers from the standard input into an array
until something which is not an integer number appears (the return value of scanf
is 0 if it fails to read data of the specified type). Then print all entered numbers
and compute their sum. Note, the amount of numbers is not known, i.e. the length
of the array is not known beforehand. The program should work for any number
of input parameters, no maximum array size should be assumed.
Example:
Input: 4 5 6 7 34 5 y 3 4 3 6
Output:
4 5 6 7 34 5
Sum: 61
Hint. Use malloc and realloc from the header <stdlib.h>. Don’t reallocate the
array for each new number but rather for a chunk of 10 numbers at a time. */

#include <stdlib.h>
#include <stdio.h>

void print_array(int*, int);
int sum(int*, int);

int main (){

    int a;
    int *arr; 

    int arrLength = 10;
    arr = (int *)malloc(arrLength*sizeof(int));

    int count = 0;
    while(scanf("%d",&a) != 0){
        arr[count] = a; 
        count++; 
        if (count%10 ==0){
            arrLength +=10; 
            arr = (int *)realloc(arr, arrLength * sizeof(int));
            printf("Allocated more memory for the array\n");

             if (arr == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(arr);  // Free the original memory
                return 1;      // Return an error code
             }      
        }
    }
   
    print_array(arr,count);   
    printf("Sum of your array = %d\n",sum(arr, count));

    return 0; 
}


int sum(int* arr, int n){
    int sum = 0; 
    for (size_t i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum; 
}

void print_array(int* arr, int n){
    for (int i = 0; i<n; i++){
        printf("%d,",arr[i]);
    }
    printf("\n");  
}