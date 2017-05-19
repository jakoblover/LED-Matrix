#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "SPI.h"
#include "Display.h"



void SPI_init(void){
	PORTC.DIRSET |= 1 << 0; //Latch pin for TLC5947
	PORTC.DIRSET |= 1 << 1; //BLANK pin for TLC5947
	PORTC.DIRSET |= 1 << 7; //SCK pin for TLC5947
	PORTC.DIRSET |= 1 << 5; //MOSI pin for TLC5947


	PORTC.PIN4CTRL |= PORT_OPC_PULLUP_gc;
	PORTC.DIRSET |= 1 << 4; //Slave select
	PORTC.OUTSET |= 1 << 4; //Slave select HIGH
	

	SPIC.CTRL |= SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV4_gc | SPI_CLK2X_bm;
	SPIC.INTCTRL |= SPI_INTLVL_LO_gc;
	
	PORTC.OUTCLR |= 1 << 0;
}

void SPI_update(void){
	SPIC.INTCTRL |= SPI_INTLVL_MED_gc; // interrupt level for SPIC set to medium
}

ISR ( SPIC_INT_vect )
{
	static uint8_t	_8bytesSent		= 0;
	static uint8_t	row				= 0;

	SPIC.DATA = 0b0011;
	_8bytesSent++;
	
	
	if(_8bytesSent>36){
		_8bytesSent = 0;
		PORTC.OUTSET |= 1 << 0 | 1<<1;
		PORTC.OUTCLR |= 1 << 0 | 1<<1;
		SPIC.INTCTRL	&=		~( ( 1 << 0 ) | ( 1 << 1 ) );
		
		PORTA.OUT = ~( 1 << row );
		if(++row > 7)
			row = 0;
		
	}
}
