/*
 * Peripherals.c
 *
 * Created: 22-May-17 9:22:20 PM
 *  Author: Jakob
 */ 

#include "Peripherals.h"
#include "Print.h"
#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Peripherals_init(void){
	PORTD.DIRCLR =  (1 << 0) | (1 << BUTTON_1) | (1 << BUTTON_2);
	PORTD.INTCTRL = PORT_INT0LVL_HI_gc;
	PORTD.INT0MASK = (1 << 0) | (1 << BUTTON_1) | (1 << BUTTON_2);
}

ISR (PORTD_INT0_vect){
	if (PORTD.IN & 0b00000001)
		TCC1.PER = 10000;
	else TCC1.PER = 2000;

	
}