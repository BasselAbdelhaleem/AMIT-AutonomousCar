/*
 * LCD.c
 *
 *  Created on: Aug 27, 2022
 *      Author: ahmed
 */

#include "LCD.h"
#include <util/delay.h>
void LCD_Init()
{


#if      LCD_MODE   ==    8
	/*initializing the pins direction in 8-bit mode*/
	DIO_SetPinDir(LCD_8BIT_CMD_PORT , LCD_RS_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_8BIT_CMD_PORT , LCD_RW_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_8BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_OUTPUT);

	DIO_SetPortDir(LCD_8BIT_DATA_PORT , DIO_PORT_OUTPUT);

	_delay_ms(100);
	/*send commands to LCD for initializing as 8-bit mode*/
	LCD_WriteCommand(0x38);
	/*Cursor off*/
	LCD_WriteCommand(0x0C);
	/*clear LCD*/
	LCD_WriteCommand(0x01);
	/*Increment Cursor*/
	LCD_WriteCommand(0x06);
	/*Return Home*/
	LCD_WriteCommand(0x02);

	#elif    LCD_MODE   ==    4
	/*initializing the pins direction in 4-bit mode*/
	DIO_SetPinDir(LCD_4BIT_CMD_PORT , LCD_RS_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_CMD_PORT , LCD_RW_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_OUTPUT);

	DIO_SetPinDir(LCD_4BIT_DATA_PORT , D4_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_DATA_PORT , D5_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_DATA_PORT , D6_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_DATA_PORT , D7_PIN , DIO_PIN_OUTPUT);

	_delay_ms(100);
	/*send commands to LCD for initializing as 4-bit mode*/
	LCD_WriteCommand(0x33);
	LCD_WriteCommand(0x32);
	LCD_WriteCommand(0x28);

	/*display on ,cursor off*/
	LCD_WriteCommand(0x0C);
	/*clear display*/
	LCD_WriteCommand(0x01);
	/* return home*/
	LCD_WriteCommand(0x02);




#else



#endif
}

void LCD_WriteCommand(uint8 cmd)
{
		uint8 command,portValue;
		//send command
		DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_RS_PIN , DIO_PIN_LOW);
		//Write on LCD
		DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_RW_PIN , DIO_PIN_LOW);
		//Low level on E PIN
		DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);

		//get data of the port
		portValue=DIO_GetPortVal(LCD_4BIT_DATA_PORT);
		//write high bit of my cmd
		command = (cmd & 0xf0) | ( portValue & 0x0f);
		// write it bach to port
		DIO_SetPortVal(LCD_4BIT_DATA_PORT, command);

		//E PIN high
		DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_HIGH);
		_delay_ms(1);
		//e PIN LOW to get edge triggered
		DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);

		portValue=DIO_GetPortVal(LCD_4BIT_DATA_PORT);
		command = (cmd << 4) | (portValue & 0x0f);

		DIO_SetPortVal(LCD_4BIT_DATA_PORT, command);

		DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_HIGH);
		_delay_ms(1);
		DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);


		_delay_ms(5);

}

void LCD_WriteChar(uint8 chr)
{

	uint8 data,portValue;
	DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_RS_PIN , DIO_PIN_HIGH);
	DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_RW_PIN , DIO_PIN_LOW);
	DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);

	portValue=DIO_GetPortVal(LCD_4BIT_DATA_PORT);
	data = (chr & 0xf0) | (portValue & 0x0f);

	DIO_SetPortVal(LCD_4BIT_DATA_PORT, data);

	DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_HIGH);
			_delay_ms(1);
	DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);

	portValue=DIO_GetPortVal(LCD_4BIT_DATA_PORT);
	data = (chr << 4) | (portValue & 0x0f);

	DIO_SetPortVal(LCD_4BIT_DATA_PORT, data);

	DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_HIGH);
			_delay_ms(1);
	DIO_SetPinVal(LCD_4BIT_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);


	_delay_ms(5);
}


void LCD_WriteString(uint8* str)
{
	uint8 i = 0 ;

	while(str[i] != '\0')
	{
		LCD_WriteChar(str[i]);
		i++;
	}
}


void LCD_GoTo(uint8 row , uint8 col)
{
	uint8 pos[2] = {0x80 , 0xc0};

	LCD_WriteCommand(pos[row]+col);
}

void LCD_WriteInteger(sint32 intgr)
{

	sint32 y = 1;

	if(intgr < 0)
	{
		LCD_WriteChar('-');
		intgr *= -1;
	}

	while(intgr > 0)
	{
		y = ((y*10) + (intgr%10));
		intgr /= 10;
	}

	while(y > 1 )
	{
		LCD_WriteChar(((y%10)+48));
		y /= 10;
	}
}




