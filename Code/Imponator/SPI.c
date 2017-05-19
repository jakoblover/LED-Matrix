/*
 * SPI.c
 *
 * Created: 18-May-17 8:28:57 PM
 *  Author: Jakob
 */ 

#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "SPI.h"

void spi_init(){
	PORTC.DIRSET |= 1 << 0; //Latch pin for TLC5947
	PORTC.DIRSET |= 1 << 1; //BLANK pin for TLC5947
	PORTC.DIRSET |= 1 << 7; //SCK pin for TLC5947
	PORTC.DIRSET |= 1 << 5; //MOSI pin for TLC5947
	PORTC.DIRSET |= 1 << 4; //Slave select
	//PORTC.DIRSET |= 0b10110011;
	
	PORTC.PIN4CTRL |= PORT_OPC_PULLUP_gc; //Slave select requires a pull-up i guess
	PORTC.OUTSET |= 1 << 4; //Slave select HIGH. This is to prevent the XMEGA from being reset to slave
	PORTC.OUTCLR |= 1 << 0; //Set latch pin low
	
	SPIC.CTRL |= SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc; //Enable SPI, select as master, Mode 0 SPI
	SPIC.INTCTRL |= SPI_INTLVL_OFF_gc; //turn off interrupts. for now.
	
}

void SPI_blankAndLatch(void){
		PORTC.DIRSET |= 1 << 0;
		PORTC.DIRCLR |= 1 << 0;
}
	