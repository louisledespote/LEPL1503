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
    //On va crée les differents objets et on alloue de la memoir   
    struct history *new_history = malloc(sizeof(struct history)); 
    
    // On initialise les valeurs de first et current à NULL

    new_history->current == NULL;
    new_history->first == NULL;

    //on teste si history est null
    if(new_history == NULL){
        return NULL;
    }

    // On retourne l'history initialisé
    return new_history;
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
    struct page *new_page = malloc(sizeof(struct page));

    if (!h || !url) return -1;  
    if (!new_page) return -1;


    new_page->url = url;
    new_page->next = NULL;

    if (h->first == NULL) { 
        h->first = new_page;
        h->current = new_page;
        new_page->prev = NULL;
    } else {  
        new_page->prev = h->current;
        h->current->next = new_page;
        h->current = new_page;
    }
    

    return 0;
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
    if(h->current->prev != NULL){
        h->current = h->current->prev;
        return 1;
    }
    if (!h || !h->current) return 0;
    {
        return 0;
    }
    
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
    if(h->current->next != NULL){
        h->current = h->current->next;
        return 1;
    }
    if (!h || !h->current->next) return 0;
    {
        return 0;
    }
    
    return 0;
}

/**
 * Libère TOUTE la mémoire allouée pour la structure history.
 * 
 * @param h la structure history
 */
void history_free(struct history *h) {
    
    if (!h) return;  

    struct page *current = h->first;
    while (current) {
        struct page *next = current->next; 
        free(current);  
        current = next; 
    }

    free(h);
    
}






