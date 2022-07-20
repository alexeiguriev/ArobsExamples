/*
 * Pwm.c
 *
 * Created: 7/20/2022 5:28:53 PM
 *  Author: alexei.guriev
 */
 #include <avr/io.h>
 #include "Pwm.h"
 #include "TimerSw.h"
 #include "TimerCfg.h"

typedef enum
{
	CounterInc,
	CounterDec
}CounterState;

static uint8_t duty;
static TimerSwHandle timerSwHandle;
static CounterState counterState;

void PwmInit()
{
	StatusError err;
	
	TimerSwInitParam *pTimerSwInitParam = TimerGetIntervalPointerCfg();
	
	err = TimerSwInit(pTimerSwInitParam,&timerSwHandle);
	
	if (err == StatusErrNone)
	{
		TimerSwStartup(&timerSwHandle,PWM_DATAUPDATE_MS);
	}
	
	counterState = CounterInc;
	duty = 0;
	
	/*set fast PWM mode with non-inverted output*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB|=(1<<PB3);  /*set OC0 pin as output*/
	
}


void PwmRutine()
{
	StatusError err;
	err = TimerSwIsExpired(&timerSwHandle);
	if (err == StatusErrTime)
	{
		switch(counterState)
		{
			case CounterInc:
			duty += DUTY_STEP;
			if (duty >= COUNTER_MAX_VALUE)
			{
				counterState = CounterDec;
			}
			break;
			case CounterDec:
			duty -= DUTY_STEP;
			if (duty <= 0)
			{
				counterState = CounterInc;
			}
			break;
			default:
			counterState = CounterInc;
			break;
			
		}
		
		OCR0=duty;
		
		TimerSwStartup(&timerSwHandle,PWM_DATAUPDATE_MS);
	}
}
