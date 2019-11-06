#ifndef LED_LED_H_
#define LED_LED_H_
#include "stdint.h"

typedef enum {eRed, eGreen, eBlue} color;

void LedInit(void);

void Led_Set(uint16_t red, uint16_t green, uint16_t blue);
void Led_Set_Color(color color, uint16_t value);

uint16_t Led_Get_Color(color color);
uint16_t * Led_Get_Arr_Color(void);

void Led_Refresh(uint16_t max_value);

#endif /* LED_LED_H_ */
