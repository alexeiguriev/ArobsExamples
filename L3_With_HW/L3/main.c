/*
 * L3.c
 *
 * Created: 7/18/2022 5:14:20 PM
 * Author : alexei.guriev
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "StatuError.h"
#include "TimerSw.h"


#define TIMER_INTERVAL_MS	1000 
#define LED PD4

uint32_t interval;
TimerSwHandle timerSwHandle;

void TimerInit()
{
	TimerInitCfg();
	TimerEnableCfg(true);
	
	sei();
}

void PortPinInit()
{
	DDRD = (0x01 << LED);     //Configure the PORTD4 as output
}

int main(void)
{
	StatusError err;
	
	TimerInit();
	TimerEnableCfg(true);
	PortPinInit();
	
	TimerSwInitParam *pTimerSwInitParam = TimerGetIntervalPointerCfg();
	
	err = TimerSwInit(pTimerSwInitParam,&timerSwHandle);
	
	if (err == StatusErrNone)
	{
		TimerSwStartup(&timerSwHandle,TIMER_INTERVAL_MS);
	}
	
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		err = TimerSwIsExpired(&timerSwHandle);
		if (err == StatusErrTime)
		{
			PORTD ^= (1 << LED);
			TimerSwStartup(&timerSwHandle,TIMER_INTERVAL_MS);
		}
    }
}

