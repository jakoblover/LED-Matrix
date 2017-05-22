/*
 * Print.h
 *
 * Created: 21-May-17 11:18:06 AM
 *  Author: Jakob
 */ 


#ifndef PRINT_H_
#define PRINT_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

#ifndef CharacterSize
#define CharacterSize(x)			( x * 8 )
#define TEXTLENGTH					CharacterSize(20) + 8
#endif

///////////////////// Extern Character Definitions ( located in ProgmemData.h ) ////////////////////////////
extern const char CharacterOmega[] PROGMEM;
///////////////////////////////////////////////////////////////////////////////////////////////////////////











void	Print_init					(void);
void	Print_emptyBuffer			(void);
void	Print_outputBuffer			(void);
void	Print_character				(void);
void	Print_changeColor			(void);



#endif /* PRINT_H_ */