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
	
	sei();
	PMIC.CTRL |= 7; //all interrupt levels are enabled
	
	
	PORTA.DIRSET = 0b11111111; //ROW2
	PORTA.OUTSET = 0b00000001; //ROW2
	SPIC.DATA = 0b00000000;
	
	/*for(int i = 0; i < 36; i++){
		SPIC.DATA = 0b11111111;
		while(!(SPIC_STATUS & SPI_IF_bm)){};
	}
	SPI_blankAndLatch();*/

	while (1) 
    {
	/*if(PORTA.OUT == 0){
		PORTA.OUT+=1;
		_delay_us(50);
	}
		PORTA.OUT = PORTA.OUT << 1;
		
		_delay_us(50);*/
    }
}

void clock_init(){
	OSC.CTRL |= OSC_RC32MEN_bm;
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));
	_PROTECTED_WRITE(CLK_CTRL, CLK_SCLKSEL_RC32M_gc);
}
