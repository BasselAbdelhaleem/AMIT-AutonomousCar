

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_

#include "REGISTERS_ADDRESSES.h"
#include "../MACROS.h"
#include "../STD_TYPES.h"
#include <avr/interrupt.h>


void TIMER0_Init();
void TIMER0_Start();
void TIMER0_Stop();
void TIMER0_Delay_ms(uint32 delay);
void Set_CallBack(void(*p)(void));
void TIMER0_CTC_Init();
void TIMER0_CTC_delay_ms(uint32 delay);
void TIMER0_CTC_Start();
void TIMER0_CTC_Stop();

void PWM0_INIT();
void PWM0_Generate(uint16 Duty_Cycle);
void PWM0_Start();

void TIMER1_Init();
void PWM1_INIT();
void PWM1_Generate(uint16 Duty_Cycle);


void PWM_Set_OCR(uint16 degree);


void ICU_Init();
#endif /* MCAL_TIMER_H_ */
