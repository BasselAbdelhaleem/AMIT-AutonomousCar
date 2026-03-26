#include "Ultrasonic.h"

#include "../MCAL/TIMER.h"
#include "util/delay.h"

int TimerOverflow = 0;
long count;
double distance;

//extern int isrID;

void Ultrasonic_init()
{
	TIMER1_Init();
	ICU_Init();
	SET_BIT(SREG,7);
}

double Ultrasonic_getDistance()
{
	//isrID = 1;
	SET_BIT(TriggerPort,TriggerPin);
	_delay_us(10);
	CLR_BIT(TriggerPort,TriggerPin);

	TCNT1 = 0x00;
	TCCR1B = 0x41;
	SET_BIT(TIFR,ICF1);
	SET_BIT(TIFR,TOV1);

	while((TIFR & (1<<ICF1)) == 0);
	TCNT1 = 0x00;
	TCCR1B = 0x01;
	SET_BIT(TIFR,ICF1);
	SET_BIT(TIFR,TOV1);
	TimerOverflow = 0;

	while((TIFR & (1<<ICF1)) == 0);
	count = ICR1 + (65535 * TimerOverflow);
	distance = (double)count/466.47;

	//isrID = 0;

	return distance;
}
