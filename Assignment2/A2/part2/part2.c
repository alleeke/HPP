#include <stdio.h>
#include <stdlib.h>

/* 
in the part2 directory that was provided with this assignment there is a small
binary file called little_bin_file. The file size is 17 bytes. You can check the
size using the command “ls -l”.
The file contains the following data, in this order:
•An integer number represented using the datatype int
•A floating-point number represented using the datatype double
•A character represented using the datatype char
•A floating-point number represented using the datatype float
In a C program we can use sizeof to determine the size of each datatype; you can
verify that the total size for the four types above becomes 17 bytes by adding up
the corresponding sizeof results.
Write a C program that opens the file, reads its contents into memory, and prints
out the four pieces of data. Your program should not require any input arguments;
it should assume that the input file is always called little_bin_file. The program
should use the C library functions fopen, fread, and fclose to open the file, read
it, and close the file when you are done with it. Use printf to output the results,
printing each piece of data on a separate line in the same order as above, so that
the program gives precisely 4 lines of output.
The name of the executable should be “readfile”. 
*/

int MAXSIZE = 100; 

int main(){

    /* 
    TODO:
        1. define each type we want to read
        2. read each type with fread
        3. close file    
    */
    int a; 
    double b;
    char c; 
    float d;

    char* filename = "little_bin_file"; 

    FILE * myFile = fopen(filename,"r"); // open file, r- read only option

    fread(&a,sizeof(int),1,myFile);
    fread(&b,sizeof(double),1,myFile);
    fread(&c,sizeof(char),1,myFile);
    fread(&d,sizeof(float),1,myFile);

    fclose(myFile);

    printf("%d\n",a);
    printf("%f\n",b);
    printf("%c\n",c);
    printf("%f\n",d);


    // printf("Size of int + double + char + float = %lu",sizeof(a)+sizeof(b)+sizeof(c)+sizeof(d));

    return 0; 
}