#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h> 

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}
int nprimes(int m, int M){
    // Computer number of primes in [m,M] (m has to be >=2)
    if(m < 3) m = 3; 
    int np = 1; // 2 is a prime (1 doesnt count)
    for (int i = m; i <= M; i+=2)
    {   
        int add = 1; 
        for (int j = 2; j < i; j++)
        {
            
            if (i % j == 0)
            {
                add = 0; 
                j = i; // Break loop
            }
            
        }
        np += add; 
        
    }
    return np;
}


int nprimes2(int m, int M,int N){
    // Computer number of primes in [m,M] (m has to be >=2)

    int np = 0; 
    for (int i = m; i <= M; i+=2*N)
    {   
        int add = 1; 
        for (int j = 2; j < i; j++)
        {
            
            if (i % j == 0)
            {
                add = 0; 
                j = i; // Break loop
            }
            
        }
        np += add; 
        
    }
    return np;
}

void *threaded_nprimes(void *arg){
     // Computer number of primes in [m,M] (m has to be >=2)
    double time1 = get_wall_seconds();
    int * data = (int*)arg; 
    int m = data[0];
    int M = data[1];
    int N = data[2]; //nthreads

    printf("m = %d", m);
    
    int np = 0; 
    for (int i = m; i <= M; i+=2*N)
    {   
        int add = 1; 
        for (int j = 2; j < i; j++)
        {
            
            if (i % j == 0)
            {
                add = 0; 
                j = i; // Break loop
            }
            
        }
        np += add; 
        
    }
    printf("thread (%d) found %d primes\t", N,np);
    data[3] += np;
    printf("%s took %7.3f wall seconds.\n", __func__, get_wall_seconds()-time1);
    return NULL; 
}


int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Call as %s M N where M and N are integers", argv[0]); 
        return -1;
    }

    int M = atoi(argv[1]);
    int N = atoi(argv[2]); // Number of threads 

    // Serial implementation
    printf("\n\nSerial implementation\n");
    double time1 = get_wall_seconds();
    int np = nprimes(1,M);
    printf("There are %d primes between 1 and %d\n",np,M); 
    printf("nprimes in serial took %7.3f wall seconds.\n", get_wall_seconds()-time1);

    //Threaded implementation (between main and one other thread)
    printf("\n\nThreaded implementation \n");
    time1 = get_wall_seconds();
    int data[N][4]; 


    pthread_t threads[N-1]; // N-1 so we let main work as well 

    for (int i = 1; i < N; i++)
    {
        data[i][0] = 3+2*i;  // starting index (5,7,9) then we step with 2*4 --> (13,15,17) after 1 iteration
        data[i][1] = M;  
        data[i][2] = N; 
        data[i][3] = 0; 
        pthread_create(&threads[i],NULL,threaded_nprimes,&(data[i])); 
    }
    
    np = nprimes2(3,M,N);
    
    
    for (int i = 0; i < N; i++)
        pthread_join(threads[i],NULL);


    int total_primes = np+1; 
    for (int i = 1; i < N; i++)
    {
         total_primes += data[i][3];
    }
       

    printf("main found %d primes\n",np);

    
    printf("There are %d primes between 1 and %d\n",total_primes,M); 
    printf("nprimes with %d threads took %7.3f wall seconds.\n",N, get_wall_seconds()-time1);

}