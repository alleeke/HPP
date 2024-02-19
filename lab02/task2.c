
#include <stdio.h>
#include <assert.h>
/* 
Task 2: Write a C program which reads two integer numbers a and b from the
standard input using scanf function. Output using printf function and symbols
’.’ and ’*’ the rectangle of size a ×b. Example:
Input: 5 7
Output:
*******
*.....*
*.....*
*.....*
******* */

int main(){
    int a; int b;
    printf("Input 2 numbers\n");
    scanf("%d", &a);
    scanf("%d", &b);

    while(a<0 || b<0){
        printf("At least one of the inputs are negative. requires positive input\n");
        printf("Input 2 new numbers\n");
        scanf("%d", &a);
        scanf("%d", &b);
    }

    assert((a>0 && b>0)&& "Check that input is positive");

    printf("You choose the values (%d,%d)\n",a,b);
    
    for (size_t i = 0; i < a; i++)
    {
        for (size_t j = 0; j < b; j++)
        {
           printf("*");
        }
        printf("\n");
    }
    

    return 0; 
}