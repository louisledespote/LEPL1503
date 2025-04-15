#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../src/bruteForceSimple.c"

void testsBruteForceSimple() {
    char *pwd_corentin = bruteForceSimple("Corentin");
    CU_ASSERT_PTR_NOT_NULL(pwd_corentin);
    if (pwd_corentin != NULL) {
        CU_ASSERT_STRING_EQUAL(pwd_corentin, "Adi3");
        free(pwd_corentin);
    }

    char *pwd_antoine = bruteForceSimple("Antoine");
    CU_ASSERT_PTR_NOT_NULL(pwd_antoine);
    if (pwd_antoine != NULL) {
        CU_ASSERT_STRING_EQUAL(pwd_antoine, "g2dP");
        free(pwd_antoine);
    }

    char *pwd_melanie = bruteForceSimple("Melanie");
    CU_ASSERT_PTR_NOT_NULL(pwd_melanie);
    if (pwd_melanie != NULL) {
        CU_ASSERT_STRING_EQUAL(pwd_melanie, "a10d");
        free(pwd_melanie);
    }
}
int main() {
    // Initialisation de CUnit
    if (CU_initialize_registry() != CUE_SUCCESS) {
        fprintf(stderr, "Erreur d'initialisation de CUnit.\n");
        return CU_get_error();
    }

    // Création d'une suite de tests
    CU_pSuite pSuite = CU_add_suite("Suite de tests pour bruteForceSimple", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        fprintf(stderr, "Erreur lors de la création de la suite de tests.\n");
        return CU_get_error();
    }

    // Ajout des tests à la suite
    if (CU_add_test(pSuite, "testsBruteForceSimple", testsBruteForceSimple) == NULL) {
        CU_cleanup_registry();
        fprintf(stderr, "Erreur lors de l'ajout du test.\n");
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    // Exécution des tests
    CU_basic_run_tests();

    // Nettoyage de CUnit
    int failed_tests = CU_get_number_of_failures();
    CU_cleanup_registry();
    return (failed_tests > 0) ? 1 : 0;
}

