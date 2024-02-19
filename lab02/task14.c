#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
Modify your program such that is accepts one argument passed from the command line. This parameter will be 
a file name with a list of products. Make sure your program can be run like this: ./a.out data.txt
Hint. The lines int main(int argc, char const *argv[]) and strcpy(filename,
argv[1]) can be used.
*/

int main(int argc, char const *argv[]){

    if(argc != 2){
        printf("Incorrect arguments be called as ./a data.txt");
        return -1;
    }

    int n;
    double price;
    char product[10];
    char filename[10]; 
    strcpy(filename, argv[1]);
    FILE* stream = fopen(filename,"r"); // Read values from file  
    fscanf(stream,"%d", &n); 
    while(fscanf(stream,"%s %lf", product, &price)>0)
    {
        printf("%s costs %f kr\n", product, price);
    }

}   