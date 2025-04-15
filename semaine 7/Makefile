all: test

# Compilation et exécution des tests
test:
	clang -o tests/real_manager tests/real_manager.c src/real_manager.c -lcunit
	./tests/real_manager

# Nettoyage du fichier exécutable
clean:
	rm -f tests/real_manager

# Utilisation de Valgrind pour vérifier les fuites mémoires
valgrind:
	clang -o src/leak -g src/leak.c
	valgrind --leak-check=full ./src/leak
	rm -f src/leak