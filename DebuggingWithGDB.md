### Exemple d'utilisation de GDB

**Création du fichier :**

Créez le fichier `history.c` dans votre répertoire de travail et copiez-y le code suivant :

```C
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

    struct history *h = malloc(sizeof(struct history));
    if (h == NULL) {
        return NULL;
    }
    h->first = NULL;
    h->current = NULL;
    return h;
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

    struct page *p = malloc(sizeof(struct page));
    if (p == NULL) {
        return -1;
    }
    p->url = url;
    p->next = NULL;
    p->prev = NULL;
    if (h->first == NULL) {
        h->first = p;
        h->current = p;
    } else {
        if (h->current->next != NULL) {
            struct page *next = h->current->next;
            while (next != NULL) {
                struct page *next_next = next->next;
                free(next);
                next = next_next;
            }
        }
        h->current->next->prev = NULL; 
        h->current->next = p;
        p->prev = h->current;
        h->current = p;
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
    if (h->current != NULL && h->current->prev != NULL) {
        h->current = h->current->prev;
        return 1;
    } else {
        return 0;
    }
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
    if (h->current != NULL && h->current->next != NULL) {
        h->current = h->current->next;
        return 1;
    } else {
        return 0;
    }
}

/**
 * Libère TOUTE la mémoire allouée pour la structure history.
 *
 * @param h la structure history
 */
void history_free(struct history *h) {
    struct page *p = h->first;
    while (p != NULL) {
        struct page *next = p->next;
        free(p);
        p = next;
    }
    free(h);
}


void history_print(struct history *h) {
    struct page *p = h->first;
    while (p != NULL) {
        printf("%s\n", p->url);
        p = p->next;
    }
}

int main() {
    struct history *h = history_new();
    if (h == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return 1;
    }

    history_add(h, "http://example.com");
    history_add(h, "http://example.com/1");

    printf("Historique :\n");
    history_print(h);

    history_free(h);
    return 0;
}
```

**Compilation et exécution du programme :**

Compilez le programme avec la commande suivante :

```bash
clang -o history history.c
```

Exécutez le programme avec la commande suivante :

```bash
./history
```
Vous devriez obtenir une erreur de segmentation dans votre terminal.

**Recompilation avec débogage et utilisation de GDB :**

Recompilez le programme avec l'option `-g` pour inclure les informations de debugging :

```bash
clang -g -o history history.c
```

Lancez GDB avec le programme compilé `history` :

```bash
gdb ./history
```

Vous devriez avoir cet output :

```bash
GNU gdb (Ubuntu 15.0.50.20240403-0ubuntu1) 15.0.50.20240403-git
Copyright (C) 2024 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./history...
(gdb) 


```

Dans GDB, tapez "run" pour exécuter le programme, puis sélectionnez "n" pour continuer.

Vous devriez obtenir une erreur de segmentation. 

```bash
Debuginfod has been disabled.
To make this setting permanent, add 'set debuginfod enabled off' to .gdbinit.
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x00005555555552a3 in history_add (h=0x5555555592a0, url=0x555555556039 "http://example.com/1") at history.c:82
82              h->current->next->prev = NULL;
```

**Correction de la segmentation fault :**

Vous constatez que la segmentation fault se produit à la ligne 82 de `history.c`. 

Corrigez l'erreur, ensuite recompilez et exécutez de nouveau le programme pour vérifier que tout fonctionne correctement.

Normalement, vous devriez obtenir cet output dans votre terminal si votre correction est correcte :

```bash
Historique :
http://example.com
http://example.com/1
```

### Pour aller plus loin cette ressource peut vous aider :

[GDB](https://lepl1503.info.ucl.ac.be/syllabus/outils/gdb.html)
