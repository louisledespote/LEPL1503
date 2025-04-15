# LEPL1503 - Projet 2025 - Groupe J1

## Description du projet

Ce projet consiste à réaliser des opérations élémentaires sur les matrices et vecteurs.


## Lancer le programme


Pour compiler le projet, entrez la commande


```sh
make
```

L'exécutable est alors généré à la racine du projet. Pour l'utiliser, entrez la commande

```sh
./main [-v] [-f output_stream] name_op input_file_A [input_file_B]
```


Les arguments entre crochets sont optionnels. Les opérations disponibles sont : ```add_m_m```,``` sub_m_m```, ```mult_m_v```, ```mult_m_m```, ```dot_prod```,  ```transp```, ```lstsq```, ```suv_v_v```, ```add_v_v``` et ```back_sub```.


La commande ```./main -h``` permet d'avoir des explications sur les différents paramètres (les docstrings).

Les fichiers d'entrée et de sortie sont au format binaire. Pour un vecteur et une matrice, le fichier prend le même format que celui indiqué dans l'énoncé du projet.


Pour lancer les tests, tapez la commande

```sh
make test
```

Enfin, pour nettoyer le projet en senlevant les fichiers objets et les exécutables, utilisez la commande

```sh
make clean
```


## Fonctions du programme


- ```add_v_v``` : l'addition de 2 vecteurs
- ```sub_v_v``` : la soustraction de 2 vecteurs
- ```dot_prod```: le produit scalaire entre deux vecteurs 
- ```norm``` : la norme d’un vecteur
- ```init_vector``` :  crée un vecteur
- ```print_vector``` : permet d'afficher le vecteur
- ```free_vector``` : libère le vecteur
- ```init_matrix``` : crée une matrice
- ```print_matrix``` : permet d'afficher la matrice 
- ```free_matrix``` : libère la matrice 
- ```add_m_m``` : l'addition de 2 matrices
- ```sub_m_m``` : la soustraction de 2 matrices
- ```mult_m_v``` : la multiplication entre une matrice et un vecteur
- ```mult_m_m``` : la multiplication entre deux matrices
- ```transp``` : la transposée d’une matrice
- ```back_sub``` : la substitution arrière 
- ```qr``` :  La décomposition QR d’une matrice
- ```lstsq``` : La régression polynomiale au sens des moindres carrés (application de la décomposition QR)

## Les tests
On retrouve dans le fichier test_basic_op.c les tests unitaires des fonctions du programme en utilisant la bibliothèque CUnit :
- ```test_add_v_v``` : vérifie que l'addition de 2 vecteurs, élément par élément, est effectuée correctement.
- ```test_sub_v_v``` : vérifie que la soustraction de 2 vecteurs, élément par élément, est effectuée correctement.
- ```test_dot_prod```: vérifie que le produit scalaire entre deux vecteurs est correct
- ```test_norm``` : vérifie que la norme d’un vecteur est correctement calculée
- ```test_add_m_m``` : Vérifie que la somme de deux matrices est correcte e comparant chaque élément de la matrice donnée par la fonction et celle attendue.
- ```test_sub_m_m``` :  Vérifie, de la même manière, que la différence de deux matrices est correcte.
- ```test_mult_m_v``` : vérifie que la multiplication entre une matrice et un vecteur donne le résultat attendu
- ```mult_m_m``` : Teste la multiplication de matrices pour plusieurs tailles et valeurs différentes et vérifie que les résultats obtenus sont égaux aux résultats attendus.
- ```transp``` : vérifie les valeurs de la transposée de différentes matrices.
- ```back_sub``` : Teste la substitution arrière pour résoudre un système triangulaire supérieur Ux = b;

## Arborescence du projet

```
./
├── headers (contient les fichiers headers)
│   ├── file.h
│   ├── matrix.h
│   ├── vector.h
│   ├── portable_endian.h
├── help (contient les codes pour générer des vecteurs et matrices)
│   ├── generator_matrix.c
│   ├── generator_vector.c
├── src (contient les fichiers sources)
|   ├── file.c
|   ├── main.c
|   ├── matrix.c
|   ├── vector.c
├── tests (contient les codes des tests)
|   ├── tests_matrix.c
│   ├── test_fichier.c
│   ├── test_basic_op.c
│   ├── tests_io.c
├── Makefile
└── README.md
```