/*
 * L1.c
 *
 * Created: 7/12/2022 4:32:54 PM
 * Author : alexei.guriev
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define LED PD4
#define BUTTON PD0

int main(void)
{
    /* Replace with your application code */
	
	DDRD = (0x01 << LED);     //Configure the PORTD4 as output
	DDRD &= ~ (0x01 << BUTTON);     //Configure the PORTD0 as input
    while (1) 
    {
		if (PIND & (0x01 << BUTTON))
		{
			PORTD |= 1 << LED;
		}
		else
		{
			PORTD &= ~(1 << LED);
		}
	    //PORTD ^= (1 << LED);
		//_delay_us(1000000);
    }
}

