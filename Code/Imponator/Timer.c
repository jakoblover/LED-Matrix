/*
 * Timer.c
 *
 * Created: 19-May-17 11:29:01 PM
 *  Author: Jakob
 */ 
#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "Timer.h"
#include "SPI.h"
#include "Display.h"
#include "Print.h"

void Timer0_init(void)
{
	TCC0.CTRLA = 0b00000011; //PRESCALER CLK_DIV4
	TCC0.INTCTRLA = 0b00000011; //Interrupt level HIGH
	TCC0.PER = 5000;
}
/*		Timer 0 is used for the periodic update of the Display		*/

void Timer1_init(void)
{
	TCC1.CTRLA = 0b00000111; //PRESCALER CLK_DIV1024
	TCC1.INTCTRLA = 0b00000001; //Interrupt level LOW
	TCC1.PER = 20000;
}
/*		Timer 1		*/

ISR ( TCC0_OVF_vect )
{
	SPI_update();
}

ISR ( TCC1_OVF_vect )
{
	
}
