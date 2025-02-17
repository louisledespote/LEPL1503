all: test

# Compilation et exécution des tests
test:
	clang -o tests/my_lib tests/my_lib.c -Wall -lcunit
	./tests/my_lib

# Nettoyage du fichier exécutable
clean:
	rm -f tests/my_lib
