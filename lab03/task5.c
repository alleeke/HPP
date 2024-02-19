#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Write a C program which sorts an array of strings in alphabetic order using the
qsort function. You should write a function CmpString which follows the prototype
of compar and compare two elements of the array, such that the following code sorts
elements of the array arrStr in alphabetic order:

char *arrStr[] = {"daa", "cbab", "bbbb", "bababa", "ccccc", "aaaa"};
int arrStrLen = sizeof(arrStr) / sizeof(char *);
qsort(arrStr, arrStrLen, sizeof(char *), CmpString);

Hint. Use the strcmp function for comparison of strings.
Hint: Note that the CmpString function should get pointers to the elements in the
array which should be compared. In our case we get pointers to strings (char**). To
help understanding what is happening, it may again be helpful to add some printf
statements inside your CmpString function, showing which strings are being com-
pared. This is little bit tricky but you can read about it, e.g., at https://www.
benjaminwuethrich.dev/2015-03-07-sorting-strings-in-c-with-qsort.html */


int compare_string(const void * ptr_a, const void* ptr_b){
    char* a = *(char **)ptr_a;
    char* b = *(char **)ptr_b;

    printf("Now comparing (%s,%s)\n", a,b); 

    if(strcmp(a,b)) return 1;
    else if(strcmp(a,b) == 0) return 0; 
    else return -1;
    
}

int main() {

    int (*CmpString)(const void*,const void*);
    CmpString = compare_string; 

    char *arrStr[] = {"daa", "cbab", "bbbb", "bababa", "ccccc", "aaaa"};
    int arrStrLen = sizeof(arrStr) / sizeof(char *);
    qsort(arrStr, arrStrLen, sizeof(char *), CmpString);
    for (int i = 0; i < 6; i++)
    {
        printf("%s,", arrStr[i]);
    }
    

    return 0; 
}