## A Parallel Recursive Quick Sort Algorithm 

\- Final project in High Performance Computing 

\- VT24 Uppsala Universitet

\- Alexander Eketrapp
##

Sorts an array (of type sortType defined in quick_sort.h) using a parallel quick sort algorithm. 

To run the program execute the make command and run as ./quick_sort N nthreads. Where N is the size of the array and nthreads how many threads you want to parallelize with. nthreads must be a power of 2 since this is how the algorithm is implemented (see report for more in depth). If nthreads is set to a number which is not a power of 2 the program runs with the default value of 4 threads. 

If sortType is changed, also change how the random list is generated in the file main.c 