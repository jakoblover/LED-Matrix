#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "SPI.h"
#include "Display.h"
#include "ProgmemData.h"


void SPI_init(void){
	PORTC.DIRSET |= 1 << 0; //Latch pin for TLC5947
	PORTC.DIRSET |= 1 << 1; //BLANK pin for TLC5947
	PORTC.DIRSET |= 1 << 7; //SCK pin for TLC5947
	PORTC.DIRSET |= 1 << 5; //MOSI pin for TLC5947


	PORTC.PIN4CTRL |= PORT_OPC_PULLUP_gc;
	PORTC.DIRSET |= 1 << 4; //Slave select
	PORTC.OUTSET |= 1 << 4; //Slave select HIGH
	

	SPIC.CTRL |= SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV128_gc | SPI_CLK2X_bm;
	SPIC.INTCTRL |= SPI_INTLVL_LO_gc;
	
	PORTC.OUTCLR |= 1 << 0;
}

void SPI_update(void){
	SPIC.INTCTRL |= SPI_INTLVL_MED_gc; // interrupt level for SPIC set to medium
}

void SPI_blankAndLatch(void){
	PORTC.OUTSET |= 1 << 0 | 1<<1;
	PORTC.OUTCLR |= 1 << 0 | 1<<1;
}

ISR ( SPIC_INT_vect )
{
	static uint8_t		_12bytesSent	= 0;
	static uint8_t		_8bytesSent		= 0;
	static uint8_t		row				= 0;
	
	static uint16_t		first12Bits		= 0;
	static uint16_t		second12Bits	= 0;
	
	uint8_t				c				= 0;
	uint8_t				MSB_filter_var	= 0;

	
/*
	The data is sent in batches of two 12bits variables, divided into three 8bits variables. ( 12*2 == 8*3 )
	The sending of the two 12bits variables are divided into three actions, each one choosing the appropriate bits
	to put into the 8bit variable c, which is transmitted once the switch ends.
*/
	
	switch ( _8bytesSent % 3 )			
	{
		case ( 0 ):
			first12Bits = pgm_read_word(  & (  BrightnessLookUpTable[Display_getChannelBrightness(row,23-_12bytesSent)] ) );
			c = ( uint8_t ) (first12Bits >> 4);
			
			break;

		case( 1 ):
			++_12bytesSent;
			second12Bits = pgm_read_word(  & (   BrightnessLookUpTable[Display_getChannelBrightness(row,23-_12bytesSent)]) );
			c = (uint8_t) ( first12Bits << 4 );
			MSB_filter_var = ((uint8_t) ( second12Bits >> 8 ))  & 0x0F;
			c |= MSB_filter_var;

			break;
			
		case( 2 ):
		
			c = (uint8_t) second12Bits;
			_12bytesSent++;
			break;	
	
		break;
		
		
		}
		
		SPIC.DATA = c;                  // send data
		_8bytesSent++;
		
		if ( _12bytesSent >= 24  || _8bytesSent >= 36 )					// if reached end
		{
			while(!(SPIC_STATUS & SPI_IF_bm)){}
			SPI_blankAndLatch();
			
			SPIC.INTCTRL	&=		~( ( 1 << 0 ) | ( 1 << 1 ) );		// turn off interrupts
			_12bytesSent	=		0;
			_8bytesSent		=		0;
			
			if(row > 7){
				row = 0;
				PORTA.OUT = (1<<0);
			}
			else if (row == 0) PORTA.OUT = (1<<0);
			else PORTA.OUT= PORTA.OUT << 1;
			
			/*
			switch(row){
				case(0):
				PORTA.OUT = 0b00000001;
				break;
				case(1):
				PORTA.OUT = 0b00000010;
				break;
				case(2):
				PORTA.OUT = 0b00000100;
				break;
				case(3):
				PORTA.OUT = 0b00001000;
				break;
				case(4):
				PORTA.OUT = 0b00010000;
				break;
				case(5):
				PORTA.OUT = 0b00100000;
				break;
				case(6):
				PORTA.OUT = 0b01000000;
				break;
				case(7):
				PORTA.OUT = 0b10000000;
				break;
			}*/
			row++;
			if(row == 8)
				row = 0;
			
		}	
}
