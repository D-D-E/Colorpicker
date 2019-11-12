#ifndef DISPLAY_DISPLAY_H_
#define DISPLAY_DISPLAY_H_
#include "stdint.h"
#include "stdbool.h"

void Display_Init(void);

void Display_ON(void);
void Display_OFF(void);

void Display_SetPage(uint8_t addr);
void Display_SetColumn(uint8_t data);
void Display_Contrast(uint8_t data);
void Display_ReadModifyWrite(void);
void Display_ReadModifyWrite_End(void);
void Display_Write(uint8_t data);
void Display_Inverse(void);
void Display_Clean();
void Display_Test(void);
void Display_PrintSymbol(uint8_t sym, uint8_t page, bool nl);
void display();

#endif /* DISPLAY_DISPLAY_H_ */
