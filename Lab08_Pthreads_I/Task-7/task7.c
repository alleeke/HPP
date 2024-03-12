#include <stdio.h>
#include <pthread.h>

void *my_thread_func2(void *arg){
    
    long phid = (long)arg;
    printf("Hello from thread %ld\n", phid); 

    return NULL; 
}

void *my_thread_func(void *arg){
    pthread_t threadA,threadB;

    long phid = (long)arg;
    printf("Hello from thread %ld\n", phid); 
    
    pthread_create(&threadA,NULL,my_thread_func2,(void*)3);
    pthread_create(&threadB,NULL,my_thread_func2,(void*)4);

    return NULL;
}


int main(){
    pthread_t threadA,threadB;
    
    pthread_create(&threadA,NULL,my_thread_func,(void*)1);
    pthread_create(&threadB,NULL,my_thread_func,(void*)2);

    pthread_exit(NULL); 


    return 0;
}