#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../src/real_manager.h"

void test_RealManager(void) {

    // TODO : modifier le Python et les tests

    CU_ASSERT_DOUBLE_EQUAL(getAverage(), 5.3, 0.0001);

    CU_ASSERT_EQUAL(changeReal(1, 4.5), 0);
    CU_ASSERT_EQUAL(changeReal(2, 2.9), 0);

    CU_ASSERT_DOUBLE_EQUAL(getAverage(), 3.3, 0.0001);

    // reset
    CU_ASSERT_EQUAL(changeReal(1, 5.5), 0);
    CU_ASSERT_EQUAL(changeReal(2, 7.9 ), 0);

}

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Real manager", NULL, NULL);
    CU_add_test(pSuite, "test_real_manager", test_RealManager);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    int failed_tests = CU_get_number_of_failures();
    CU_cleanup_registry();
    return (failed_tests > 0) ? 1 : 0;
}
