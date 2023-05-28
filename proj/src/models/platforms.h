#ifndef _LCOM_PLATFORMS_H_
#define _LCOM_PLATFORMS_H_

#include <stdint.h>

#define N_PLATFORMS 4


typedef struct {
uint16_t x; 
uint16_t y;
uint16_t width;
uint16_t height;
} Platform;

Platform platforms[N_PLATFORMS];


void initialize_platforms();
void platforms_location(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint8_t number);
void draw_platforms();

#endif
