/*
 * LCD.h
 *
 *  Created on: Aug 27, 2022
 *      Author: ahmed
 */

#ifndef HALL_LCD_H_
#define HALL_LCD_H_
#include "../MCAL/DIO.h"
#include "LCD_Cfg.h"


void LCD_Init();
void LCD_WriteCommand(uint8 cmd);
void LCD_WriteChar(uint8 chr);

void LCD_WriteString(uint8* str);
void LCD_GoTo(uint8 row , uint8 col);

void LCD_WriteInteger(sint32 intgr);

#endif /* HALL_LCD_H_ */
