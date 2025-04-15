# Semaine 6

Le TP de cette semaine sert d'introduction à l'utilisation des threads dans le but d'accélérer l'exécution de votre code. Les parties du syllabus à lire avant le TP sont:

- [Utilisation de plusieurs threads](https://lepl1503.info.ucl.ac.be/syllabus/theorie/Threads/threads.html)
- [Communication entre threads](https://lepl1503.info.ucl.ac.be/syllabus/theorie/Threads/threads2.html)
- [Coordination entre threads](https://lepl1503.info.ucl.ac.be/syllabus/theorie/Threads/threads2.html#coordination-entre-threads)
- [Les sémaphores](https://lepl1503.info.ucl.ac.be/syllabus/theorie/Threads/coordination.html)


Cette semaine, nous vous proposons d'utiliser la puissance de la programmation multithreads afin de craquer un mot de passe par [la force brute](https://fr.wikipedia.org/wiki/Attaque_par_force_brute).

## Info utile

Chaque fichier contient une fonction `login`, prenant en argument un nom d'utilisateur et un mot de passe. Cette fonction simule l'appel à un serveur distant afin de vérifier si l'accès est autorisé avec ce nom d'utilisateur et mot de passe.

Nous supposerons que les utilisateurs de ce service n'ont pas pris beaucoup de précautions et ont utilisé un mot de passe comportant uniquement des lettres (majuscules et minuscules) ainsi que des chiffres. La longueur du mot de passe est de exactement 4 caractères.

Notez que dans un cas réel, envoyer de manière intensive des requêtes à un serveur peut ressembler à une [attaque DDOS](https://fr.wikipedia.org/wiki/Attaque_par_déni_de_service), rendant le service indisponible.

## TODO

1. Commencez par ouvrir le fichier `testBruteForceSimple.c` dans le dossier `tests`. Prenez le temps de comprendre comment fonctionne ce code et complétez le TODO en ajoutant deux tests à la suite de tests : le mot de passe d'Antoine est `g2dP` et celui de Melanie est `a10d`.

2. Ouvrez le fichier `bruteForceSimple.c` dans le dossier `src`. Complétez la fonction `bruteForceSimple`. Indice : 4 boucles for devraient facilement faire l'affaire (en mono thread pour l'instant).

3. Ouvrez le fichier `Makefile` et comprenez son fonctionnement. Lancez la commande `make simple` pour compiler le fichier de test et lancer les tests. Vérifiez que les trois tests unitaires réussissent. Ces tests peuvent prendre du temps (+-1 minute).

4. Nous allons maintenant utiliser les threads et les mutex pour accélérer l'exécution du programme. Ouvrez le fichier `bruteForceMulti.c` dans le dossier `src`. Comparez la fonction `login` avec celle qui se trouve dans `bruteForceSimple.c`. Un changement majeur est l'utilisation de `crypt_r` à la place de `crypt`. Cette fonction fait exactement la même chose mais permet d'être exécutée en parallèle par plusieurs threads : [thread-safe](https://fr.wikipedia.org/wiki/Thread_safety). Comprenez d'abord le fonctionnement de la fonction `bruteForceMulti`. Ensuite, complétez la fonction `bruteForceThread` en vous inspirant de votre code dans la fonction `bruteForceSimple`. Nous avons commencé le travail pour vous. N'oubliez pas d'utiliser le mutex lorsque vous écrivez le mot de passe dans `found_password`. La fonction renvoie `NULL` si l'appel à `malloc` échoue.

5. Comme précédemment, ajoutez les deux tests au fichier `testBruteForceMulti.c` dans le dossier `tests`.

6. Complétez le `Makefile` afin de compiler, lancer les tests et nettoyer les exécutables lors de l'exécution de la commande `make multi`. Inspirez-vous de `make simple`. N'oubliez pas que ce programme utilise la librairie `pthread` en plus des librairies `CUnit` et `crypt`.

7. Lorsque vous comparez le temps écoulé imprimé par la commande `make multi` à celui de la commande `make simple`, il peut sembler que l'exécution monothreadée est plus rapide que l'exécution multithreadée. Cependant, le temps affiché ne correspond pas au temps réel écoulé, mais à la somme des temps pris par chaque thread. Pour obtenir une comparaison basée sur le temps réel écoulé, lancez les commandes `time make multi` et `time make simple`. 

8. Nous aimerions maintenant pouvoir brute-forcer des codes de longueur allant de 1 caractère à 4 caractères. Ouvrez le fichier `bruteForceAdvance.c` et comprenez le fonctionnement de la fonction récursive `bruteForceHelper`. Complétez ensuite la fonction `bruteForceAdvance` (mono thread). Le mot de passe peut maintenant avoir une longueur de 1 caractère à 4 caractères. La fonction renvoie `NULL` si l'appel à `malloc` échoue.

9. Modifiez le `Makefile` pour lancer le code avec `make advance`. Vérifiez que les tests réussissent.

10. BONUS : Transformez ce code en une version multithreadée et vérifiez son exécution.

## Outils pour le projet (2)

Cette semaine, nous allons introduire des outils utiles pour mesurer le temps d'exécution de vos fonctions et le nombre d'exécutions de celles-ci. Ensuite, nous utiliserons Helgrind pour mettre en lumière les problèmes de concurrence avec les threads. Vous trouverez plus d'informations sur Helgrind et gprof dans la partie outil du syllabus:

- [Helgrind](https://lepl1503.info.ucl.ac.be/syllabus/outils/valgrind.html#detecter-les-deadlocks-avec-valgrind)
- [gprof](https://lepl1503.info.ucl.ac.be/syllabus/outils/gprof.html)
- [llvm-profdata](https://llvm.org/docs/CommandGuide/llvm-profdata.html#profdata-merge)
- [llvm-cov](https://llvm.org/docs/CommandGuide/llvm-cov.html#llvm-cov-show)

11. Installez `gprof` avec la commande `sudo apt install binutils`. Installez les outils `llvm-profdata` et `llvm-cov` avec la commande `sudo apt install llvm`.

12. Copiez et collez vos deux fonctions CORRECTES, `bruteForceSimple` et `bruteForceThread`, dans le fichier `bruteForceTime.c`.

13. Nous allons utiliser l'outil `gprof` pour mesurer le temps d'exécution et comparer vos deux implémentations. Exécutez la commande `make time`. Un fichier `rapport_time.txt` devrait être créé. Analysez-le pour comparer les temps d'exécution des différentes fonctions. Vous pouvez vous aider de ce [site](https://ftp.gnu.org/old-gnu/Manuals/gprof-2.9.1/html_chapter/gprof_5.html) pour comprendre le fichier `rapport_time.txt`.

14. Nous allons utiliser les outils `llvm-profdata` et `llvm-cov` pour analyser la couverture des fonctions. Exécutez `make coverage`, un fichier `rapport_gcov.txt` devrait être créé. Analysez-le pour comprendre la couverture de code.

15. Finalement, le code `concurrency.c` initialise simplement 5 threads qui vont augmenter un compteur 10000 fois chacun. Lancez la commande `make concurrency` pour compiler et lancer le code. Le compteur est-il bien 50000 ? Lancez plusieurs fois cette commande et vérifiez le résultat. Lancez maintenant `make helgrind` pour analyser la concurrence des threads. Analysez la sortie et corrigez le code en ajoutant des mutex. Votre code est-il correct maintenant ?
