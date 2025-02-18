# Semaine 3

Cette semaine, nous allons apprendre à maîtriser les fonctions de gestion de la mémoire introduites la semaine dernière ainsi que les structures. Pour cela, nous allons implémenter un historique de navigation web étape par étape. Le but sera de pouvoir aller en arrière ou en avant dans l'historique de navigation d'un utilisateur.

L'idée est de représenter une page web par une structure contenant l'URL de la page et pointant vers la page précédente et vers la page suivante.

```
    First               Current      
      |                    |
      V                    V
+-----------+        +-----------+        +-----------+
|   Site A  |        |   Site B  |        |   Site C  |
|-----------|        |-----------|        |-----------|
| url: "A"  |        | url: "B"  |        | url: "C"  |
|-----------|        |-----------|        |-----------|
| next: B   |------->| next: C   |------->| next: NULL|
| prev: NULL|<-------| prev: A   |<-------| prev: B   |
+-----------+        +-----------+        +-----------+
```

Les sections suivantes du syllabus pourraient vous aider:

- [Les structures](https://lepl1503.info.ucl.ac.be/syllabus/theorie/C/datatypes.html#les-structures)

- [Les pointeurs](https://lepl1503.info.ucl.ac.be/syllabus/theorie/C/datatypes.html#les-pointeurs)

- [L'organisation de la mémoire](https://lepl1503.info.ucl.ac.be/syllabus/theorie/C/malloc.html#organisation-de-la-memoire)

## Structures

Voici les deux structures à votre disposition : 

**History :** Structure représentant l'historique
- **first :** Pointeur vers la première page de l'historique
- **current :** Pointeur vers la page actuellement visitée

**Page :** Structure représentant une page web
- **url :** Chaîne de caractères contenant l'URL de la page web
- **next :** Pointeur vers la prochaine page à partir de cette page
- **prev :** Pointeur vers la page précédente à partir de cette page

## TODO

1. Compléter la fonction `history_new` renvoyant un nouvel historique, où `first` et `current` doivent pointer vers `NULL`. La fonction renvoie `NULL` si l'appel à `malloc` échoue.

2. Compléter `history_add`. Cette fonction doit ajouter une nouvelle page à partir de `current` et modifier ce `current` vers la nouvelle page. La fonction renvoie -1 si l'appel à `malloc` échoue et 0 sinon. Indice : Que se passe-t-il lorsque l'on ajoute la première page ?

3. Compléter `go_back`. Cette fonction permet de revenir à la page précédente en modifiant `current`. Elle renvoie 1 si l'exécution réussi et 0 sinon. Indice : Dans quel cas cela peut-il échouer ?

4. Compléter `go_forward`. Cette fonction permet d'avancer vers la page suivante à partir de `current`. Elle renvoie 1 si l'exécution réussi et 0 sinon.

5. Compléter `history_free`. Cette fonction permet de libérer la mémoire en utilisant la commande `free` sur toutes les pages et sur l'historique.

6. BONUS : Que se passe-t-il si vous ajoutez une page (`history_add`) alors que vous aviez déjà des pages devant vous ? Sont-elles bien libérées ? Si la réponse est non, vous pourriez obtenir des fuites de mémoire. Modifier la fonction `history_add` pour gérer ce cas. Utilisez des outils comme Valgrind pour vérifier les fuites de mémoire.

7. Lancer les tests avec `make test`. Vérifiez que tous les tests passent et n'hésitez pas à les analyser en cas de difficultés afin de comprendre ce qui vous est demandé.
