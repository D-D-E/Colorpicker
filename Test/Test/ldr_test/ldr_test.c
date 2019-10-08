#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include "ldr.h"

static void test_ldr_init(void **state)
{
    LDRInit();
}

static void test_ldr_get(void **state)
{
    assert_in_range(LDR_Get(), 0, 65535);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_ldr_init)
       ,cmocka_unit_test(test_ldr_get)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

