all: test

# Compilation et exécution des tests
test:
	clang -o tests/history tests/history.c -Wall -lcunit
	./tests/history

# Nettoyage du fichier exécutable
clean:
	rm -f tests/history
