# Semaine 5

Cette semaine, nous allons apprendre à manipuler des fichiers binaires pour y lire et écrire des informations. Pour cela, nous allons stocker des nombres réels (float) dans un fichier binaire au format `.dat` (data). Il s'agit d'un format binaire brut où des nombres flottants seront stockés les uns après les autres.

Le premier nombre sera un entier spécifiant le nombre de réels dans le fichier. Ensuite, la suite des réels qui nous intéresse sera stockée. Notez que la mise en binaire d'un entier dépend de votre système d'exploitation (OS). En effet, ils peuvent être représentés sous forme [Big Endian ou Little Endian](https://en.wikipedia.org/wiki/Endianness). Afin que cet exercice soit formaté de la même manière pour tout le monde, nous allons utiliser le format standard utilisé sur le réseau pour représenter les nombres entiers : Big Endian. Pour cela, vous devez utiliser la fonction `htonl` pour convertir de la représentation de l'OS à celle du réseau, et `ntohl` pour convertir de la représentation réseau à celle de l'OS.

Par exemple, si nous avons les 3 floats 2.1, 4.1 et 9.12, le fichier commencera par un entier représentant la valeur 3, suivit ensuite par les 3 floats. Le données seront donc ordonnées de la sorte dans le fichier : [3, 2.1, 4.1, 9.12]

N'oubliez pas de consulter la [section du syllabus dédiée aux systèmes de fichiers en C](https://sites.uclouvain.be/SyllabusC/notes/Theorie/Fichiers/fichiers.html#systemes-de-fichiers) pour réaliser les exercices de cette semaine.

## TODO

1. Commencez par ouvrir le fichier Python `buildReals.py` qui construit le fichier binaire. Comprenez son fonctionnement. Lancez-le afin de construire le binaire dans le dossier `datas`. Vous pouvez modifier `file_name` et `float_values`, mais n'oubliez pas de modifier les tests en conséquence.

2. Ouvrez le fichier `real_manager` et complétez la fonction `getAverage`. Cette fonction doit renvoyer la moyenne des floats du binaire en utilisant `mmap`. Indice : Commencez par ouvrir le fichier avec `open`, calculez sa taille grâce à `fstat`, utilisez `mmap` pour mapper le fichier en mémoire. N'oubliez pas de manipuler les pointeurs et d'utiliser `sizeof` afin de lire uniquement les floats et pas le premier int. La fonction doit utiliser l'appel `exit(EXIT_FAILURE)` en cas d'échec à l'une des étapes. N'oubliez pas d'utiliser 'ntohl' pour convertir le premier entier du fichier.

3. Complétez la fonction `changeReal` qui prend en argument un index et un float. Cette fonction doit modifier le float dans le binaire à l'index fourni (le int ne compte pas dans le calcul des index) par le nouveau float. Indice : Utilisez toujours `mmap`. Elle renvoie -1 en cas d'erreur ou de mauvais index et 0 sinon. Intéressez-vous aux différents arguments de la fonction `mmap`, le reste ressemble à la première fonction. N'oubliez pas d'utiliser 'ntohl' pour convertir le premier entier du fichier.

4. Ouvrez le fichier de tests et comprenez son fonctionnement. Lancez les tests grâce au Makefile et vérifiez qu'ils passent tous. N'hésitez pas à jouer avec le fichier Python et à modifier les tests.

## Outils pour le projet (1)

Cette semaine, nous allons introduire l'outil `Valgrind`. Il s'agit d'un outil très utile pour votre projet. Nous en présenterons d'autres la semaine prochaine. Valgrind permet de vérifier que la mémoire allouée avec `malloc` a bien été libérée avec `free`. Si ce n'est pas le cas, il se peut que la mémoire allouée augmente sans arrêt, ce qui résulte en [une fuite de mémoire ou memory leak](https://fr.wikipedia.org/wiki/Fuite_de_m%C3%A9moire).

Commencez par installer Valgrind en suivant [ce lien](https://wiki.student.info.ucl.ac.be/Logiciels/GCC).

5. Ouvrez le code `leak.c`. Ce code simple permet de créer, de multiplier et d'afficher des fractions. Lancez la commande `gcc -o src/leak -g src/leak.c` pour compiler le fichier. Lancez Valgrind avec `valgrind --leak-check=full ./src/leak`. Vous pouvez aussi le faire avec `make valgrind`.

6. Analysez la sortie. Ce code contient des fuites de mémoire ; corrigez-le en ajoutant des `free` jusqu'à ce qu'il n'y en ait plus.

Vous pouvez trouver plus d'informations sur Valgrind en suivant [ce lien](https://sites.uclouvain.be/SyllabusC/notes/Outils/valgrind.html)