#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>

// Base de données contenant les utilisateurs et les mots de passe hachés
const int db_size = 3;
const char *username[] = {"Corentin", "Antoine", "Melanie"};
const char *hashpassword[] = {"aa01GHsDYPZU6", "aapOLy4V6kWdA", "aaTg9vp2wmizQ"};

const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int charset_size = 62;

/**
 * Simule l'envoi d'un mot de passe et du nom d'utilisateur à un serveur
 * 
 * @param user Nom d'utilisateur
 * @param password Mot de passe
 * 
 * @return 1 si l'utilisateur et le mot de passe sont corrects, 0 sinon
 */
int login(char *user, char *password) {
    if (password == NULL) {
        fprintf(stderr, "password est NULL !\n");
        return 0;
    }
    for (int i = 0; i < db_size; i++) {
        if (strcmp(user, username[i]) == 0) {
            /**
             * Nous utilisons un salt fixe dans le cadre de cet exercice ("aa").
             * Visitez l'article original du salt pour en savoir plus : https://dl.acm.org/doi/pdf/10.1145/359168.359172 
             */
            if (strcmp(crypt(password, "aa"), hashpassword[i]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Fonction pour trouver le mot de passe en mono-thread
 * 
 * @param user Nom d'utilisateur
 * 
 * @return Mot de passe trouvé, NULL sinon
 */
char *bruteForceSimple(char *user) {
    int charset_size = strlen(charset);
    
    for(int i = 0; i < charset_size; i++) {
        for(int j = 0; j < charset_size; j++) {
            for(int k = 0; k < charset_size; k++) {
                for(int l = 0; l < charset_size; l++) {
                    char *password = malloc(5 * sizeof(char));
                    if (password == NULL) {
                        return NULL;
                    }
                    password[0] = charset[i];
                    password[1] = charset[j];
                    password[2] = charset[k];
                    password[3] = charset[l];
                    password[4] = '\0';

                    if (login(user, password)) {
                        return password;
                    }
                    free(password);
                }
            }
        }
    }

    return NULL;
}
