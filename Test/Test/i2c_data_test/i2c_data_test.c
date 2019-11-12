#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include "i2c_data.h"
#include "i2c.h"
#include "led.h"

static void test_i2c_data_init(void **state)
{
    I2C_Init();
}

static void test_i2c_data_SaveToEEPROM(void **state)
{
    Led_Set(100, 100, 100);
    ColorToEEPROM();
    setLedI2C();
    assert_int_equal(Led_Get_Color(eRed), 100);
    assert_int_equal(Led_Get_Color(eGreen), 100);
    assert_int_equal(Led_Get_Color(eBlue), 100);
}

static void test_i2c_data_SaveToEEPROM_zero(void **state)
{
    Led_Set(0, 0, 0);
    ColorToEEPROM();
    setLedI2C();
    assert_int_equal(Led_Get_Color(eRed), 0);
    assert_int_equal(Led_Get_Color(eGreen), 0);
    assert_int_equal(Led_Get_Color(eBlue), 0);
}

static void test_i2c_data_SaveToEEPROM_nax(void **state)
{
    Led_Set(4095, 4095, 4095);
    ColorToEEPROM();
    setLedI2C();
    assert_int_equal(Led_Get_Color(eRed), 4095);
    assert_int_equal(Led_Get_Color(eGreen), 4095);
    assert_int_equal(Led_Get_Color(eBlue), 4095);
}


int main(void)
{
    const struct CMUnitTest tests[] =
    {
            cmocka_unit_test(test_i2c_data_init)
           ,cmocka_unit_test(test_i2c_data_SaveToEEPROM)
           ,cmocka_unit_test(test_i2c_data_SaveToEEPROM_zero)
           ,cmocka_unit_test(test_i2c_data_SaveToEEPROM_nax)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
