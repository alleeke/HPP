#include <stdio.h>

/* 
Write a C program which creates a function pointer to that kind of functions and
calls print_int_1 using this function pointer, then set the pointer to point to
print_int_2 instead, and use the function pointer to call that function. Does
it work? Note that the same function pointer can be used to refer to different
functions, as long as the return type and argument types are the same. 
*/

void print_int_1(int x) {
printf("Here is the number: %d\n", x);
}
void print_int_2(int x) {
printf("Wow, %d is really an impressive number!\n", x);
}

int main(){

    void (*foo)(int x); // Functioner pointer to a function returning void with argument int

    foo = print_int_1; 

    foo(5);

    foo = print_int_2;

    foo(6);

    return 0; 
}