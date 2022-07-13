/*
 * L1.c
 *
 * Created: 7/12/2022 4:32:54 PM
 * Author : alexei.guriev
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

typedef enum
{
	TogglStateNo,
	TogglStateWaiting,
	TogglStateDone
}TogglState;

typedef enum
{
	ButtonStatePressed,
	ButtonStateRealesed,
}ButtonState;

#define LED PD4
#define BUTTON PD0
#define MAX_COUNTER_VALUE 100

TogglState togglState = TogglStateNo;
ButtonState buttonState = ButtonStateRealesed;

uint16_t counter = 0;

int main(void)
{
    /* Replace with your application code */
	
	DDRD = (0x01 << LED);     //Configure the PORTD4 as output
	DDRD &= ~ (0x01 << BUTTON);     //Configure the PORTD0 as input
    while (1) 
    {
		_delay_us(1);
		if (PIND & (0x01 << BUTTON))
		{
			if (counter != 0)
			{
				counter--;	
			}
			else
			{
				buttonState = ButtonStateRealesed;				
			}
		}
		else
		{
			if (counter <= MAX_COUNTER_VALUE)
			{
				counter++;	
			}
			else
			{
				buttonState = ButtonStatePressed;				
			}
		}
		
		if (buttonState == ButtonStateRealesed)
		{
			togglState = TogglStateNo;
		}
		else
		{
			if (togglState == TogglStateNo)
			{
				togglState = TogglStateWaiting;
			}
			
		}
		
		if (togglState == TogglStateWaiting)
		{
			PORTD ^= (1 << LED);
			togglState = TogglStateDone;
		}
	    //PORTD ^= (1 << LED);
		//_delay_us(1000000);
    }
}

