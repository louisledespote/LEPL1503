# Semaine 1

Cette première semaine sera l'occasion pour vous de vous familiariser avec les commandes de base dans un terminal, ainsi qu'avec l'exécution de programmes et de tests simples. Il est important de comprendre ce qui se passe à chaque étape, car ce seront des notions essentielles pour la suite du cours.

**Avant la première session**, vérifiez impérativement les points suivants : 

* Faire les instructons dans le fichier [BEFORE_THE_LAB.md](https://forge.uclouvain.be/lepl15031/students/practical-sessions/2024-2025/-/blob/main/BEFORE_THE_LAB.md?ref_type=heads).
* [Lire l’introduction du syllabus](https://lepl1503.info.ucl.ac.be/syllabus/theorie/intro.html).  

## TODO

1. Ouvrez un terminal et naviguez dans les dossiers pour vous retrouver au même niveau que ce README. Utilisez la commande `pwd` pour afficher le dossier courant et `cd NOM_DOSSIER` pour accéder à un dossier. Vous pouvez aussi utiliser `ls` pour afficher le contenu du dossier et `cd ..` pour remonter vers le dossier parent. Essayez ces différentes commandes dans votre terminal. Vous devriez ensuite vous trouver dans un dossier '..../2024-2025/semaine 1'. Pour obtenir des informations détaillées sur une commande, utilisez `man NOM_COMMANDE`. Par exemple, `man ls` vous donnera des informations sur la commande `ls`.


2. Entrez la commande `mkdir src` pour créer un dossier nommé `src`.

3. Accédez à ce dossier avec la commande `cd src`.

4. Entrez la commande `nano main.c` pour créer un fichier et l'éditer en ligne de commande.

5. Copiez-y le code suivant et enregistrez le fichier.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Hello World\n");
    return 0;
}
```

6. Entrez la commande `cat main.c` pour vérifier le contenu du fichier. Entrez `ls` pour afficher le contenu du dossier.

7. Compilez le fichier en entrant la commande `clang main.c -o main`. `clang` est l'un des compilateurs les plus populaires pour transformer votre code écrit en C en langage machine exécutable par votre ordinateur. Cette commande prend en argument le nom du fichier à compiler `main.c` et l'option `-o` suivie d'un nom, indiquant le nom du fichier compilé. Si vous n'avez pas `clang` installé, visiter [ce site](https://wiki.student.info.ucl.ac.be/Logiciels/CLang).

8. Exécutez le programme en entrant `./main`. Vous devriez voir apparaître 'Hello World'.

9. Revenez au dossier parent avec `cd ..`.

10. Exécutez le code depuis le dossier parent en utilisant `./src/main`.

11. Supprimez le fichier compilé en faisant `rm src/main`.

12. Créez un fichier Makefile de la même manière que précédemment avec `nano Makefile` et copiez-y le code suivant :

```makefile
# Cible par défaut. Exécute `main`.
all: main

# Compile `src/main.c` en `src/main`.
main: src/main.c
	clang -o src/main src/main.c

# Exécute `src/main`. Dépend de `main` pour garantir que l'exécutable est à jour.
run: main
	./src/main

# Supprime l'exécutable `src/main`.
clean:
	rm -f src/main

```

Un Makefile nous permet de simplifier l'exécution de plusieurs commandes. Par exemple, ici la commande `make` appellera `main`, ce qui exécutera la compilation. Essayez de compiler le programme avec `make` ou `make main`, lancez le programme avec `make run` et supprimez l'exécutable avec `make clean`. Si vous n'avez pas `make` installé, exécutez `sudo apt install make` pour l'installer sur linux.

13. Accédez à `src` avec `cd src` et créez un nouveau fichier `mediane.c`. Copiez-y le code suivant :

```c
#include "mediane.h"

/**
 * @brief Computes the median of three integers.
 *
 * This function takes three integer arguments and returns the median value.
 * The median is the middle value when the integers are sorted in ascending order.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @param c The third integer.
 * @return The median of the three integers.
 */
int mediane(int a, int b, int c) {
    if ((a >= b && a <= c) || (a <= b && a >= c)) {
        return a;
    } else if ((b >= a && b <= c) || (b <= a && b >= c)) {
        return b;
    } else {
        return c;
    }
}
```

14. Créez un fichier `mediane.h` et mettez-y le code suivant :

```c
#ifndef MEDIANE_H_
#define MEDIANE_H_

int mediane(int a, int b, int c);

#endif
```

Je vous renvoie vers le syllabus pour comprendre le rôle d'un fichier `.h`.

15. Revenez en arrière avec `cd ..`, créez un nouveau dossier `tests` avec `mkdir tests` et accédez-y avec `cd tests`.

16. Créez un fichier `test.c` avec `nano test.c` et copiez-y le code suivant :

```c
#include <CUnit/Basic.h>
#include "../src/mediane.c"

// Fonction de test unique pour mediane()
void test_mediane(void) {
    CU_ASSERT_EQUAL(mediane(3, 5, 8), 5);
    CU_ASSERT_EQUAL(mediane(2, 1, 9), 2);
    CU_ASSERT_EQUAL(mediane(-1, 3, 2), 2);
}

int main() {
    CU_initialize_registry();

    // Création de la suite de tests
    CU_pSuite pSuite = CU_add_suite("Suite de tests pour mediane()", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ajout du test à la suite
    if (NULL == CU_add_test(pSuite, "Test de la fonction mediane()", test_mediane)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Exécution des tests
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
```

Ce code nous permet de tester le fonctionnement d'un programme en spécifiant l'entrée et de vérifier si la sortie correspond à celle attendue. Prenez le temps de comprendre comment fonctionne ce programme. Si vous n'avez pas CUnit installé, visiter [ce site](https://wiki.student.info.ucl.ac.be/Logiciels/CLang) pour l'installation.

17. Compilez le code de tests avec `clang test.c -o test -lcunit`.

18. Lancez les tests avec `./test` et analysez les résultats.

19. Ajoutez de nouveaux tests au fichier `test.c` (d'autre cas limites, par example le cas où l'on utilise de [très grande valeur](https://learn.microsoft.com/en-us/cpp/c-language/cpp-integer-limits?view=msvc-170), il faudra peut-être rajouter un [header](https://www.man7.org/linux/man-pages/man0/limits.h.0p.html)).  Essayez d'ajouter un test incorrect, par example le cas où `a` est `NULL`, et vérifiez le résultat. Comment le compilateur réagit-il à ce cas ?

20. Modifiez le `Makefile` pour ajouter une cible `test` qui compile et exécute les tests. 

Félicitations, vous savez maintenant construire un programme en C, le compiler, l'exécuter, accélérer le développement avec un Makefile et écrire une suite de tests.