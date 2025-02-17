int main() {
    CU_initialize_registry();

    // Création de la suite de tests
    CU_pSuite pSuite = CU_add_suite("Suite de tests pour mediane()", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ajout des tests à la suite
    if (NULL == CU_add_test(pSuite, "Test de la fonction mediane()", test_mediane)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Test avec des nombres négatifs", test_mediane_negative)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Test avec des nombres égaux", test_mediane_equals)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Test avec des nombres impairs", test_mediane_odd_numbers)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "Test avec des entrées non triées", test_mediane_unsorted)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Exécution des tests
    CU_basic_run_tests();
    
    // Nettoyage
    CU_cleanup_registry();
    return 0;
}

