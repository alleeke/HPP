
/* Write a C program which prints numbers 100, 96, 92, ..., 0 using
•for loop
•while loop
•do...while loop */
#include <stdio.h>


int main() {
    printf("Using for loop");
    for (int i = 0; i < 100/4+1; i++)
    {
        printf("%d\n",100-4*i);
    }

    int output = 100;
    printf("Using while loop");
    while (output >= 0)
    {
        printf("%d",output);
        output = output-4;
    }

    int output2 = 100;
    printf("Using do-while loop");
     do{
        printf("%d",output);
        output = output-4;
     }
     while (output2 < 0);
     
    return 0; 
}