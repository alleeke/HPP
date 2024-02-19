#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Task 16:
Assume that the number of products in a file is not known in advance and can be very big. 
Modify your program such that the array product t *arr of prod is allocated dynamically using malloc
as soon as you know the exact number of products in the file (the first number in the file is the
number of products). 
*/

typedef struct product
{
char name[50];
double price;
} product_t;

int main(int argc, char const *argv[]){

    if(argc != 2){
        printf("Incorrect arguments be called as ./a data.txt");
        return -1;
    }

    char filename[10]; 
    strcpy(filename, argv[1]);

   

    FILE * stream = fopen(filename,"r"); 
    
    int reads = 0, numberOfProducts; 
    fscanf(stream,"%d",&numberOfProducts);
    printf("%s contains %d products\n\n", filename, numberOfProducts);
    product_t products[numberOfProducts]; 

    while(fscanf(stream,"%s %lf",products[reads].name,&products[reads].price)>0)
    {
        reads++; 
    }

    for (int i = 0; i < reads; i++)
    {
        printf("%s costs %lf\n", products[i].name, products[i].price);
    }
    


    return 0;
}