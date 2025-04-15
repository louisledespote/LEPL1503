#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <pthread.h>

#define NUM_THREADS 5

// Base de données contenant les utilisateurs et les mots de passe hachés
const int db_size = 3;
const char *username[] = {"Corentin", "Antoine", "Melanie"};
const char *hashpassword[] = {"aa01GHsDYPZU6", "aapOLy4V6kWdA", "aaTg9vp2wmizQ"};

const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int charset_size = 62;

typedef struct {
    char *user;
    int thread_id;
} thread_data_t;

pthread_mutex_t found_mutex = PTHREAD_MUTEX_INITIALIZER;
char *found_password = NULL;


int loginMulti(char *user, char *password) {
    struct crypt_data data;
    data.initialized = 0;

    for (int i = 0; i < db_size; i++) {
        if (strcmp(user, username[i]) == 0) {
            char *hash = crypt_r(password, "aa", &data);
            if (hash != NULL && strcmp(hash, hashpassword[i]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int loginSimple(char *user, char *password) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(user, username[i]) == 0) {
            if (strcmp(crypt(password, "aa"), hashpassword[i]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Fonction exécutée par chaque thread pour trouver le mot de passe
 * 
 * @param arg les données du thread
 */
void *bruteForceThread(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    char * password = malloc(5 * sizeof(char));
    if (password == NULL) {
        pthread_exit(NULL);
    }

    password[4] = '\0';
    
    for(int i = data->thread_id; i < charset_size; i += NUM_THREADS) {
        // TODO
        
    }

    free(password);
    pthread_exit(NULL);
}

/**
 * Fonction pour trouver le mot de passe en utilisant plusieurs threads
 * 
 * @param user Nom d'utilisateur
 * 
 * @return Mot de passe trouvé, NULL sinon
 */
char *bruteForceMulti(char *user) {
    found_password = NULL;
    pthread_t threads[NUM_THREADS];
    thread_data_t * thread_data = malloc(NUM_THREADS * sizeof(thread_data_t));
    if (thread_data == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].user = user;
        thread_data[i].thread_id = i;
        pthread_create(&threads[i], NULL, bruteForceThread, &thread_data[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return found_password;
}

/**
 * Fonction pour trouver le mot de passe en mono-thread
 * 
 * @param user Nom d'utilisateur
 * 
 * @return Mot de passe trouvé, NULL sinon
 */
char *bruteForceSimple(char *user) {
    // TODO
    
    return NULL;
}


int main() {
    char *user = "Corentin";
    char *password = bruteForceSimple(user);
    if (password != NULL) {
        printf("Mot de passe trouvé (bruteForceSimple): %s\n", password);
    } else {
        printf("Mot de passe non trouvé (bruteForceSimple)\n");
    }

    password = bruteForceMulti(user);
    if (password != NULL) {
        printf("Mot de passe trouvé (bruteForceMulti): %s\n", password);
    } else {
        printf("Mot de passe non trouvé (bruteForceMulti)\n");
    }

    return 0;
}

