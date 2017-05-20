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

void Display_setChannelBrightness(int row, int channel, uint8_t brightness);
uint8_t Display_getChannelBrightness(int row, int channel);



#endif /* DISPLAY_H_ */