#include <stdlib.h>
#include <stdio.h>

struct history {
    struct page *first;
    struct page *current;
};

struct page {
    char *url;
    struct page *next;
    struct page *prev;
};

/**
 * Crée une nouvelle structure history.
 * 
 * @return la structure history et NULL en cas d'erreur d'allocation de mémoire 
 */
struct history *history_new() {
    // TODO
    
    return NULL;
}

/**
 * Ajoute une nouvelle page à l'historique à partir de la page courante.
 * 
 * @param h la structure history
 * @param url l'URL de la page à ajouter. L'URL n'est ni copiée ni libérée par `history`.
 * L'utilisateur doit s'assurer que `url` reste valide aussi longtemps que l'historique l'utilise.
 * Si `url` a été alloué dynamiquement, c'est à l'utilisateur de le `free()`
 * après que l'historique n'en a plus besoin.
 *
 * // Exemple 1 : Utilisation d'une chaîne statique 
 *     history_add(h, "http://example.com");
 *     
 * // Exemple 2 : Utilisation d'une chaîne allouée dynamiquement 
 *     char *url = malloc(50);
 *     if (url) {
 *         strcpy(url, "http://example.com/page1");
 *         history_add(h, url);
 *     }

 *     // Utilisation de l'historique...
 *     
 *     // Libération de l'historique
 *     history_free(h);
 *     
 *     // L'utilisateur doit libérer les URL allouées dynamiquement après history_free()
 *     free(url);     
 * 
 * @return 0 si l'ajout a réussi, -1 sinon
 
 */
int history_add(struct history *h, char *url) {
    // TODO
    
    return -1;
}

/**
 * Recule d'une page dans l'historique.
 * Modifie le pointeur de la page courante vers la page précédente si elle existe.
 * 
 * @param h la structure history
 * 
 * @return 1 si le déplacement a réussi, 0 sinon
 */
int go_back(struct history *h) {
    // TODO
    
    return 0;
}

/**
 * Avance d'une page dans l'historique. 
 * Modifie le pointeur current vers la page suivante si elle existe.
 * 
 * @param h la structure history
 * 
 * @return 1 si le déplacement a réussi, 0 sinon
 */
int go_forward(struct history *h) {
    // TODO
    
    return 0;
}

/**
 * Libère TOUTE la mémoire allouée pour la structure history.
 * 
 * @param h la structure history
 */
void history_free(struct history *h) {
    // TODO
    
}






