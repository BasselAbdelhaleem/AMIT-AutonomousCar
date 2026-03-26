
#ifndef HALL_SERVO_H_
#define HALL_SERVO_H_
#include "../MCAL/TIMER.h"
#include "../MCAL/DIO.h"

typedef enum
{
	ServoMotor_Degree_0,
	ServoMotor_Degree_90,
	ServoMotor_Degree_180,
}ServoDegree;

void ServoMotor_Init();

void ServoMotor_Set_Degree(ServoDegree degree);


#endif /* HALL_SERVO_H_ */
