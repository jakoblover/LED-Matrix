#include "Print.h"
#include "Display.h"
//#include "ProgmemData.h"

volatile uint8_t	print_CharacterBlueVal	=	0	;
volatile uint8_t	print_CharacterGreenVal	=	255	;
volatile uint8_t	print_CharacterRedVal	=	0	;
volatile uint8_t	print_CharacterChangeCounter = 0;

uint8_t				print_textBuffer[8];


void Print_init(void)
{
	Print_emptyBuffer();
}

void Print_emptyBuffer(void)
{
	for ( uint8_t i = 0; i < 8 ; ++i )
	print_textBuffer[i] = 0;
}

void Print_changeColor( void )
{
		if(print_CharacterRedVal == 255){
			print_CharacterGreenVal = 255;
			print_CharacterRedVal = 0;
		}
		else if(print_CharacterGreenVal == 255){
			print_CharacterBlueVal = 255;
			print_CharacterGreenVal = 0;
		}
		else if(print_CharacterBlueVal == 255){
			print_CharacterRedVal = 255;
			print_CharacterBlueVal = 0;
		}
		else print_CharacterRedVal = 255;
	
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
			else{
				Display_setChannelBrightness(rowCounter,	j*3,		0);
				Display_setChannelBrightness(rowCounter,	j*3 + 1,	0);
				Display_setChannelBrightness(rowCounter,	j*3 + 2,	0);
			}
		}
		rowCounter++;
	}
}





void Print_character(void)
{
	static uint16_t frame_counter = 0;
	uint8_t counter = 0;
	for ( uint8_t i = 0; i < 8 ; ++i)
	{
		print_textBuffer[i] = pgm_read_byte ( & ( IMAGES[frame_counter][counter++] ) );
	}
	++frame_counter;
	if(frame_counter == 19){
		frame_counter = 0;
		Print_changeColor();
	}
	//TODO : Find a sensible way to introduce a new character to an established string...
}