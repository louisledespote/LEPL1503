#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../src/bruteForceAdvance.c"

void testsBruteForceAdvance() {
    CU_ASSERT_PTR_NOT_NULL(bruteForceAdvance("Corentin"));
    if (bruteForceAdvance("Corentin") != NULL) { // Cette condition évite un segmentation fault si le pointeur est NULL
        CU_ASSERT_STRING_EQUAL(bruteForceAdvance("Corentin"), "ad7");
    }
    CU_ASSERT_PTR_NOT_NULL(bruteForceAdvance("Antoine"));
    if (bruteForceAdvance("Antoine") != NULL) {
        CU_ASSERT_STRING_EQUAL(bruteForceAdvance("Antoine"), "dIn2");
    }
    CU_ASSERT_PTR_NOT_NULL(bruteForceAdvance("Melanie"));
    if (bruteForceAdvance("Melanie") != NULL) {
        CU_ASSERT_STRING_EQUAL(bruteForceAdvance("Melanie"), "I3");
    }
}

int main() {
    // Initialisation de CUnit
    if (CU_initialize_registry() != CUE_SUCCESS) {
        fprintf(stderr, "Erreur d'initialisation de CUnit.\n");
        return CU_get_error();
    }

    // Création d'une suite de tests
    CU_pSuite pSuite = CU_add_suite("Suite de tests pour bruteForceAdvance", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        fprintf(stderr, "Erreur lors de la création de la suite de tests.\n");
        return CU_get_error();
    }

    // Ajout des tests à la suite
    if (CU_add_test(pSuite, "testsBruteForceAdvance", testsBruteForceAdvance) == NULL) {
        CU_cleanup_registry();
        fprintf(stderr, "Erreur lors de l'ajout du test.\n");
        return CU_get_error();
    }

    // Exécution des tests
    CU_basic_run_tests();

    // Nettoyage de CUnit
    int failed_tests = CU_get_number_of_failures();
    CU_cleanup_registry();
    return (failed_tests > 0) ? 1 : 0;
}
