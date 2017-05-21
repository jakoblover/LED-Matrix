/*
 * Display.h
 *
 * Created: 19-May-17 10:32:24 PM
 *  Author: Jakob
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#define DISP_ROWS 8
#define DISP_CHANNELS 24

void Display_setChannelBrightness(uint8_t row, uint8_t channel, uint8_t brightness);
uint8_t Display_getChannelBrightness(uint8_t row, uint8_t channel);
void Display_clear(void);



#endif /* DISPLAY_H_ */