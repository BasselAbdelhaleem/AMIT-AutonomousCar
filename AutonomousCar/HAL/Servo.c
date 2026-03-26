#include "Servo.h"
#define F_CPU 16000000
#include <util/delay.h>

//extern int isrID;

void ServoMotor_Init()
{
	//PWM1_INIT(); //20ms -- 50hz
	DIO_SetPinDir(DIO_PORTD, DIO_PIN2, DIO_PIN_OUTPUT);
}

void ServoMotor_Set_Degree(ServoDegree degree)
{
	switch(degree)
	{
	case 0:
		//PWM_Set_OCR(97);
		
		DIO_SetPinVal(DIO_PORTD, DIO_PIN2, DIO_PIN_HIGH);
		_delay_ms(0.5);
		DIO_SetPinVal(DIO_PORTD, DIO_PIN2, DIO_PIN_LOW);
		
		break;
	case 1:
		//PWM_Set_OCR(316);
		
		DIO_SetPinVal(DIO_PORTD, DIO_PIN2, DIO_PIN_HIGH);
		_delay_ms(1.5);
		DIO_SetPinVal(DIO_PORTD, DIO_PIN2, DIO_PIN_LOW);
		
		break;
	case 2:
		//isrID = 2;
		//PWM_Set_OCR(535);
		
		DIO_SetPinVal(DIO_PORTD, DIO_PIN2, DIO_PIN_HIGH);
		_delay_ms(2.5);
		DIO_SetPinVal(DIO_PORTD, DIO_PIN2, DIO_PIN_LOW);
		
		break;
	}
}
