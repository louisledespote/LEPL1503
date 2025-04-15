#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>

// Base de données contenant les utilisateurs et les mots de passe hachés
int db_size = 3;
const char *username[] = {"Corentin", "Antoine", "Melanie"};
const char *hashpassword[] = {"aaHgH6E8QomwA", "aandyfwrUkmFE", "aaQe9fBjM9Rsw"};

static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static const int charset_size = 62;

/**
 * Simule l'envoi d'un mot de passe et du nom d'utilisateur à un serveur
 * 
 * @param user Nom d'utilisateur
 * @param password Mot de passe
 * 
 * @return 1 si l'utilisateur et le mot de passe sont corrects, 0 sinon
 */
int login(char *user, char *password) {
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
 * Fonction récursive pour trouver le mot de passe utilisé dans la fonction bruteForceAdvance
 * 
 * @param user Nom d'utilisateur
 * @param password Mot de passe en cours de construction
 * @param pos Position actuelle dans le mot de passe
 * @param len Longueur du mot de passe
 * 
 * @return Mot de passe trouvé, NULL sinon
 */
char* bruteForceHelper(char *user, char *password, int pos, int len) {

    if (pos == len) {
        password[len] = '\0';
        if (login(user, password)) {
            return strdup(password);
        }
        return NULL;
    }
    
    for (int i = 0; i < charset_size; i++) {
        password[pos] = charset[i];
        char *found = bruteForceHelper(user, password, pos + 1, len);
        if (found != NULL) {
            return found;
        }
    }
    
    return NULL;
}

/**
 * Fonction pour trouver le mot de passe
 * 
 * @param user Nom d'utilisateur
 * 
 * @return Mot de passe trouvé, NULL sinon
 */
char *bruteForceAdvance(char *user) {
        
    return NULL;
}
