#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include "led.h"

static void test_led_init(void **state)
{
    LedInit();
}

static void test_led_set_all(void **state)
{
    Led_Set(100, 100, 100);
}

static void test_led_set_red(void **state)
{
    Led_Set_Color(eRed, 10);
}

static void test_led_set_green(void **state)
{
    Led_Set_Color(eGreen, 20);
}

static void test_led_set_blue(void **state)
{
    Led_Set_Color(eBlue, 30);
}

static void test_led_set_default(void **state)
{
    Led_Set_Color(5, 30);
}

static void test_led_get_red(void **state)
{
    assert_int_equal(10, Led_Get_Color(eRed));
}

static void test_led_get_green(void **state)
{
    assert_int_equal(20, Led_Get_Color(eGreen));
}

static void test_led_get_blue(void **state)
{
    assert_int_equal(30, Led_Get_Color(eBlue));
}

static void test_led_get_default(void **state)
{
    assert_int_equal(0, Led_Get_Color(5));
}

static void test_led_refresh(void **state)
{
    Led_Refresh(100);
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
           ,cmocka_unit_test(test_led_get_red)
           ,cmocka_unit_test(test_led_get_green)
           ,cmocka_unit_test(test_led_get_blue)
           ,cmocka_unit_test(test_led_get_default)
           ,cmocka_unit_test(test_led_refresh)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

