#ifndef HALL_DC_MOTOR_H_
#define HALL_DC_MOTOR_H_

#include "../MCAL/DIO.h"
#include "../MCAL/TIMER.h"

typedef enum
{
DC_CLOCK_WISE,
DC_ANTI_CLOCK_WISE
}DC_Motor_Dir;

void DcMotor_Init();
void DcMotor_Dir(DC_Motor_Dir dir);
void DcMotor_SetSpeed(uint8 speed);
void DcMotor_Start();
void DcMotor_Stop();
void DcMotor_TurnRight();
void DcMotor_TurnLeft();
void DcMotor_TurnBack();
#endif /* HALL_DC_MOTOR_H_ */
