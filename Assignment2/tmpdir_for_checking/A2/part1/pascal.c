#include <stdio.h>
#include <stdlib.h>

void print_triangle(int);

int main(int argc, char const *argv[])
{

   // Check so the program is called with the right arguments 
   if (argc != 2)
   {
      printf("Usage: %s n (size of triangle)\n", argv[0]);
      return -1;
   }
   
   int n; 
   n = atoi(argv[1]);

   if(n < 0) {
     printf("input argument has to be positive");
    return -1; 
   }

   print_triangle(n); 



    return 0; 
}

void print_triangle(int n){
    /* 
    TODO:
        0. hard print first row 
        1. Outer loop (rows) of size n-1
        2. "hard" print 1 (beginning of each row)
        3. Inner Loop (cols) from (1-> i-1) and compute the value with mult_sum (n+1-i)/i sum from 1 to k
        4. "hard" print 1 (end of each row)

    Improvement: 
        Don't use formula with mult_sum (alot of operations for large values of n)
        Better to use previous values to build the current through the formula 
            (n,k) = (n-1,k-1) + (n-1,k)
        However in this case we have to allocate memory to store the previous values. 
        This should not be a problem. We only need to store the prev row. Deallocate
        rows not used/ + allocate more + update the pointer with the next row

    WANT: (start from index 0,0)
        1 
        1 1
        1 2 1
        1 3 3 1
        1 4 6 4 1
    */


    printf("%d\n",1); // first row

    double val = 1;  
    for (int i = 1; i < n; i++) // i - row index (starting from 2nd row)
    { 
        printf("%d ",1);
        for (int j = 1; j < i; j++) // j - col index (start from 2nd column)
        { 
            for (int k = 1; k <= j; k++)
            {   
                val *= (double)(i+1-k)/(double)k; 
            }
            printf("%g ", val); // Interesting note, printing this with (int)val gives wrong errors at line 12. 461 instead of 462.
            val = 1; // Reset for next iteration
        }
        
        printf("%d\n",1); 
    }
    

}