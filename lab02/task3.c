#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Task 3:
•Write a C program which reads two integers from the standard input. If
both numbers are even, write their sum, otherwise, output their product.
•Write a C program which reads three real numbers from the standard input.
Find which of these numbers is the largest by absolute value and print the
result.
Date: November 26, 2021.
1
2 LAB 2
•Write a C program which reads three real numbers from the standard input.
Find which of these numbers is the second largest by absolute value and
print the result */

int main(){
    int a; int b;

    printf("Input two integers\n");
    scanf("%d%d", &a,&b);


    if(a%2 == 0 && b%2 == 0){
        printf("%d", a+b);
    }
    else {
        printf("%d", a*b);
    }


    float c,d,e; 
    

    printf("Input three numbers\n");
    scanf("%f%f%f", &c,&d,&e);
  
    float max = c;
    if (fabsf(max) < fabsf(d)){
        max = d;
    }
    if(fabsf(max) < fabsf(e)){
        max = e; 
    }


    printf("Largest number in absolute value is %f", max);


    return 0;
}