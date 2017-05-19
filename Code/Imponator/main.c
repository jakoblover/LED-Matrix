/*
 * Imponator.c
 *
 * Created: 5/12/2017 2:17:03 PM
 * Author : Jakob
 */ 

#define F_CPU 2000000UL

#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "SPI.h"

void clock_init(void);


int main(void)
{
	clock_init();
	spi_init();

	PORTA.DIRSET = 0b11111111; //ROW2
	PORTA.OUTSET = 0b11111111; //ROW2


	
	for(int i = 0; i < 36; i++){
		SPIC.DATA = 0b00101100;
		while(!(SPIC.STATUS & SPI_IF_bm)){}
		_delay_ms(1);
	}
	
	SPI_blankAndLatch();


	
	while (1) 
    {
		if(PORTA.OUT == 0){
			PORTA.OUT+=1;
			_delay_ms(1);
		}
		PORTA.OUT = PORTA.OUT << 1;
		_delay_ms(1);
    }
	
}

void clock_init(){
	OSC.CTRL |= OSC_RC2MEN_bm;
	while(!(OSC.STATUS & OSC_RC2MRDY_bm));
	_PROTECTED_WRITE(CLK_CTRL, CLK_SCLKSEL_RC2M_gc);
}


