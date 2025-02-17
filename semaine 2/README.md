# Semaine 2

Lors de cette deuxième semaine, nous allons implémenter certaines fonctions manipulant des chaînes de caractères. Les sections suivantes du syllabus pourraient vous aider:

- [Caractères et chaines de caractères](https://lepl1503.info.ucl.ac.be/syllabus/theorie/C/datatypes.html#caracteres-et-chaines-de-caracteres);
- [Les pointeurs](https://lepl1503.info.ucl.ac.be/syllabus/theorie/C/datatypes.html#les-pointeurs).

En parallèle, vous apprendrez à **tester vos implémentations** en utilisant `CUnit`.

Les exercices 1 à 7 réfèrent à des functions existantes du language C permettant la manipulation de string (faisant parties de la librarie `string.h`). Vous ne pouvez évidemment pas utilisez les implémentations existantes pour faire les votres, ni pour tester. 
Cependant, n'hésitez pas à **consulter la `manpage` des fonctions** afin d'avoir plus d'informations sur leur comportement. Sur Linux, vous pouvez le faire depuis le terminal avec la commande `man <nom_fonction>`.

Pour ces mêmes exercices (1 à 7), des tests vous sont fournis dans le fichier `my_lib.c` dans le dossier `test`. N'hésitez pas à y ajouter vos propre tests !

## TODO

### Partie implémentation

1. Implémentez la fonction `my_strlen` dans le fichier `my_lib.c`. Cette fonction doit renvoyer la longueur de la chaîne de caractères passée en argument. 
    
    *Indice : Consultez le syllabus pour savoir comment reconnaître la fin d'une chaîne de caractères.*

2. Complétez la fonction `my_get`, qui renvoie le caractère dans la chaîne de caractères à l'indice fourni ou `'\0'` si l'indice n'est pas valide.

3. Complétez la fonction `my_count`, qui compte le nombre d'occurrences d'un caractère dans la chaîne de caractères.

4. Complétez la fonction `my_strcmp`, qui compare deux chaînes de caractères. Elle renvoie une valeur négative si la première chaîne est inférieure à la seconde, une valeur positive si la première chaîne est supérieure à la seconde et une valeur nulle si les deux chaînes sont égales. La comparaison doit être faite en utilisant l'ordre lexicographique.
    
    *Indice : plus grand, plus petit pour des chaînes de caractères ? Conulter le syllabus (et une table ASCII ?).*

5. Complétez la fonction `my_strpbrk`, qui renvoie un pointeur vers la première occurrence dans une chaîne de caractères parmi une liste de caractères recherchés. 

    Exemple : `my_strpbrk("hello, world", "ol")` -> pointeur vers le premier 'l' de "hello".

6. **INTRO MALLOC (semaine 3)** : Complétez la fonction `my_strdup`, qui renvoit un pointeur vers une copie de la chaîne de caractères passée en argument. Nous utiliserons la fonction `malloc` pour alloué un nouvel espace mémoire afin d'y copier la chaîne de caractères. Le code nécessaire pour allouer cet espace mémoire vous est fourni; n'hésitez pas à le lire et le comprendre. 

    *PS: N'hésitez pas à vous renseigner davantage sur l'utilisation de la fonction `malloc`, c'est une fonction très importante en C.*

7. **INTRO MALLOC (semaine 3)** : Complétez la fonction `my_append`, qui renverra un pointeur vers une nouvelle chaîne de caractères correspondant à la concaténation de 2 chaines de caractères passées en argument. À nouveau, essayez de comprendre l'utilisation de `malloc` dans ce cas-ci.

### Partie test

8. Dans le fichier `test.c` dans le dossier `tests`, essayez de comprendre le fonctionnement du programme de tests. **Ajoutez un test** pour chaque suite de tests.

9. Nous vous avons fourni la fonction `my_factorial`. Cette fonction calcule simplement la factorielle d'un nombre. Complétez la fonction `test_my_factorial` pour ajouter une suite de tests. Ajoutez-la ensuite dans la fonction `main` du fichier `tests/my_lib.c`. Les valeurs à tester doivent couvrir l'ensemble du domaine des valeurs possibles, cela inclut les valeurs négatives interdites. Pensez aussi aux cas limites (observez l'implémentation).

    *Indice: Le chapitre sur [les nombres entiers](https://lepl1503.info.ucl.ac.be/syllabus/theorie/C/datatypes.html#nombres-entiers) du syllabus peut vous aider.*

10. Lancez les tests avec `make test` ou `make`.

11. Vous aurez peut-être remarqué qu'une variable globale, `debug_mode`, est présente. Cette variable peut prendre les valeurs 1 ou 0 en fonction de si vous souhaitez, ou non, ajouter des informations de `débogage`. Observez son utilisation dans la fonction `my_factorial` et essayez de la transposer à vos fonctions. Souvenez-vous, pour les semaines à venir, qu'inclure cette variable peut être une bonne pratique.

Si tous vos tests passent, félicitations, vous commencez à bien appréhender le C.