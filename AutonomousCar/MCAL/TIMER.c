
#include "TIMER.h"
uint32 Number_OVRflows =0 ;
uint32 Init_Value = 0;

volatile uint32 Num_OVF1 = 0;
volatile uint32 ICR_CAPT1 = 0;
volatile uint32 ICR_CAPT2 = 0;
volatile uint32 ICR_CAPT3 = 0;
volatile uint32 ICR_COUNTER = 0;
void (*ptr)(void) = 0 ;


void TIMER0_Init()
{
	TCNT0 = 0x00;
	TCCR0 = 0x00;
	SET_BIT(TIMSK,0);

}
void TIMER0_Start()
{
	TCCR0 |= 0x05;

}
void TIMER0_Stop()
{
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
}

void TIMER0_Delay_ms(uint32 delay)
{
	uint32 Tick_Time = (1024 / 16) ;

	uint32 Total_Ticks = (delay * 1000) / Tick_Time ;

	Number_OVRflows = Total_Ticks / 256 ;

	Init_Value  =   256 - (Total_Ticks % 256) ;

	TCNT0 = Init_Value ;

	Number_OVRflows++;


}
void Set_CallBack(void(*p)(void))
{

	ptr = p ;

}

void PWM0_INIT()
{
	SET_BIT(DDRB,3); //output
	TCCR0 |= 0x68;
}

void PWM0_Generate(uint16 Duty_Cycle)
{
	OCR0 = ((Duty_Cycle * 256)/100)-1;
}
void PWM0_Start()
{
	TCCR0 |=0x05;
}

void TIMER1_Init()
{
	TCNT1 = 0x00;
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	SET_BIT(TIMSK,2);
	SET_BIT(TIMSK,5);
}

void PWM1_INIT()
{
	SET_BIT(DDRD,5);
	TCCR1B |=0x1B;
	TCCR1A |=0x82;
	ICR1 = 4999;
}

void PWM1_Generate(uint16 Duty_Cycle)
{
	OCR1A = ((Duty_Cycle * 4999)/100)-1;
}

void PWM_Set_OCR(uint16 degree)
{

	OCR1A = degree;
}

void ICU_Init()
{
	ICR1=0x0000;
	CLR_BIT(DDRD,6);
	TCCR1B |= 0x41;
	TCCR1A = 0x00;
   SET_BIT(TIMSK,2);
   SET_BIT(TIMSK,5);

}
/*
ISR(TIMER1_OVF_vect)
{
	Num_OVF1++;

}
*/
ISR(TIMER1_CAPT_vect)
{

	ICR_COUNTER++;
	if(ICR_COUNTER==1)
	{
		Num_OVF1=0;
		ICR_CAPT1 = ICR1;
		CLR_BIT(TCCR1B,6);
	}
	else if(ICR_COUNTER==2)
	{
		ICR_CAPT2 = ICR1 +(Num_OVF1*65535);
		SET_BIT(TCCR1B,6);
	}
	else if(ICR_COUNTER==3)\
	{
		ICR_CAPT3 = ICR1 +(Num_OVF1*65535);
		CLR_BIT(TIMSK,5);
	}


}







