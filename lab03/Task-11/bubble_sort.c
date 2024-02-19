#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/*
 * Sort an array using bubble sort algorithm.
 */

/* Swap values pointed by x and y */
void swap(int *x, int *y)
{
   int tmp;

   tmp = *x;
   *x  = *y;
   *y  = tmp;
}


void print_array(int *a, int n)
{
   for (int i = 0; i < n; i++)
   {
      printf("%d ", a[i]);
   }
   printf("\n");
}


void fill_in_array(int *a, int n)
{
   srand(time(NULL));
   for (int i = 0; i < n; ++i)
   {
      a[i] = rand() % n;
   }
}


void bubble_sort(int *a, int n)
{
   // Complexity if we do second for loop until n aswell then we get O(n^2) (worst case scenario)
   int swapped = 0;

   for (int i = 0; i < n; ++i)
   {
      swapped = 0;
      // avoid looking at the last n-1 items when running for the n-th time
      for (int k = 1; k < n-i; ++k)
      {
         if (a[k] < a[k - 1])
         {
            swap(&a[k], &a[k - 1]);
            swapped = 1;
         }
      }
      if (swapped == 0)
          break;
   }
}

double get_wall_seconds()
{
struct timeval tv;
gettimeofday(&tv, NULL);
double seconds = tv.tv_sec + (double)tv.tv_usec/1000000;
return seconds;
}
/* 
n = 100 -> 0.000029 s (10^2^2 = 10^4)
n = 1000 -> 0.003476 s (10^3^2 = 10^6)
n = 10000 -> 0.304250 s (10^4^2 = 10^8)
n = 100000 -> 37.639549 s (10^5^2 = 10^10)

We see that each case (n increases with a factor 10) takes about
100x longer than the previous one. 

 */

int main(int argc, char const *argv[])
{
   int n;

   if (argc != 2)
   {
      printf("Usage: %s n\n", argv[0]);
      return -1;
   }
   n = atoi(argv[1]);
   int *a = malloc(n * sizeof(int));
   fill_in_array(a, n);

   printf("Array is created.\n");

   // printf("Original array: \n");
   // print_array(a, n);

   double t1 = get_wall_seconds();
   bubble_sort(a, n);
   double t2 = get_wall_seconds();
   printf("bubble_sort: %f\n", t2-t1);
   // printf("Sorted array: \n");
    // print_array(a, n);

   printf("Array is sorted!\n");

   return 0;
}
