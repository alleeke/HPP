/* C program for Merge Sort
from http://quiz.geeksforgeeks.org/merge-sort/
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
// void merge(int arr[], int l, int m, int r) // Inital (old)
void merge(int* arr, int l, int m, int r) // fixed
{
   int i, j, k;
   int n1 = m - l + 1;
   int n2 = r - m;

   /* create temp arrays */
   int L[n1], R[n2];

   /* Copy data to temp arrays L[] and R[] */
   for (i = 0; i < n1; i++)
   {
      L[i] = arr[l + i];
   }
   for (j = 0; j < n2; j++)
   {
      R[j] = arr[m + 1 + j];
   }

   /* Merge the temp arrays back into arr[l..r]*/
   i = 0;  // Initial index of first subarray
   j = 0;  // Initial index of second subarray
   k = l;  // Initial index of merged subarray
   while (i < n1 && j < n2)
   {
      if (L[i] <= R[j])
      {
         arr[k] = L[i];
         i++;
      }
      else
      {
         arr[k] = R[j];
         j++;
      }
      k++;
   }

   /* Copy the remaining elements of L[], if there
    * are any */
   while (i < n1)
   {
      arr[k] = L[i];
      i++;
      k++;
   }

   /* Copy the remaining elements of R[], if there
    * are any */
   while (j < n2)
   {
      arr[k] = R[j];
      j++;
      k++;
   }
}


/* l is for left index and r is right index of the
 * sub-array of arr to be sorted */
// void mergeSort(int arr[], int l, int r) // Old code
void mergeSort(int* arr, int l, int r) // fixed code
{
   if (l < r)
   {
      // Same as (l+r)/2, but avoids overflow for
      // large l and h
      int m = l + (r - l) / 2;

      // Sort first and second halves
      mergeSort(arr, l, m);
      mergeSort(arr, m + 1, r);

      merge(arr, l, m, r);
   }
}


void fill_in_array(int *a, int n)
{
   srand(time(NULL));
   for (int i = 0; i < n; ++i)
   {
      a[i] = rand() % n;
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
n = 100 0.000019 s
n = 1000 0.000137 s 
n = 10000 0.002568
n = 100000 0.020890
 */

int main(int argc, char const *argv[])
{
   int n;
   // Since we have a recursive merge sort it is easy to get stack over flow! 

   if (argc != 2)
   {
      printf("Usage: %s n\n", argv[0]);
      return -1;
   }
   n = atoi(argv[1]);
   int *a = malloc(n * sizeof(int));
   fill_in_array(a, n);

   printf("Array is created.\n");

   double t1 = get_wall_seconds();
   mergeSort(a, 0, n - 1);
   double t2 = get_wall_seconds();
   printf("merge_sort: %f\n", t2-t1);

   printf("Array is sorted!\n");

   return 0;
}
