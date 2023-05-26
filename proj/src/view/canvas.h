#ifndef _LCOM_CANVAS_H_
#define _LCOM_CANVAS_H_

#include "../devices/video.h"
#include "../models/player.h"
#include "../models/helicopter.h"
#include "../devices/values.h"


int (canvas_draw_arena)(uint32_t new_arena_color, uint32_t new_walls_color);
int (canvas_refresh)(Player* obj, Helicopter* heli);
int (canvas_draw_menu)();
int (canvas_draw_instructions)();
int (canvas_draw_mode)();
int (canvas_draw_game_over)();
void (draw_background)();

#endif // _LCOM_CANVAS_H_
