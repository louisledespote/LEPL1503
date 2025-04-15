#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

int compteur = 0;
pthread_mutex_t mutex_compteur;

void *fonction_thread(void *arg) {
    
    for(int i = 0; i < 10000; i++) {
        
        compteur++;
        
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    
    pthread_mutex_init(&mutex_compteur, NULL);
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, fonction_thread, &thread_args[i]) != 0) {
            perror("Erreur lors de la création du thread");
            exit(EXIT_FAILURE);
        }
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Erreur lors de l'attente du thread");
            exit(EXIT_FAILURE);
        }
    }
    
    pthread_mutex_destroy(&mutex_compteur);

    printf("Compteur: %d\n", compteur);
    
    return 0;
}
