/*
 * L2.c
 *
 * Created: 7/13/2022 5:32:22 PM
 * Author : alexei.guriev
 */ 
#define F_CPU 16000000
#define LED PD4
#define TOLERANCE 20

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

uint16_t adcValue;

bool ledState = false;

void ADCInit(void){
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));   // 16Mhz/128 = 125Khz the ADC reference clock
	ADMUX |= (1<<REFS0);                            // Voltage reference from Avcc (5v)
	ADCSRA |= (1<<ADEN);                            // Turn on ADC
	ADCSRA |= (1<<ADSC);                            // Do an initial conversion because this one is the slowest and to ensure that everything is up and running
}

uint16_t ADCRead(uint8_t channel){
	ADMUX &= 0xF0;                            // Clear the older channel that was read
	ADMUX |= channel;                            // Defines the new ADC channel to be read
	ADCSRA |= (1<<ADSC);                            // Starts a new conversion
	while(ADCSRA & (1<<ADSC));                        // Wait until the conversion is done
	return ADCW;                                // Returns the ADC value of the chosen channel
}

static void DataAnalize(uint16_t value);

int main(void)
{
	DDRD = (0x01 << LED);     //Configure the PORTD4 as output
	ADCInit();
	/* Replace with your application code */
	while (1)
	{
		adcValue = ADCRead(0);
		_delay_ms(100);
		ADCRead(0);
		
		DataAnalize(adcValue);
		
		if (ledState == true)
		{
			PORTD |= 1 << LED;
		}
		else
		{
			PORTD &= ~(1 << LED);
		}
	}
}

static void DataAnalize(uint16_t value)
{
	if (ledState == true)
	{
		if (value < (512 - TOLERANCE))
		{
			ledState = false;
		}
	}
	else
	{
		if (value > (512 + TOLERANCE))
		{
			ledState = true;
		}
	}
};
