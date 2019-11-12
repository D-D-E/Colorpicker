#include "display.h"
#include "delay.h"
#include "spi.h"
#include "led.h"
#include "ESP8266.h"

uint8_t table[17][7] = //symbol table
{
		{0x00, 0x7E, 0x81, 0x81, 0x81, 0x7E, 0x00}, // 0
		{0x00, 0x84, 0x82, 0xFF, 0x80, 0x80, 0x80}, // 1
		{0x00, 0xC6, 0xA1, 0x91, 0x89, 0x86, 0x80}, // 2
		{0x00, 0x42, 0x81, 0x89, 0x89, 0x76, 0x00}, // 3
		{0x00, 0x30, 0x2C, 0x22, 0xFF, 0x20, 0x00}, // 4
		{0x00, 0x8F, 0x89, 0x89, 0x89, 0x71, 0x00}, // 5
		{0x00, 0x7E, 0x89, 0x89, 0x89, 0x70, 0x00}, // 6
		{0x00, 0x01, 0xC1, 0x31, 0x0D, 0x03, 0x00}, // 7
		{0x00, 0x76, 0x89, 0x89, 0x89, 0x76, 0x00}, // 8
		{0x00, 0x0E, 0x91, 0x91, 0x91, 0x7E, 0x00}, // 9
		{0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00}, // .
		{0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00}, // :
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // sp
		{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // ff
		{0xFF, 0xFF, 0x31, 0x71, 0xD1, 0x8E, 0x00}, // R
		{0x7E, 0x7E, 0x81, 0xB1, 0x91, 0x62, 0x00}, // G
		{0xFF, 0xFF, 0x89, 0x89, 0x89, 0x76, 0x00}  // B
};

typedef enum {eZero, eOne, eTwo, eThree, eFour, eFive, eSeven, eEight, eNine, eTen, ePoint, eDPoint, eSpace, eFill, eR, eG, eB}symbol;

void Display_Init(void)
{
	MX_SPI1_Init();

	Reset();
	delay(100);

	ClearDC();
	SPI1_SendByte(0xAE);

	SPI1_SendByte(0xA8); //multiplex ratio
	SPI1_SendByte(0x3F);

	SPI1_SendByte(0xD3); //offset
	SPI1_SendByte(0x00);

	SPI1_SendByte(0x40); //start line

	SPI1_SendByte(0xA1); //segment re-map

	SPI1_SendByte(0xC8); //scan direction

	SPI1_SendByte(0xDA); //COM pins
	SPI1_SendByte(0x12);

	SPI1_SendByte(0xD5); //clock div
	SPI1_SendByte(0x30);

	SPI1_SendByte(0xA4);

	SPI1_SendByte(0x8D); //charge bump
	SPI1_SendByte(0x14); //VCC gen by DC/DC

	SPI1_SendByte(0xD9); //pre-charged period
	SPI1_SendByte(0xF1);

	SPI1_SendByte(0xB0); //start page

	SPI1_SendByte(0xDB); //VCOM level
	SPI1_SendByte(0x40); //20

	SPI1_SendByte(0x20); //page mode
	SPI1_SendByte(0x22);

	SPI1_SendByte(0x2E); //off scroll
}

void Display_ON(void)
{
	SPI1_SendByte(0xAF);
	Display_Contrast(0xFF);
}

void Display_OFF(void)
{
	ClearDC();
	SPI1_SendByte(0xAE);
}

void Display_SetPage(uint8_t addr)
{
	ClearDC();
	SPI1_SendByte(0xB0 + addr);
}

void Display_Write(uint8_t data)
{
	SetDC();
	SPI1_SendByte(data);
}

void Display_SetColumn(uint8_t data)
{
	ClearDC();
	SPI1_SendByte(0x00 + data);
	SPI1_SendByte(0x10 + (data >> 4));
}

void Display_Contrast(uint8_t data)
{
	ClearDC();
	SPI1_SendByte(0x81);
	SPI1_SendByte(data);
}

void Display_ReadModifyWrite(void) //dont use
{
	ClearDC();
	SPI1_SendByte(0b11100000);
}

void Display_ReadModifyWrite_End(void) //dont use
{
	ClearDC();
	SPI1_SendByte(0b11101110);
}

void Display_Inverse(void)
{
	ClearDC();
	SPI1_SendByte(0xA7); //0xA6 normal
}

void Display_Clean()
{
	for(int i = 0; i < 8; i++)
	{
		ClearDC();
		SPI1_SendByte(0xB0 + i);
		SPI1_SendByte(0x00);
		SPI1_SendByte(0x10);

		SetDC();
		for(int c = 0; c < 128; c++)
		{
			SPI1_SendByte(0x00);
		}
	}
}

void Display_Test(void)
{
	for(int i = 0; i < 8; i++)
	{
		Display_SetPage(i);

		for(int c = 0; c < 128; c++)
		{

			if(c % 2 == 0)
			{
				Display_Write(0xFF);
			}
			else Display_Write(0x00);
		}
	}
}

void Display_PrintSymbol(symbol sym, uint8_t page, bool nl)
{
	Display_SetPage(page);

	if(nl)
	{
		Display_SetColumn(0);
	}
	for(int i = 0; i < 8; i++)
	{
		Display_Write(table[sym][i]);
	}
}

void display()
{
	Display_Clean();

	uint16_t r = Led_Get_Color(eRed) * 100 / 4096; // convert led value into %
	uint16_t g = Led_Get_Color(eGreen) * 100 / 4096;
	uint16_t b = Led_Get_Color(eBlue) * 100 / 4096;

	Display_PrintSymbol(eR, 0, true);
	Display_PrintSymbol(eDPoint, 0, false);
	Display_PrintSymbol(r / 100 % 10, 0, false);
	Display_PrintSymbol(r / 10 % 10, 0, false);
	Display_PrintSymbol(r % 10, 0, false);

	Display_PrintSymbol(eG, 2, true);
	Display_PrintSymbol(eDPoint, 2, false);
	Display_PrintSymbol(g / 100 % 10, 2, false);
	Display_PrintSymbol(g / 10 % 10, 2, false);
	Display_PrintSymbol(g % 10, 2, false);

	Display_PrintSymbol(eB, 4, true);
	Display_PrintSymbol(eDPoint, 4, false);
	Display_PrintSymbol(b / 100 % 10, 4, false);
	Display_PrintSymbol(b / 10 % 10, 4, false);
	Display_PrintSymbol(b % 10, 4, false);

	//Display_Test();

	for(int i = 0; i < 15; i++) //display ip
	{
		int temp = GetIP()[i] - 48; //convert ascii to int
		if(temp < 0) //symbol after convert < 0,  set '.'
		{
			temp = 10;
		}
		Display_PrintSymbol(temp, 6, i);
	}
}
