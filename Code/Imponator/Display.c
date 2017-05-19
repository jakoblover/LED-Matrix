/*
 * Display.c
 *
 * Created: 19-May-17 10:32:14 PM
 *  Author: Jakob
 */ 

#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Display.h"

static uint8_t DisplayData[8][24] = {{0}};

void Display_setChannelBrightness(int row, int channel, uint8_t brightness){
	DisplayData[row][channel] = brightness;
}

uint8_t Display_getChannelBrightness(int row, int channel){
	
	return DisplayData[row][channel];
}


