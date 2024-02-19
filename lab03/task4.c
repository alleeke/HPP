#include <stdio.h>
#include <stdlib.h>

/* Write a C program which sorts an array of real numbers in descending order using
the qsort function. You should write a function CmpDouble which follows the
prototype of compar and compares two elements of the array, such that the following
code sorts elements of the array arrDouble in descending order
double arrDouble[] = {9.3, -2.3, 1.2, -0.4, 2, 9.2, 1, 2.1, 0, -9.2};
int arrlen=10;
qsort (arrDouble, arrlen, sizeof(double), CmpDouble); */

// void qsort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));

int compare_doubles(const void*, const void*); 
void print_array(double* arr, int size);

int main(){

    int (*CmpDouble)(const void*, const void*);
    CmpDouble = compare_doubles;  

    double arrDouble[] = {9.3, -2.3, 1.2, -0.4, 2, 9.2, 1, 2.1, 0, -9.2};
    print_array(arrDouble,10);
    int arrlen=10;
    qsort (arrDouble, arrlen, sizeof(double), CmpDouble);
    print_array(arrDouble,10);

    return 0;
}

int compare_doubles(const void*  ptr_a, const void* ptr_b){
    // Cast the generic pointers to a double pointer then dereference it obtain the double value pointed to by ptr_a, ptr_b. 
    double a = *(double*)ptr_a;
    double b = *(double*)ptr_b; 

    // printf("Comparing %lf,%lf\n", a,b);
    if(a < b)return -1;
    else if (a > b) return 1; 
    else return 0; 
    
}

void print_array(double* arr, int size){
    for (int i = 0; i < size; i++)
    {
        printf("%lf ", arr[i]); 
    }
    printf("\n");
    
}