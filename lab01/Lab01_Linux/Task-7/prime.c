#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NDEBUG
#include <assert.h>


int is_prime(int n);

int main(){
    
    int n, nprimes;
    int *prime;
    
    printf("Give a number: ");
    scanf("%d", &n);
    assert(n > 0 && "check input postive");
    prime=(int *)malloc(n*sizeof(int));
  
    
    // Compute all primes
    prime[0]=2;
    nprimes=1;
    for (int number=2;number<=n;number+=2){
        if (is_prime(number)){
            prime[nprimes]=number;
            nprimes++;
        }
    }
    
    
    if (nprimes<1000)
        for (int i=0;i<nprimes;i++)
            printf("%d\n",prime[i]);

    printf("Total number of primes: %d\n",nprimes);
    printf("Current line %d", __LINE__);
    return 0;
}

int is_prime(int n){
    for (int i=2;i<=sqrt(n);i++){
        if (n%i==0){
            return 0;
        }
    }
    return 1;
}
