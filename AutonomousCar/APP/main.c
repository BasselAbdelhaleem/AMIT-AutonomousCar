#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../MACROS.h"
#include "../STD_TYPES.h"
#include "../HAL/Servo.h"
#include "../HAL/Ultrasonic.h"
#include "../HAL/LCD.h"
#include "../HAL/DC_MOTOR.h"

extern int TimerOverflow;

int maxDistance = 40;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;
}

int main()
{
	//LCD_Init();
	//Ultrasonic_init();
	//ServoMotor_Init();
	DcMotor_Init();
	DcMotor_Dir(DC_CLOCK_WISE);
	DcMotor_SetSpeed(10);
	DcMotor_Start();
	
	while(1)
	{
		/*
		LCD_WriteCommand(0x01);
		LCD_WriteCommand(0x02);
		LCD_WriteString("  Forward");
		
		ServoMotor_Set_Degree(ServoMotor_Degree_90);
		_delay_ms(500);
		*/
		
		/*
		if ((sint32)Ultrasonic_getDistance() < maxDistance)
		{
			//DcMotor_Stop();
			
			ServoMotor_Set_Degree(ServoMotor_Degree_0);
			_delay_ms(500);
			if ((sint32)Ultrasonic_getDistance() > maxDistance)
			{
				LCD_WriteCommand(0x01);
				LCD_WriteCommand(0x02);
				LCD_WriteString("  Right");
				//DcMotor_TurnRight();
				
				ServoMotor_Set_Degree(ServoMotor_Degree_90);
				_delay_ms(500);
			}
			else
			{
				ServoMotor_Set_Degree(ServoMotor_Degree_180);
				_delay_ms(500);
				if ((sint32)Ultrasonic_getDistance() > maxDistance)
				{
					LCD_WriteCommand(0x01);
					LCD_WriteCommand(0x02);
					LCD_WriteString("  Left");
					//DcMotor_TurnLeft();
					
					ServoMotor_Set_Degree(ServoMotor_Degree_90);
					_delay_ms(500);
				}
				else
				{
					LCD_WriteCommand(0x01);
					LCD_WriteCommand(0x02);
					LCD_WriteString("  Back");
					//DcMotor_TurnBack();
					
					ServoMotor_Set_Degree(ServoMotor_Degree_90);
					_delay_ms(500);
				}
			}
		}
		*/
     }
}
