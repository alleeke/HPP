#include <stdio.h>

/* The function swap nums swaps values of two integers, and the function swap pointers
swaps values of two pointers. Write functions swap nums and swap pointers such
that the program works and gives the following output:
a=4, b=3
s1=first, s2=second */

void swap_nums(int*, int*);
void swap_pointers(char**, char**);


int main(){
    int a,b;
    char *s1,*s2;

    a = 3;
    b = 4;
    
    swap_nums(&a,&b);
    printf("a=%d, b=%d\n", a, b);

    s1 = "second";
    s2 = "first";
    swap_pointers(&s1,&s2);
    printf("s1=%s, s2=%s\n", s1, s2);

    return 0;
}

void swap_nums(int* a, int*b){
    int temporary = *a;
    *a = *b;
    *b = temporary; 
}

void swap_pointers(char** a, char** b){
    char* temporary = *a; 
    *a = *b;
    *b = temporary;
}