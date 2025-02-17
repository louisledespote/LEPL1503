#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../src/history.c"

void test_history(void) {
    struct history *h = history_new();
    CU_ASSERT_PTR_NOT_NULL_FATAL(h);
    CU_ASSERT_PTR_NULL(h->first);
    CU_ASSERT_PTR_NULL(h->current);
    
    // ajouter une page
    history_add(h, "http://example.com");
    CU_ASSERT_PTR_NOT_NULL(h->first);
    CU_ASSERT_PTR_NOT_NULL(h->current);
    CU_ASSERT_STRING_EQUAL(h->first->url, "http://example.com");
    CU_ASSERT_PTR_NULL(h->first->next);
    CU_ASSERT_PTR_NULL(h->first->prev);
    CU_ASSERT_PTR_EQUAL(h->first, h->current);

    // ajouter une autre page
    history_add(h, "http://example.com/1");
    CU_ASSERT_PTR_NOT_NULL(h->first);
    CU_ASSERT_PTR_NOT_NULL(h->current);
    CU_ASSERT_STRING_EQUAL(h->first->url, "http://example.com");
    CU_ASSERT_STRING_EQUAL(h->first->next->url, "http://example.com/1");
    CU_ASSERT_PTR_NULL(h->first->prev);
    CU_ASSERT_PTR_EQUAL(h->first, h->current->prev);
    CU_ASSERT_PTR_EQUAL(h->first->next, h->current);
    CU_ASSERT_PTR_NULL(h->current->next);

    // go forward doit retourner 0 car il n'y a pas de page suivante
    CU_ASSERT_EQUAL(go_forward(h), 0);

    // go back doit retourner 1 car il y a une page précédente
    CU_ASSERT_EQUAL(go_back(h), 1);
    CU_ASSERT_PTR_EQUAL(h->first, h->current);

    // go back doit retourner 0 car il n'y a pas de page précédente
    CU_ASSERT_EQUAL(go_back(h), 0);
    CU_ASSERT_PTR_EQUAL(h->first, h->current);
    
    // ajoute une page après avoir fait un go back
    history_add(h, "http://example.com/2");
    CU_ASSERT_PTR_NOT_NULL(h->first);
    CU_ASSERT_PTR_NOT_NULL(h->current); 
    CU_ASSERT_STRING_EQUAL(h->first->url, "http://example.com");
    CU_ASSERT_STRING_EQUAL(h->first->next->url, "http://example.com/2");
    CU_ASSERT_PTR_EQUAL(h->first, h->current->prev);
    CU_ASSERT_PTR_EQUAL(h->first->next, h->current);
    CU_ASSERT_PTR_NULL(h->current->next);

    // go back doit retourner 1 car il y a une page précédente
    CU_ASSERT_EQUAL(go_back(h), 1);

    // go forward doit retourner 1 car il y a une page suivante
    CU_ASSERT_EQUAL(go_forward(h), 1);

    // vérifie que l'on revient bien à example.com/2
    CU_ASSERT_STRING_EQUAL(h->current->url, "http://example.com/2");

    // ajoute une page
    history_add(h, "http://example.com/3");
    CU_ASSERT_PTR_EQUAL(h->first->next->next, h->current);
    CU_ASSERT_STRING_EQUAL(h->current->url, "http://example.com/3");

    // revient à exemple.com
    CU_ASSERT_EQUAL(go_back(h), 1);
    CU_ASSERT_EQUAL(go_back(h), 1);

    // vérifie que l'on revient bien à example.com
    CU_ASSERT_STRING_EQUAL(h->current->url, "http://example.com");

    // libère la mémoire
    history_free(h);
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Suite", NULL, NULL);
    CU_add_test(suite, "test_history", test_history);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    int failed_tests = CU_get_number_of_failures();
    CU_cleanup_registry();

    return (failed_tests > 0) ? 1 : 0; // Return non-zero if tests fail
}
