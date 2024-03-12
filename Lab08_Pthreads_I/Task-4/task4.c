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

void *threaded_nprimes(void *arg){
     // Computer number of primes in [m,M] (m has to be >=2)
    double time1 = get_wall_seconds();
    int * data = (int*)arg; 
    int m = data[0];
    int M = data[1]; 
    if(m < 2) m = 2; 
    
   
    int np = 0; // 2 is a prime (1 doesnt count)
    for (int i = m; i <= M; i++)
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
    data[2] = np;
    printf("%s took %7.3f wall seconds.\n", __func__, get_wall_seconds()-time1);
    return NULL; 
}

int nprimes2(int m, int M){
    // Computer number of primes in [m,M] (m has to be >=2)

    int np = 0; 
    for (int i = m; i <= M; i+=4)
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

void *threaded_nprimes2(void *arg){
     // Computer number of primes in [m,M] (m has to be >=2)
    double time1 = get_wall_seconds();
    int * data = (int*)arg; 
    int m = data[0];
    int M = data[1]; 
    
    int np = 0; 
    for (int i = m; i <= M; i+=4)
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
    data[2] = np;
    printf("%s took %7.3f wall seconds.\n", __func__, get_wall_seconds()-time1);
    return NULL; 
}


int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Call as %s M where M is an integer", argv[0]); 
        return -1;
    }

    int M = atoi(argv[1]);

    // Serial implementation
    printf("\n\nSerial implementation\n");
    double time1 = get_wall_seconds();
    int np = nprimes(1,M);
    printf("There are %d primes between 1 and %d\n",np,M); 
    printf("nprimes in serial took %7.3f wall seconds.\n", get_wall_seconds()-time1);

    //Threaded implementation # 1 (between main and one other thread)
    printf("\n\nThreaded implementation #1\n");
    time1 = get_wall_seconds();
    int data[3];
    data[0] = M/2 + 1; 
    data[1] = M;  
    pthread_t thread;

    pthread_create(&thread,NULL,threaded_nprimes,&data); 

    np = nprimes(1,data[0]-1);

    pthread_join(thread,NULL);

    int total_primes = np + data[2]; 
    printf("There are %d primes between 1 and %d\n",total_primes,M); 
    printf("nprimes with 2 threads took %7.3f wall seconds.\n", get_wall_seconds()-time1);

    //Threaded implementation # 2 (between main and one other thread)
    printf("\n\nThreaded implementation #2\n");
    time1 = get_wall_seconds();
    data[0] = 5; 
    data[1] = M;  

    pthread_create(&thread,NULL,threaded_nprimes2,&data); 

    double time2 = get_wall_seconds();
    np = nprimes2(3,M);
    printf("nprimes in serial took %7.3f wall seconds.\n", get_wall_seconds()-time2);

    pthread_join(thread,NULL);

    total_primes = 1+np + data[2]; 
    printf("There are %d primes between 1 and %d\n",total_primes,M); 
    printf("nprimes with 2 threads took %7.3f wall seconds.\n", get_wall_seconds()-time1);

}