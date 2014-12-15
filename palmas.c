/*
 * palmas.c
 *
 * Created: 03/04/2013 23:28:19
 *  Author: Cesar
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

volatile int habilitar_timer=0, comenzar_silencio=0, cuenta_silencio=0,flanco_detectado=0,encendido=0;
const int duracion_silencio=600, max_silencio=1600, max_silencio2=4000;

char pinEntrada=0, pinSalida=1;

int main(void)
{
	//Configuracion del temporizador
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt
	OCR1A   = 1000;// // Set CTC compare value to 1Hz at 1MHz AVR clock
	TCCR1B |= ((0 << CS10) | (1 << CS11) | (0 << CS12)); // Start timer at Fcpu/8
	
	//puertos
	pinMode(pinEntrada, INPUT);
	pinMode(pinSalida, OUTPUT);

	sei(); //  Enable global interrupts
	
    while(1)
    {
        if (!digitalRead(pinEntrada))
		{
			habilitar_timer=1;
			comenzar_silencio=0;
			cuenta_silencio=0;
			while(!digitalRead(pinEntrada);
			if (flanco_detectado==2)
			{
				flanco_detectado=0;
			}
		}		
    }
}

ISR(TIMER1_COMPA_vect)
{
	if (habilitar_timer)
	{
		cuenta_silencio++;
		
		if (cuenta_silencio==duracion_silencio)
		{
			flanco_detectado++;
		}else if (cuenta_silencio>max_silencio & flanco_detectado==1)
		{
			habilitar_timer=0;
			flanco_detectado=0;
		}else if (cuenta_silencio>max_silencio2 & flanco_detectado==2)
		{
			if (encendido)
			{
				PORTD&=~(1<<PD4);
				encendido=0;
			}else
			{
				PORTD|=(1<<PD4);
				encendido=1;
			}
			flanco_detectado=0;
			habilitar_timer=0;
		}
	}
}