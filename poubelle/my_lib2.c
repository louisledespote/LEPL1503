#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int debug_mode = 1;

/**
 * Renvoie la longueur de la chaîne de caractères str.
 * 
 * @param str la chaîne de caractères
 * 
 * @return la longueur de la chaîne de caractères
 */
int my_strlen(const char *str) {
    int length = strlen(str);
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        len++;
    }
    
    

    return len;
}

/**
 * Renvoie le caractère à l'index donné de la chaîne de caractères str.
 * 
 * @param str la chaîne de caractères
 * @param index l'index du caractère
 * 
 * @return le caractère de la chaîne de caractères à l'index donné ou '\0' si l'index est en dehors de la chaîne
 */
char my_get(const char *str, int index) {

    
    
    return str [index];
}

/**
 * Renvoie le nombre d'occurrences du caractère c dans la chaîne de caractères str.
 * 
 * @param str la chaîne de caractères
 * @param c le caractère
 * 
 * @return le nombre d'occurrences du caractère c dans la chaîne de caractères
 */
int my_count(const char *str, char c) {
    int len = 0; 
    for (int i = 0; str[i] != '\0'; i++) {
        if(str[i] == c){
            len ++;
        };
    };
        
    return len;
}

/**
 * Compare deux chaînes de caractères.
 * 
 * Exemples :
 * - my_strcmp("abc", "abc") renvoie 0
 * - my_strcmp("abc", "abcd") renvoie un entier négatif
 * - my_strcmp("abcd", "abc") renvoie un entier positif
 * - my_strcmp("abc", "def") renvoie un entier négatif
 * - my_strcmp("def", "abc") renvoie un entier positif
 * 
 * @param str1 la première chaîne de caractères 
 * @param str2 la deuxième chaîne de caractères
 * 
 * @return un entier négatif si str1 est inférieure à str2, un entier positif si str1 est supérieure à str2, 0 sinon
 */
int my_strcmp(const char *str1, const char *str2) {
    int i = 0; 
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];  
        }
        i++;
    }   
    return str1[i] - str2[i]; 
    
}

/**
 * Renvoie un pointeur sur la première occurrence dans la chaîne de caractères str
 * d'un des caractères de la chaîne de caractères search.
 * 
 * Exemples :
 * - my_strpbrk("hello", "world") renvoie un pointeur sur le premier caractère 'l' de la chaîne de caractères "hello"
 * - my_strpbrk("house", "oiu") renvoie un pointeur sur le premier caractère 'o' de la chaîne de caractères "house"
 * - my_strpbrk("house", "abc") renvoie NULL
 * 
 * @param str la chaîne de caractères
 * @param search la chaîne de caractères contenant les caractères à rechercher
 * 
 * @return un pointeur vers la première occurrence dans la chaîne de caractères str 
 *         d'un des caractères de la chaîne de caractères search
 */
char *my_strpbrk(char *str, char *search) {
    for(int j = 0; str[j] != '\0'; j++)  {  
        for (int i = 0; search[i] != '\0'; i++) { 
            if (str[j] == search[i]) {
                return str+j; 
            }
        }
    }
    return NULL;
 
}
/**
 * Renvoie une copie de la chaîne de caractères str.
 * 
 * @param str la chaîne de caractères
 * 
 * @return une copie de la chaîne de caractères ou NULL en cas de problème d'allocation de mémoire.
 */
char * my_strdup(const char *str) {
    int len = my_strlen(str);

    // allocation de la mémoire pour la nouvelle chaîne de caractères de taille len + 1
    // sizeof(char) correspond à la taille d'un caractère en octets dans la mémoire
    // cette fonction renvoie un pointeur vers la première adresse mémoire allouée
    char *new_str = (char *) malloc((len + 1) * sizeof(char)); // Question: Pourquoi len + 1 au lieu de len ?
    if (new_str == NULL) {
        return NULL;
    }
    else {
        for(int i = 0; str[i] != '\0'; i++){
            new_str[i] = str[i];
        }
        new_str[len] = '\0';
        return new_str;
    }

    // TODO
    
}

/**
 * Renvoie une nouvelle chaîne de caractères résultant de la concaténation de str1 et str2.
 * 
 * @param str1 la première chaîne de caractères
 * @param str2 la deuxième chaîne de caractères
 * 
 * @return une nouvelle chaîne de caractères résultant de la concaténation de str1 et str2 ou NULL en cas de problème d'allocation de mémoire.
 */
char * my_append(const char *str1, const char *str2) {
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);
    char *new_str = (char *) malloc((len1 + len2 + 1) * sizeof(char)); // Question: Et ici, pourquoi len1 + len2 + 1 ?
    if (new_str == NULL) {
        return NULL;
    }

    for (int i = 0; i < len1; i++) {
        new_str[i] = str1[i];
    }

    for (int i = 0; i < len2; i++) {
        new_str[len1 + i] = str2[i];
    }

    new_str[len1 + len2] = '\0';

    return new_str;
}

/**
 * Renvoie la factorielle de n.
 * 
 * @param n un entier
 * 
 * @return la factorielle de n
 */

int my_factorial(int n) {
    if (n < 0) {
        if (debug_mode) {
            printf("Erreur : Factorielle de nombre négatif n'est pas définie.\n");
        }
        return -1;
    }
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
        if (debug_mode) {
            printf("Étape %d : %d\n", i, result);
        }
    }
    return result;
}
