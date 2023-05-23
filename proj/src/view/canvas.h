#ifndef _LCOM_CANVAS_H_
#define _LCOM_CANVAS_H_

#include "../devices/video.h"
#include "../models/player.h"
#include "../models/helicopter.h"

int (canvas_draw_arena)(uint32_t new_arena_color, uint32_t new_walls_color);
int (canvas_refresh)(Player* obj, Helicopter* heli);

#endif // _LCOM_CANVAS_H_
