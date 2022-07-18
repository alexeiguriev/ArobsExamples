/*
 * L3.c
 *
 * Created: 7/18/2022 5:14:20 PM
 * Author : alexei.guriev
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>


#define TIMER_CFG_COUNTER_INIT_STATE 45535
#define LED PD4

uint32_t interval;

ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	interval++;
	
	if(interval > 100)
	{
		PORTD ^= (1 << LED);
		interval = 0;
	}
	
	TCNT1 = TIMER_CFG_COUNTER_INIT_STATE;
}

void TimerInit()
{
	TCNT1 = TIMER_CFG_COUNTER_INIT_STATE;
	TCCR1A = 0x00;
	TCCR1B = 0x00;

	TCCR1B = (1<<CS11);  // Timer mode with 8 prescler
}

void TimerEnableCfg(bool state){
	
	if(state == false)
	{
		TIMSK &= ~(1UL << TOIE1); // Disable timer1 overflow interrupt(TOIE1)
	}
	else
	{
		TIMSK = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
	}
}

void PortPinInit()
{
	DDRD = (0x01 << LED);     //Configure the PORTD4 as output
}

int main(void)
{
	TimerInit();
	TimerEnableCfg(true);
	PortPinInit();
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

