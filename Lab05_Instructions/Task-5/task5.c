#include <stdio.h>

void myFunctionThatDoesAFewThings(){
    int a = 1; 
    int b = 2; 
    for (int i = 0; i < b << 10; i++)
    {
       a = b << 2;
       b = b << 2; 
       int d = 1/10;
       int k = 100*d;
    }
}

inline void myInlineFunctionThatDoesAFewThings(){
    int a = 1; 
    int b = 2; 
    for (int i = 0; i < b << 10; i++)
    {
       a = b << 2;
       b = b << 2; 
       int d = 1/10;
       int k = 100*d;
    }
}

#define FAST 0

int main(){

    int N = 100000; 
    for (int i = 0; i < N; i++)
    {
        #if FAST 
        myInlineFunctionThatDoesAFewThings(); 
        #else
        myFunctionThatDoesAFewThings();
        #endif 
    }
    return 0; 
}