#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *thread_func(void *arg){
    long thid = (long)arg;
    printf("Hello from thread%ld\n", thid); 

    return NULL;

}

int main(int argc, char *argv[]){
    
    if(argc != 2){
        printf("Call as %s N, where N is a integer", argv[0]); 
        return -1;
    }

    int N = atoi(argv[1]);
    pthread_t threads[N]; 

    for (long i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, thread_func,(void*)i);
    
    pthread_exit(NULL); 
    


    return 0;
}