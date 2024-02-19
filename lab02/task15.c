#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Let product be represented in a code as a structure:
typedef struct product
{
char   name[50];
double price;
} product_t;

Modify your program such that all data read from a file are stored into an array of products:
product_t arr_of_prod[100];
Assume there will be no more that 100 products in a file. When all data are read from the file, output data from the array to the standard output as a table.
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

    product_t products[100]; 

    FILE * stream = fopen(filename,"r"); 
    double price;
    char* name; 
    int reads = 0;
    while(fscanf(stream,"%s %lf",products[reads].name,&products[reads].price)>0)
    {
        reads++; 
    }

    for (size_t i = 0; i < reads; i++)
    {
        printf("%s costs %lf\n", products[i].name, products[i].price);
    }
    


    return 0;
}