/*
 * Imponator.c
 *
 * Created: 5/12/2017 2:17:03 PM
 * Author : Jakob
 */ 

#define F_CPU 2000000UL //change this
#define _latPort PORTC
#define _latPin 0
#define _SSPort PORTC
#define _SSPin 4

#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#define NUM_BYTES     4


void clock_init(void);

int main(void)
{
	clock_init();
	
	_latPort.DIRSET |= 1 << _latPin; //Latch pin for TLC5947
	_latPort.DIRSET |= 1 << 1; //BLANK pin for TLC5947
	_latPort.DIRSET |= 1 << 7; //SCK pin for TLC5947
	_latPort.DIRSET |= 1 << 5; //MOSI pin for TLC5947


	PORTA.DIRSET = 0b11111111; //ROW2

	_SSPort.PIN4CTRL |= PORT_OPC_PULLUP_gc;
	_SSPort.DIRSET |= 1 << _SSPin; //Slave select
	_SSPort.OUTSET |= 1 << _SSPin; //Slave select HIGH
	PORTA.OUTSET = 0b11111111; //ROW2

	SPIC.CTRL |= SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc;
	SPIC.INTCTRL |= SPI_INTLVL_OFF_gc;

		_latPort.OUTCLR |= 1 << _latPin;

		SPIC.DATA = 0b11111111;
		while(!(SPIC.STATUS & SPI_IF_bm)){}
		SPIC.DATA = 0b11110000;
		while(!(SPIC.STATUS & SPI_IF_bm)){}

		for(int i = 0; i < 34; i++){
			SPIC.DATA = 0b00000000;
			while(!(SPIC.STATUS & SPI_IF_bm)){}
		}
		_latPort.OUTSET |= 1 << _latPin;
		_latPort.OUTCLR |= 1 << _latPin;


	
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
