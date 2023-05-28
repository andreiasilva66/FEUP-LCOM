#ifndef _LCOM_CANVAS_H_
#define _LCOM_CANVAS_H_

#include "../devices/video.h"
#include "../models/player.h"
#include "../models/helicopter.h"
#include "../devices/values.h"


int (canvas_draw_menu)(Mouse *mouse);
int (canvas_draw_instructions)(Mouse *mouse);
int (canvas_draw_game_over)(Mouse *mouse);
void (draw_background)(bool day);
void draw_mouse(Mouse *mouse);
int draw_numbers(uint8_t number,uint16_t x, uint16_t y);
int draw_month(uint8_t month, uint16_t x, uint16_t y);
int draw_double_dots(uint16_t x, uint16_t y);
int draw_date(uint8_t hours, uint8_t minutes,uint8_t seconds, uint8_t day, uint8_t month);



#endif // _LCOM_CANVAS_H_
