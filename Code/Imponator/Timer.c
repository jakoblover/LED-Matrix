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

uint8_t ranForFirstTime = 0;
void Timer0_init(void)
{
	TCC0.CTRLA = 0b00000011; //PRESCALER CLK_DIV4
	TCC0.INTCTRLA = 0b00000011; //Interrupt level HIGH
	TCC0.PER = 5000;
}
/*		Timer 0 is used for the periodic update of the Display		*/

ISR ( TCC0_OVF_vect )
{
	SPI_update();
}