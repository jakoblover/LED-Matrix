#include "Print.h"
#include "Display.h"

volatile uint8_t	print_CharacterBlueVal	=	0	;
volatile uint8_t	print_CharacterGreenVal	=	200	;
volatile uint8_t	print_CharacterRedVal	=	0	;
volatile uint8_t	print_CharacterChangeCounter = 0;

uint8_t				print_textBuffer[TEXTLENGTH];


void Print_init(void)
{
	Print_emptyBuffer();
}

void Print_emptyBuffer(void)
{
	for ( uint8_t i = 0; i < TEXTLENGTH ; ++i )
	print_textBuffer[i] = 0;
}


void Print_outputBuffer(void)
{
	uint8_t rowCounter = 0;
	for ( uint8_t i = 0 ; i < 8 ; ++i)
	{
		for ( uint8_t j = 0 ; j < 8 ; ++j)
		{
			if ( print_textBuffer[i] & ( 1 << j ) )
			{
				Display_setChannelBrightness(rowCounter,	j*3,		print_CharacterRedVal);
				Display_setChannelBrightness(rowCounter,	j*3 + 1,	print_CharacterGreenVal);
				Display_setChannelBrightness(rowCounter,	j*3 + 2,	print_CharacterBlueVal);
			}
		}
		rowCounter++;
	}
}





void Print_character(void)
{
	uint8_t counter = 0;
	for ( uint8_t i = 0; i < 8 ; ++i)
	{
		print_textBuffer[i] = pgm_read_byte ( & ( CharacterOmega[counter++] ) );
	}
	//TODO : Find a sensible way to introduce a new character to an established string...
}