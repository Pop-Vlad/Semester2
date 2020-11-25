#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int odd_numbers = 0;
int even_numbers = 0;
pthread_mutex_t mtx;

void* generator(void* arg){
        while(1){
                int nr = random();
                int odd = nr % 2;
                pthread_mutex_lock(&mtx);
                if(odd_numbers >= 100 && even_numbers >= 100){
                        pthread_mutex_unlock(&mtx);
                        return NULL;
                }
                if(odd)
                        odd_numbers++;
                else
                        even_numbers++;
                pthread_mutex_unlock(&mtx);
        }
        return NULL;
}

int main(int argc, char** argv){
        pthread_t t[7];
        srandom(time(0));
        pthread_mutex_init(&mtx, NULL);
        int i;
        for(i=0; i<7; i++)
                pthread_create(&t[i], NULL, generator, NULL);
        for(i=0; i<7; i++)
                pthread_join(t[i], NULL);
        pthread_mutex_destroy(&mtx);
        printf("Odd: %i\n", odd_numbers);
        printf("Even: %i\n", even_numbers);
        return 0;
}