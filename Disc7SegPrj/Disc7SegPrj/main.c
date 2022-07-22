/*
 * Disc7SegPrj.c
 *
 * Created: 7/19/2022 6:31:23 PM
 * Author : alexei.guriev
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include "stdbool.h"
#include <avr/interrupt.h>
#include "TimerCfg.h"
#include "TimerSw.h"
#include "Disp7Seg.h"

float testValue = 12.34;
float oldtestValue = 0;

#define LED PD4
void init_PWM_Timer();

int main(void)
{
    /* Replace with your application code */
    init_PWM_Timer();
    Disp7SegInit();
    while (1) 
    {
	    if (oldtestValue != testValue)
	    {
		    Disp7SegSetFloatVal(testValue);
	    }
	    Disp7SegRutine();
    }
}

void init_PWM_Timer(){
	//DDRD = (0x01 << LED);     //Configure the PORTD4 as output
	
	TimerInitCfg();
	TimerEnableCfg(true);
	
	sei();
}