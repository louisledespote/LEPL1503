# Variables
CC = clang
CFLAGS = -Wall

# Règle pour tester le programme bruteForceSimple (compilation, exécution et nettoyage)
simple:
	$(CC) $(CFLAGS) tests/bruteForceSimple.c -o tests/bruteForceSimple -lcunit -lcrypt
	./tests/bruteForceSimple
	rm -f tests/bruteForceSimple

multi:
	$(CC) $(CFLAGS) tests/bruteForceMulti.c -o tests/bruteForceMulti -lcunit -lcrypt
	./tests/bruteForceMulti
	rm -f tests/bruteForceMulti


# Règle pour tester le programme bruteForceAdvance
advance:
	$(CC) $(CFLAGS) tests/bruteForceAdvance.c -o tests/bruteForceAdvance -lcunit -lcrypt
	./tests/bruteForceAdvance
	rm -f tests/bruteForceAdvance




# Règle pour mesurer le temps avec gprof
time:
	$(CC) $(CFLAGS) -pg src/bruteForceTime.c -o src/bruteForceTime -lcrypt -lpthread
	./src/bruteForceTime
	gprof src/bruteForceTime gmon.out > rapport_time.txt
	rm -f src/bruteForceTime gmon.out

# Règle pour mesurer la couverture de code avec gcov
coverage:
	$(CC) $(CFLAGS) -fprofile-instr-generate -fcoverage-mapping -g src/bruteForceTime.c -o src/bruteForceTime -lcrypt -lpthread
	./src/bruteForceTime
	llvm-profdata merge -o unittest.profdata default.profraw
	llvm-cov show src/bruteForceTime -instr-profile=unittest.profdata src/bruteForceTime.c --format text > rapport_gcov.txt
	rm -f src/bruteForceTime *.profraw *.profdata

# Compiler et lancer concurrency
concurrency:
	$(CC) $(CFLAGS) src/concurrency.c -o src/concurrency -lpthread
	./src/concurrency
	rm -f src/concurrency

# Helgrind sur le programme concurrency
helgrind:
	$(CC) $(CFLAGS) -g src/concurrency.c -o src/concurrency -lpthread
	valgrind --tool=helgrind ./src/concurrency
	rm -f src/concurrency

