#include <CUnit/Basic.h>
#include <stdlib.h>
#include "../src/my_lib.c"

// Test pour my_strlen
void test_my_strlen(void) {
    CU_ASSERT_EQUAL(my_strlen("hello"), 5);
    CU_ASSERT_EQUAL(my_strlen(""), 0);
    CU_ASSERT_EQUAL(my_strlen("a"), 1);
    // TODO : ajouter des tests
}

// Test pour my_get
void test_my_get(void) {
    CU_ASSERT_EQUAL(my_get("hello", 1), 'e');
    CU_ASSERT_EQUAL(my_get("hello", 0), 'h');
    CU_ASSERT_EQUAL(my_get("hello", 4), 'o');
    CU_ASSERT_EQUAL(my_get("hello", 5), '\0');
    CU_ASSERT_EQUAL(my_get("hello", -1), '\0');
    // TODO : ajouter des tests
}

// Test pour my_count
void test_my_count(void) {
    CU_ASSERT_EQUAL(my_count("hello", 'l'), 2);
    CU_ASSERT_EQUAL(my_count("hello", 'o'), 1);
    CU_ASSERT_EQUAL(my_count("hello", 'x'), 0);
    // TODO : ajouter des tests
}

// Test pour my_strcmp
void test_my_strcmp(void) {
    CU_ASSERT(my_strcmp("hello", "hello") == 0);
    CU_ASSERT(my_strcmp("abc", "abd") < 0);
    CU_ASSERT(my_strcmp("abc", "abb") > 0);
    // TODO : ajouter des tests
}

// Test pour my_strbrk
void test_my_strpbrk(void) {
    CU_ASSERT_PTR_NOT_NULL(my_strpbrk("hello", "ol"));
    if (my_strpbrk("hello", "ol") != NULL) { // Cette condition évite un segmentation fault si le pointeur est NULL
        CU_ASSERT_STRING_EQUAL(my_strpbrk("hello", "ol"), "llo");
    }
    CU_ASSERT_PTR_NOT_NULL(my_strpbrk("hello", "e"));
    if (my_strpbrk("hello", "e") != NULL) {
        CU_ASSERT_STRING_EQUAL(my_strpbrk("hello", "e"), "ello");
    }
    CU_ASSERT_PTR_NOT_NULL(my_strpbrk("coucou", "u"));
    if (my_strpbrk("coucou", "u") != NULL) {
        CU_ASSERT_STRING_EQUAL(my_strpbrk("coucou", "u"), "ucou");
    }
    CU_ASSERT_PTR_NULL(my_strpbrk("hello", "x"));
    // TODO : ajouter des tests
}

// Test pour my_strdup
void test_my_strdup(void) {
    char *dup = my_strdup("hello");
    CU_ASSERT_PTR_NOT_NULL(dup);
    if (dup != NULL) {
        CU_ASSERT_STRING_EQUAL(dup, "hello");
    }
    free(dup);

    dup = my_strdup("");
    CU_ASSERT_PTR_NOT_NULL(dup);
    if (dup != NULL) {  // Cette condition évite un segmentation fault si le pointeur est NULL
        CU_ASSERT_STRING_EQUAL(dup, "");
    }

    // libère la mémoire allouée par my_strdup avec malloc
    // si on ne libère pas la mémoire, chaque appel à my_strdup alloue de la mémoire et elle finit par saturer
    free(dup);

    // TODO : ajouter des tests
}

// Test pour my_append
void test_my_append(void) {
    char *app = my_append("hello", " world");
    CU_ASSERT_PTR_NOT_NULL(app);
    if (app != NULL) { // Cette condition évite un segmentation fault si le pointeur est NULL
        CU_ASSERT_STRING_EQUAL(app, "hello world");
    }
    free(app);

    app = my_append("", "world");
    CU_ASSERT_PTR_NOT_NULL(app);
    if (app != NULL) {
        CU_ASSERT_STRING_EQUAL(app, "world");
    }
    free(app);

    app = my_append("hello", "");
    CU_ASSERT_PTR_NOT_NULL(app);
    if (app != NULL) {
        CU_ASSERT_STRING_EQUAL(app, "hello");
    }
    free(app);

    // TODO : ajouter des tests
}

void test_my_factorial(void) {
    CU_ASSERT_EQUAL(my_factorial(2),2);
    CU_ASSERT_EQUAL(my_factorial(2),2);
    CU_ASSERT_EQUAL(my_factorial(3),6);
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite_strlen = CU_add_suite("Suite my_strlen", NULL, NULL);
    CU_add_test(suite_strlen, "test_my_strlen", test_my_strlen);

    CU_pSuite suite_my_get = CU_add_suite("Suite my_get", NULL, NULL);
    CU_add_test(suite_my_get, "test_my_get", test_my_get);

    CU_pSuite suite_my_count = CU_add_suite("Suite my_count", NULL, NULL);
    CU_add_test(suite_my_count, "test_my_count", test_my_count);

    CU_pSuite suite_my_strcmp = CU_add_suite("Suite my_strcmp", NULL, NULL);
    CU_add_test(suite_my_strcmp, "test_my_strcmp", test_my_strcmp);

    CU_pSuite suite_my_strpbrk = CU_add_suite("Suite my_strpbrk", NULL, NULL);
    CU_add_test(suite_my_strpbrk, "test_my_strpbrk", test_my_strpbrk);

    CU_pSuite suite_my_strdup = CU_add_suite("Suite my_strdup", NULL, NULL);
    CU_add_test(suite_my_strdup, "test_my_strdup", test_my_strdup);

     CU_pSuite suite_my_append = CU_add_suite("Suite my_append", NULL, NULL);
    CU_add_test(suite_my_append, "test_my_append", test_my_append);

    CU_pSuite suite_my_factorial = CU_add_suite("Suite my_factorial", NULL, NULL);
    CU_add_test(suite_my_factorial, "test_my_factorial", test_my_factorial);

    // TODO : ajouter les tests pour my_factorial
    

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
