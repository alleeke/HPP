#include <stdio.h>

int main(){

    char myChar = 'h'; 
    int myInt = 5000000;
    double myDouble = 5.0;
    float myFloat = 5.0;

    size_t sizeOfMyChar = sizeof(myChar);
    size_t sizeOfMyInt = sizeof(myInt);
    size_t sizeOfMyDouble = sizeof(myDouble);
    size_t sizeOfMyFloat = sizeof(myFloat);
    
    printf("Address of myChar: %p\t with size: %zu\n", (void*)&myChar, sizeOfMyChar);
    printf("Address of myInt: %p\t with size: %zu\n", (void*)&myInt, sizeOfMyInt);
    printf("Address of myDouble: %p\t with size: %zu\n", (void*)&myDouble, sizeOfMyDouble);
    printf("Address of myFloat: %p\t with size: %zu\n", (void*)&myFloat, sizeOfMyFloat);


    return 0;
}