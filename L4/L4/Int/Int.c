/*
 * Int.c
 *
 * Created: 7/20/2022 5:10:50 PM
 *  Author: alexei.guriev
 */
#include "Int.h"
#include <avr/interrupt.h>

void TogglePin(void);

ISR(INT0_vect)
{
	TogglePin();
}

void IntInit(void)
{
	PORT_DIRECTION_LED |= (1 << PIN_LED); // Led pin set as output
	PORT_DIRECTION_BUTTON &= ~(1 << PIN_BUTTON); // Button pin set as input
	
	GICR = 1<<INT0;					/* Enable INT0*/
	MCUCR = 1<<ISC01 | 0<<ISC00;	/* Trigger INT0 on falling edge */
	
	PORT_BUTTON |= (1 << PIN_BUTTON);  /* Make pull up high */
	
}

void TogglePin(void)
{
	PORT_LED ^= (1 << PIN_LED);
}