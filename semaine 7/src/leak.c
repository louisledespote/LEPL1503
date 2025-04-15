#include <stdio.h>
#include <stdlib.h>

struct Fraction {
    int num;
    int den;
};

struct Fraction* create_fraction(int num, int den) {
    struct Fraction* f = malloc(sizeof(struct Fraction));
    f->num = num;
    f->den = den;
    return f;
}

int fraction_mult(struct Fraction* f1, struct Fraction* f2, struct Fraction* result) {
    result->num = f1->num * f2->num;
    result->den = f1->den * f2->den;
    return 0;
}

void fraction_print(struct Fraction* f) {
    printf("%d/%d\n", f->num, f->den);
}

int main() {

    struct Fraction* f1 = create_fraction(1, 2);
    struct Fraction* f2 = create_fraction(1, 3);

    struct Fraction* result = malloc(sizeof(struct Fraction));

    fraction_mult(f1, f2, result);

    fraction_print(result);

    
    
    return 0;
}
