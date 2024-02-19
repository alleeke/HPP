#include <stdio.h>
#include <stdlib.h>

/* Write a C program which reads data from a file ”data.txt” line by line using fscanf(file, "%s %lf", product, &price) and directly outputs it to the stan- dard output as a table:
Milk 10.3
Water 5.2
Potatoes 3.1
Carrots 4.8
Meat 20.0 */

int main(){
    int n;
    double price;
    char product[10]; 
    FILE* stream = fopen("data.txt","r"); // Read values from file  
    fscanf(stream,"%d", &n); 
    while(fscanf(stream,"%s %lf", product, &price)>0)
    {
        printf("%s costs %f kr\n", product, price);
    }

}