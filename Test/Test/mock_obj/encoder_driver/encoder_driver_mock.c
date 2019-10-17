#include "../../../Test/mock_obj/encoder_driver/encoder_driver.h"

static bool button_status = false, rotate_status = false, rotate_pin_A, rotate_pin_B;

void GPIO_Init()
{

}

bool GetButton(void)
{
    return button_status;
}

void ClearButton()
{
    button_status = false;
}

bool GetRotateStatus(void)
{
    return rotate_status;
}

void ClearRotateStatus()
{
    rotate_status = false;
}

bool GetRotatePinB()
{
    return rotate_pin_A;
}

bool GetRotatePinA()
{
    return rotate_pin_B;
}

uint8_t GPIO_Read_Pin(uint8_t mask)
{
    return 0;
}

void EXTI1_IRQHandler(void){}
void EXTI15_10_IRQHandler(void){}



void SetButton(bool state)
{
    button_status = state;
}

void Rotate(bool pinA, bool pinB)
{
    rotate_status = true;
    rotate_pin_A = pinA;
    rotate_pin_B = pinB;
}
