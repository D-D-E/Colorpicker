#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include "ldr.h"
#include "ldr_driver.h"

static void test_ldr_get_const(void **state)
{
    LDRInit();
    SetADC1(100);
    assert_int_equal(LDR_Get(), 3995);
}

static void test_ldr_get_rand_small(void **state)
{
    LDRInit();
    SetADC1_random(0, 100);
    assert_in_range(LDR_Get(), 3995, 4095);
}

static void test_ldr_get_rand_bias(void **state)
{
    LDRInit();
    SetADC1_random(500, 700);
    assert_in_range(LDR_Get(), 3295, 3595);
}

static void test_ldr_get_rand_small_bias(void **state)
{
    LDRInit();
    SetADC1_random(400, 405);
    assert_in_range(LDR_Get(), 3690, 3695);
}

static void test_ldr_get_rand_large(void **state)
{
    LDRInit();
    SetADC1_random(0, 4095);
    assert_in_range(LDR_Get(), 0, 4095);
}

static void test_ldr_get_rand_large_bias(void **state)
{
    LDRInit();
    SetADC1_random(3995, 4095);
    assert_in_range(LDR_Get(), 0, 100);
}

static void test_ldr_get_overflow(void **state)
{
    LDRInit();
    SetADC1(60000);
    assert_int_equal(LDR_Get(), 0);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_ldr_get_const)
       ,cmocka_unit_test(test_ldr_get_rand_small)
       ,cmocka_unit_test(test_ldr_get_rand_bias)
       ,cmocka_unit_test(test_ldr_get_rand_small_bias)
       ,cmocka_unit_test(test_ldr_get_rand_large)
       ,cmocka_unit_test(test_ldr_get_rand_large_bias)
       ,cmocka_unit_test(test_ldr_get_overflow)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

