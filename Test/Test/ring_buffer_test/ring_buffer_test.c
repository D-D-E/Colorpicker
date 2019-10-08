#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include "ring_buffer.h"

static void test_ring_buffer_init(void **state)
{
    RingBuff_Init();
}

static void test_ring_buffer_push(void **state)
{
    for(int i = 0; i < 512; i++)
    {
        RingBuff_Push('c');
    }
}

static void test_ring_buffer_pop(void **state)
{
    assert_int_equal(RingBuff_Pop(), 'c');
}

static void test_ring_buffer_clear(void **state)
{
    RingBuff_Clear();
}

static void test_ring_buffer_is_empty(void **state)
{
    assert_int_equal(RingBuff_IsEmpty(), 1);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
            cmocka_unit_test(test_ring_buffer_init)
           ,cmocka_unit_test(test_ring_buffer_push)
           ,cmocka_unit_test(test_ring_buffer_pop)
           ,cmocka_unit_test(test_ring_buffer_clear)
           ,cmocka_unit_test(test_ring_buffer_is_empty)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
