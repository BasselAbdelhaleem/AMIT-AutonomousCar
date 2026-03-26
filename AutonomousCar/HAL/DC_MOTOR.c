#include "DC_MOTOR.h"
#define F_CPU 16000000
#include "util/delay.h"

void DcMotor_Init()
{
	DIO_SetPinDir(DIO_PORTC, DIO_PIN1, DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTC, DIO_PIN2, DIO_PIN_OUTPUT);
    DIO_SetPinDir(DIO_PORTC, DIO_PIN3, DIO_PIN_OUTPUT);
    DIO_SetPinDir(DIO_PORTC, DIO_PIN4, DIO_PIN_OUTPUT);

    PWM0_INIT();
}

void DcMotor_Dir(DC_Motor_Dir dir)
{
	switch (dir)
	{
	case DC_CLOCK_WISE:
		DIO_SetPinVal(DIO_PORTC, DIO_PIN3, DIO_PIN_HIGH);
		DIO_SetPinVal(DIO_PORTC, DIO_PIN4, DIO_PIN_LOW);
		
		DIO_SetPinVal(DIO_PORTC, DIO_PIN1, DIO_PIN_HIGH);
		DIO_SetPinVal(DIO_PORTC, DIO_PIN2, DIO_PIN_LOW);
		break;
		
	case DC_ANTI_CLOCK_WISE:

		DIO_SetPinVal(DIO_PORTC, DIO_PIN4, DIO_PIN_HIGH);
		DIO_SetPinVal(DIO_PORTC, DIO_PIN3, DIO_PIN_LOW);
		
		DIO_SetPinVal(DIO_PORTC, DIO_PIN1, DIO_PIN_HIGH);
		DIO_SetPinVal(DIO_PORTC, DIO_PIN2, DIO_PIN_LOW);
		break;
	}
}

void DcMotor_SetSpeed(uint8 speed)
{
	speed *= 10;
	PWM0_Generate(speed);
}

void DcMotor_Start()
{
	PWM0_Start();
}

void DcMotor_Stop()
{
	DIO_SetPinVal(DIO_PORTC, DIO_PIN4, DIO_PIN_LOW);
	DIO_SetPinVal(DIO_PORTC, DIO_PIN3, DIO_PIN_LOW);
	
	DIO_SetPinVal(DIO_PORTC, DIO_PIN1, DIO_PIN_LOW);
	DIO_SetPinVal(DIO_PORTC, DIO_PIN2, DIO_PIN_LOW);
}

void DcMotor_TurnRight()
{
	DIO_SetPinVal(DIO_PORTC, DIO_PIN3, DIO_PIN_HIGH);
	DIO_SetPinVal(DIO_PORTC, DIO_PIN4, DIO_PIN_LOW);
	
	DIO_SetPinVal(DIO_PORTC, DIO_PIN1, DIO_PIN_LOW);
	DIO_SetPinVal(DIO_PORTC, DIO_PIN2, DIO_PIN_LOW);
	
	_delay_ms(500);
}

void DcMotor_TurnLeft()
{
	DIO_SetPinVal(DIO_PORTC, DIO_PIN3, DIO_PIN_LOW);
	DIO_SetPinVal(DIO_PORTC, DIO_PIN4, DIO_PIN_LOW);
	
	DIO_SetPinVal(DIO_PORTC, DIO_PIN1, DIO_PIN_HIGH);
	DIO_SetPinVal(DIO_PORTC, DIO_PIN2, DIO_PIN_LOW);
	
	_delay_ms(500);
}

void DcMotor_TurnBack()
{
	DIO_SetPinVal(DIO_PORTC, DIO_PIN3, DIO_PIN_HIGH);
	DIO_SetPinVal(DIO_PORTC, DIO_PIN4, DIO_PIN_LOW);
	
	DIO_SetPinVal(DIO_PORTC, DIO_PIN1, DIO_PIN_LOW);
	DIO_SetPinVal(DIO_PORTC, DIO_PIN2, DIO_PIN_LOW);
	
	_delay_ms(1000);
}