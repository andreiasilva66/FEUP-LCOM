#ifndef _LCOM_CANVAS_H_
#define _LCOM_CANVAS_H_

#include "../devices/video.h"
#include "../models/player.h"
#include "../models/helicopter.h"
#include "../devices/values.h"


int (canvas_draw_arena)(uint32_t new_arena_color, uint32_t new_walls_color);
int (canvas_refresh)(Player* obj, Helicopter* heli);
int (canvas_draw_menu)(Mouse *mouse);
int (canvas_draw_instructions)(Mouse *mouse);
int (canvas_draw_game_over)(Mouse *mouse);
void (draw_background)(bool day);
void draw_mouse(Mouse *mouse);
int draw_numbers(uint8_t number,uint8_t x, uint8_t y);
int draw_month(uint8_t month, uint8_t x, uint8_t y);
int draw_double_dots(uint8_t x, uint8_t y);
int draw_date(uint8_t hours, uint8_t minutes, uint8_t day, uint8_t month);



#endif // _LCOM_CANVAS_H_
