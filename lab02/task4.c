#include <stdio.h>

/* Task 4:
Write a simple calculator. The program can read from the standard input the
following command: number OP number, where number is a double and OP is a
char ’+’, ’-’, ’*’ or ’/’. Your program must interpret the input and write the
corresponding output of the operation.
Example:
Input: 3+5
Output: 8
Note. You can use if-else statements but the switch statement is better in this
case for choosing the operation. Write also an error message if the value of OP is
not valid. */

int main(){
    double a; double b; 

    char operation; 

    printf("input 2 numbers and a arithmetic operation (+,-,*,/)\n");
    scanf("%lf%lf",&a,&b);
    scanf("%c",&operation);

    switch (operation)
    {
    case '+':
        printf("Output: %lf",a+b);
        break;
    case '-':
        printf("Output: %lf",a-b);
        break;
    case '*':
        printf("Output: %lf",a*b);
        break;    
    case '/':
        printf("Output: %lf",a/b);
        break;      
    default:
        break;
    }

   

    return 0; 
}

