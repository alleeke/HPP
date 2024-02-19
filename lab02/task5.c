#include <stdio.h>
#include <math.h>

/* A perfect square is an integer that is the square of an integer, for example the
numbers 4 and 25 are perfect squares since 4 = 2^2 and 25 = 5^2. Write a C program
which is checking if the number entered by the user is a perfect square. You can
use the sqrt function from header <math.h>.
Note. The math functions in <math.h> have implementations in the library libm.so.
If your program includes <math.h>, then for some compilers you might need to ex-
plicitly link to the math library:
gcc -o prog prog.c -lm
where prog.c is a name of your source file */

int main(){
   

    int a;
    printf("Input an integer: ");
    scanf("%d", &a);

    double b = sqrt(a); 
    int b_int = b;

    if(b == b_int){
        printf("The inputed number %d is a perfect square\n",a);
    }

     return 0; 

}