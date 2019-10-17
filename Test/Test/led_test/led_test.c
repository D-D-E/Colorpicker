#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "cmocka.h"
#include "led.h"
#include "led_driver.h"

static void test_led_init(void **state)
{
    LedInit();
}

static void test_led_set_all(void **state)
{
    Led_Set(10, 100, 1000);
    assert_int_equal(10, Led_Get_Color(eRed));
    assert_int_equal(100, Led_Get_Color(eGreen));
    assert_int_equal(1000, Led_Get_Color(eBlue));
    Led_Refresh(4095);
    assert_int_equal(10, Get_CH1());
    assert_int_equal(100, Get_CH2());
    assert_int_equal(1000, Get_CH3());
}

static void test_led_set_red(void **state)
{
    Led_Set_Color(eRed, 20);
    assert_int_equal(20, Led_Get_Color(eRed));
    Led_Refresh(4095);
    assert_int_equal(20, Get_CH1());
}

static void test_led_set_green(void **state)
{
    Led_Set_Color(eGreen, 30);
    assert_int_equal(30, Led_Get_Color(eGreen));
    Led_Refresh(4095);
    assert_int_equal(30, Get_CH2());
}

static void test_led_set_blue(void **state)
{
    Led_Set_Color(eBlue, 40);
    assert_int_equal(40, Led_Get_Color(eBlue));
    Led_Refresh(4095);
    assert_int_equal(40, Get_CH3());
}

static void test_led_set_oversize(void **state)
{
    Led_Set(70000, 70000, 70000);
    assert_int_equal(4095, Led_Get_Color(eRed));
    assert_int_equal(4095, Led_Get_Color(eGreen));
    assert_int_equal(4095, Led_Get_Color(eBlue));
    Led_Refresh(4095);
    assert_int_equal(4095, Get_CH1());
    assert_int_equal(4095, Get_CH2());
    assert_int_equal(4095, Get_CH3());
}

static void test_led_set_rand(void **state)
{
    for(int i = 0; i < 10; i++)
    {
        uint16_t rand_value = rand();
        Led_Set(rand_value, rand_value, rand_value);

        if(rand_value > 4095)
        {
            assert_int_equal(4095, Led_Get_Color(eRed));
            assert_int_equal(4095, Led_Get_Color(eGreen));
            assert_int_equal(4095, Led_Get_Color(eBlue));
            Led_Refresh(4095);
            assert_int_equal(4095, Led_Get_Color(eRed));
            assert_int_equal(4095, Led_Get_Color(eGreen));
            assert_int_equal(4095, Led_Get_Color(eBlue));
        }
        else
        {
            assert_int_equal(rand_value, Led_Get_Color(eRed));
            assert_int_equal(rand_value, Led_Get_Color(eGreen));
            assert_int_equal(rand_value, Led_Get_Color(eBlue));
            Led_Refresh(4095);
            assert_int_equal(rand_value, Get_CH1());
            assert_int_equal(rand_value, Get_CH2());
            assert_int_equal(rand_value, Get_CH3());
        }
    }
}

static void test_led_set_default(void **state)
{
    Led_Set_Color(5, 30);
}


int main(void)
{
    const struct CMUnitTest tests[] =
    {
            cmocka_unit_test(test_led_init)
           ,cmocka_unit_test(test_led_set_all)
           ,cmocka_unit_test(test_led_set_red)
           ,cmocka_unit_test(test_led_set_green)
           ,cmocka_unit_test(test_led_set_blue)
           ,cmocka_unit_test(test_led_set_default)
           ,cmocka_unit_test(test_led_set_oversize)
           ,cmocka_unit_test(test_led_set_rand)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

