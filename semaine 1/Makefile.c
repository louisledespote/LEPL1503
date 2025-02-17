all: main

main: src/main.c
	clang -o src/main src/main.c

run: main
	./src/main

clean:
	rm -f src/main

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Hello World\n");
    return 0;
}
