/*
 * SPI.h
 *
 * Created: 19-May-17 10:05:47 PM
 *  Author: Jakob
 */ 

#include <avr/pgmspace.h>

#ifndef SPI_H_
#define SPI_H_

extern const uint16_t BrightnessLookUpTable[256] PROGMEM;

void SPI_init(void);
void SPI_update(void);




#endif /* SPI_H_ */