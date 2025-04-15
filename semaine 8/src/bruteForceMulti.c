#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <pthread.h>

#define NUM_THREADS 4

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

/**
 * Simule l'envoi d'un mot de passe et du nom d'utilisateur à un serveur
 * 
 * @param user Nom d'utilisateur
 * @param password Mot de passe
 * 
 * @return 1 si l'utilisateur et le mot de passe sont corrects, 0 sinon
 */
int login(char *user, char *password) {
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

    for (int i = data->thread_id; i < charset_size; i += NUM_THREADS) {
        password[0] = charset[i];
        for (int j = 0; j < charset_size; j++) {
            password[1] = charset[j];
            for (int k = 0; k < charset_size; k++) {
                password[2] = charset[k];
                for (int l = 0; l < charset_size; l++) {
                    password[3] = charset[l];

                    // Vérifier si déjà trouvé
                    pthread_mutex_lock(&found_mutex);
                    if (found_password != NULL) {
                        pthread_mutex_unlock(&found_mutex);
                        free(password);
                        pthread_exit(NULL);
                    }
                    pthread_mutex_unlock(&found_mutex);

                    // Tester le mot de passe
                    if (login(data->user, password)) {
                        pthread_mutex_lock(&found_mutex);
                        if (found_password == NULL) {
                            found_password = strdup(password);
                        }
                        pthread_mutex_unlock(&found_mutex);
                        free(password);
                        pthread_exit(NULL);
                    }
                }
            }
        }
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
    // On va stocker chaque thread dans un tableau
    pthread_t threads[NUM_THREADS];

    // on va créee une structure pour stocker chaque info liée au thread 
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
