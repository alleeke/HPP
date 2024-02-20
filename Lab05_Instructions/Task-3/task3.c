#include <stdio.h>
#include <math.h>


int main (){

   
    double SPR_tenBase1 = -126*log10(2);
    double SPR_tenBase2 = 127*log10(2);

    double DPR_tenBase1 = -1022*log10(2);
    double DPR_tenBase2 = 1023*log10(2);

    printf("Single precision range = [1e%f,1e%f]\n",SPR_tenBase1,SPR_tenBase2);
    printf("Double precision range = [1e%f,1e%f]\n",DPR_tenBase1,DPR_tenBase2);




    float f = 1, f_prior;
    double d = 1, d_prior;

    for (int i = 0; i < 20; i++)
    {   
        f_prior = f; 
        f*=100; 
        if(isinf(f)) {
            printf("i = %d, Expected f = 1e%d The float number = 1e%f\n" ,i,(i)*2,log10(f_prior)); 
            printf("i = %d, Expected f = 1e%d The float number = %f\n" ,i,(i+1)*2,f); 
        }
    }

    for (int i = 0; i < 155; i++)
    {
        d_prior = d; 
        d*=100; 
        if(isinf(d)){
            printf("i = %d, Expected d = 1e%d The float number = 1e%f\n" ,i,(i)*2,log10(d_prior)); 
            printf("i = %d, Expected d = 1e%d The float number = %f\n" ,i,(i+1)*2,d); 
        } 
    }

    double epsilon = 1;
    for (int i = 0; i < 500; i++)
    {
       epsilon*=0.5; 
       if(1+epsilon == 1) {
            printf("1 + 1e%f = 1",log10(epsilon));
            i = 500; 
       }
    }
    

    return 0; 
}