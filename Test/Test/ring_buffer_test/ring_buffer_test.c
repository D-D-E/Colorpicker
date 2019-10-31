#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include "cmocka.h"
#include "ring_buffer.h"

static void test_ring_buffer_push_const(void **state)
{
    RingBuff_Init();

    for(int i = 0; i < 512; i++)
    {
        RingBuff_Push('c');
    }

    for(int i = 0; i < 512; i++)
    {
        assert_int_equal(RingBuff_Pop(), 'c');
    }
    assert_int_equal(RingBuff_IsEmpty(), 1);
}

static void test_ring_buffer_push_overwrite(void **state)
{
    RingBuff_Init();

    for(int i = 0; i < 1024; i++)
    {
        if(i < 512)
        {
            RingBuff_Push('c');
        }
        else
        {
            RingBuff_Push('v');
        }
    }

    for(int i = 0; i < 512; i++)
    {
        assert_int_equal(RingBuff_Pop(), 'v');
    }

    assert_int_equal(RingBuff_IsEmpty(), 1);
}

static void test_ring_buffer_push_rand(void **state)
{
    RingBuff_Init();
    char temp[512];

    for(int i = 0; i < 512; i++)
    {
        temp[i] = rand() % 255 + 32;
        RingBuff_Push(temp[i]);
    }

    for(int i = 0; i < 512; i++)
    {
        assert_int_equal(RingBuff_Pop(), temp[i]);
    }
    assert_int_equal(RingBuff_IsEmpty(), 1);
}

static void test_ring_buffer_clear(void **state)
{
    RingBuff_Clear();
    assert_int_equal(RingBuff_IsEmpty(), 1);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
            cmocka_unit_test(test_ring_buffer_push_const)
            ,cmocka_unit_test(test_ring_buffer_push_overwrite)
           ,cmocka_unit_test(test_ring_buffer_push_rand)
           ,cmocka_unit_test(test_ring_buffer_clear)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
