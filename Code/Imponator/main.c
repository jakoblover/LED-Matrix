/*
 * Imponator.c
 *
 * Created: 5/12/2017 2:17:03 PM
 * Author : Jakob
 */ 

#define F_CPU 32000000UL //change this

#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "SPI.h"
#include "Timer.h"


void clock_init(void);

int main(void)
{
	clock_init();
	SPI_init();
	Timer0_init();
	
	
	
	
	PORTA.DIRSET = 0b11111111; //ROW2
	PORTA.OUTSET = 0b00000000; //ROW2
	SPIC.DATA = 0; //Used to trigger the SPI interrupts
	
	sei(); //activate global interrupts
	PMIC.CTRL |= 7; //all interrupt levels are enabled
	

	while (1) 
    {
		
		
		
	}
}

void clock_init(){
	OSC.CTRL |= OSC_RC32MEN_bm;
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));
	_PROTECTED_WRITE(CLK_CTRL, CLK_SCLKSEL_RC32M_gc);
}
