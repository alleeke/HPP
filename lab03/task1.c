#include <stdio.h>
#include <stdlib.h>

/* Write a C program that creates a matrix of dimension n×n of the form below and
displays it: 

0 1 1 1 1
−1 0 1 1 1
−1 −1 0 1 1
−1 −1 −1 0 1
−1 −1 −1 −1 0


Note. Use statically allocated two-dimensional arrays. First store the matrix as a
two-dimensional array in memory, and then use the values from the array to print
the matrix. */

void print_array(int* arr, int size);
void fill_matrix(int*** mat,int size); // For dynamically alloacted memory 
//void fill_matrix(int mat[MAX_SIZE][MAX_SIZE],int size); // For statically alloacted memory 

int main (){

    int n; 
    printf("Input the size n of your square matrix n*n: ");
    scanf("%d",&n);

    int myMatrix[n][n]; //statically allocate 

/*
    int** myMatrix = (int**)malloc(n*sizeof(int*)); 
    for (int i = 0; i < n; i++)
    {
        myMatrix[i] = (int*)malloc(n*sizeof(int));
    } 
*/
    
    // fill_matrix(&myMatrix, n); // Since fill_matrix doesn't work well with the statically allocated memeory we can move the code here instead

    for (int i = 0; i < n; i++)
    {   
        // Lower diagonal
        for (int k = 0; k < i; k++)
        {
            myMatrix[i][k] = -1; 
        }

        // Diagonal 
        myMatrix[i][i] = 0; 
        

        // Upper diagonal 
        int j = i +1;
        while(j<n)
        {
            myMatrix[i][j] = 1; 
            j++;
        }
    }


    for (int i = 0; i < n; i++)
    {
        print_array(myMatrix[i],n);
    }

    
    return 0; 
}

void fill_matrix(int*** mat,int n){
    for (int i = 0; i < n; i++)
    {   
        // Lower diagonal
        for (int k = 0; k < i; k++)
        {
            (*mat)[i][k] = -1; 
        }

        // Diagonal 
        (*mat)[i][i] = 0; 
        

        // Upper diagonal 
        int j = i +1;
        while(j<n)
        {
            (*mat)[i][j] = 1; 
            j++;
        }
    }
}

void print_array(int* arr, int size){
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]); 
    }
    printf("\n");
    
}