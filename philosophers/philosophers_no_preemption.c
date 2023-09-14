#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PHILS 5
pthread_mutex_t forks[NUM_PHILS];

void init();
int leftOf(int i);
int rightOf(int i);
void* philosopher(void* param);
void think(int id);
void eat(int id);
void get_forks(int id);
void put_forks(int id);

int main(){
    pthread_t *thd_arr; // thread array
    thd_arr = malloc(sizeof(pthread_t) * NUM_PHILS); 

    for(int i = 0; i < NUM_PHILS; i++){
        pthread_mutex_init(&forks[i], NULL);
    }   

    for(int i = 0; i < NUM_PHILS; i++){
        pthread_create(&thd_arr[i], NULL, philosopher, (void*) &i);
        usleep((1 + rand() % 50) * 10000);
    }

    for(int i = 0; i < NUM_PHILS; i++){
        pthread_join(thd_arr[i], NULL);
    }
    return 0;
}

int leftOf(int i){
    return (i) % NUM_PHILS;
}

int rightOf(int i){
    return (i + 1) % NUM_PHILS;
}

void* philosopher(void* param){
    int id = *((int *) param);
    while(1){
        think(id);
        get_forks(id);
        eat(id);
        put_forks(id);
    }
}

void think(int id){
    printf("%d: Now, I'm thinking...\n", id);
}

void eat(int id){
    printf("%d: Now, I'm eating...\n", id);
}

void get_forks(int id){
    while (1){
        pthread_mutex_lock(&forks[leftOf(id)]);
        if (pthread_mutex_trylock(&forks[rightOf(id)]) != 0){
            pthread_mutex_unlock(&forks[leftOf(id)]);    
        } else{
            break;
        }   
    }
}

void put_forks(int id){
    pthread_mutex_unlock(&forks[leftOf(id)]);
    pthread_mutex_unlock(&forks[rightOf(id)]);
}
