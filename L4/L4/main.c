/*
 * L4.c
 *
 * Created: 7/20/2022 5:10:02 PM
 * Author : alexei.guriev
 */ 

#include <avr/interrupt.h>
#include "Pwm.h"
#include "Int.h"
#include "TimerCfg.h"

#include <stdbool.h>

void Hardware_Timer();

int main(void)
{
	Hardware_Timer();
	
	PwmInit();
	IntInit();
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
		PwmRutine();
    }
}

void Hardware_Timer()
{
	TimerInitCfg();
	TimerEnableCfg(true);
}
