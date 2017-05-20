/*
 * SPI.h
 *
 * Created: 19-May-17 10:05:47 PM
 *  Author: Jakob
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#ifndef SPI_H_
#define SPI_H_

void SPI_init(void);
void SPI_update(void);
void SPI_blankAndLatch(void);
void SPIC_INT_vect (void);



#endif /* SPI_H_ */