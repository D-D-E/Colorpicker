#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include "encoder.h"
#include "encoder_driver.h"

static void test_encoder_init(void **state)
{
    EncoderInit();
}

static void test_encoder_default(void **state)
{
    assert_int_equal(0, Encoder_State()); //get eNone
}

static void test_encoder_button(void **state)
{
    SetButton(1);
    assert_int_equal(3, Encoder_State()); //get eButton
}

static void test_encoder_rotate_right(void **state)
{
    Rotate(0, 0);
    assert_int_equal(2, Encoder_State()); //get eRight
}

static void test_encoder_rotate_right_r(void **state)
{
    Rotate(1, 1);
    assert_int_equal(2, Encoder_State()); //get eRight
}

static void test_encoder_rotate_left(void **state)
{
    Rotate(1, 0);
    assert_int_equal(1, Encoder_State()); //get eLeft
}

static void test_encoder_rotate_left_r(void **state)
{
    Rotate(0, 1);
    assert_int_equal(1, Encoder_State()); //get eLeft
}

static void test_encoder_button_and_rotate(void **state)
{
    SetButton(1);
    Rotate(0, 1);
    assert_int_equal(3, Encoder_State());
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
            cmocka_unit_test(test_encoder_init)
           ,cmocka_unit_test(test_encoder_default)
           ,cmocka_unit_test(test_encoder_button)
           ,cmocka_unit_test(test_encoder_rotate_right)
           ,cmocka_unit_test(test_encoder_rotate_right_r)
           ,cmocka_unit_test(test_encoder_rotate_left)
           ,cmocka_unit_test(test_encoder_rotate_left_r)
           ,cmocka_unit_test(test_encoder_button_and_rotate)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
