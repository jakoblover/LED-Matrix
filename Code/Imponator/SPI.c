#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "SPI.h"


uint16_t BrightnessLookUpTablelol[256] =
{
	0,0,0,1,1,2,3,4,5,6,7,9,10,12,14,16,18,20,22,25,27,30,33,36,39,42,45,49,52,56,
	60,64,68,72,77,81,86,90,95,100,105,111,116,121,127,133,139,145,151,157,163,170,
	176,183,190,197,204,211,219,226,234,242,250,258,266,274,282,291,299,308,317,326,
	335,344,354,363,373,383,393,403,413,423,434,444,455,465,476,487,499,510,521,533,
	544,556,568,580,592,605,617,630,642,655,668,681,694,707,721,734,748,762,776,790,
	804,818,833,847,862,877,892,907,922,937,953,968,984,1000,1016,1032,1048,1064,1081,
	1097,1114,1131,1148,1165,1182,1199,1217,1234,1252,1270,1288,1306,1324,1342,1361,1379,
	1398,1417,1436,1455,1474,1494,1513,1533,1552,1572,1592,1612,1633,1653,1673,1694,1715,
	1736,1757,1778,1799,1820,1842,1863,1885,1907,1929,1951,1973,1996,2018,2041,2063,2086,
	2109,2132,2156,2179,2203,2226,2250,2274,2298,2322,2346,2371,2395,2420,2444,2469,2494,
	2520,2545,2570,2596,2621,2647,2673,2699,2725,2751,2778,2804,2831,2858,2885,2912,2939,
	2966,2994,3021,3049,3076,3104,3132,3161,3189,3217,3246,3274,3303,3332,3361,3390,3420,
	3449,3479,3508,3538,3568,3598,3628,3659,3689,3720,3750,3781,3812,3843,3874,3906,3937,
	3969,4000,4032,4064,4095,4095
};

uint8_t DisplayData[8][24] = 
{
	{200,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


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
	//SPIC.INTCTRL |= SPI_INTLVL_OFF_gc;
	
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
	The sending of the two 12bits variables are divied into three actions, each one choosing the appropriate bits
	to put into the 8bit variable c, which is transmitted once the switch ends.
*/
	
	switch ( _8bytesSent % 3 )			
	{
		case ( 0 ):
			if(row == 0)
				first12Bits = 0b1111111111111111;
			else first12Bits = 0;
			c = ( uint8_t ) (first12Bits >> 4);
			
			break;
	
		// case 0: read out the 16bits value from the lookupTable. Send MSB
	

		case( 1 ):
			if(row == 0)
				second12Bits = 0b1111111111111111;
			else second12Bits = 0;
			++_12bytesSent;
			c = (uint8_t) ( first12Bits << 4 );
			MSB_filter_var = ((uint8_t) ( second12Bits >> 8 ))  & 0x0F;
			c |= MSB_filter_var;
			
			break;
		
		/*	case 1: read out the second 16bit value from the lookuptable.
			NB: if c is OR-ed directly with the 4 MSB of second12Bits,
				the results are unpredictable and leads to strange behaviour. 
				The MSB_filter_var eliminates these bits away.
		*/
			
		case( 2 ):
		
			c = (uint8_t) second12Bits;
			_12bytesSent++;
			break;
		// second12Bits has correct value because of static property		
	
		break;
		
		
		}
		
		SPIC.DATA = c;                  // send data
		_8bytesSent++;
		
		if ( _12bytesSent > 24  || _8bytesSent > 36 )					// if reached end
		{
			row++;
			SPI_blankAndLatch();
			
			SPIC.INTCTRL	&=		~( ( 1 << 0 ) | ( 1 << 1 ) );		// turn off interrupts
			_12bytesSent	=		0;
			_8bytesSent		=		0;
			
			if(row > 8){
				row = 0;
				PORTA.OUT = (1<<0);
			}
			else if (row == 1) PORTA.OUT = (1<<0);
			else {
				PORTA.OUT= PORTA.OUT << 1;
				}
			
		}	
}
