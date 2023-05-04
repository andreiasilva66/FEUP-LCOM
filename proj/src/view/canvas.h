#ifndef _LCOM_CANVAS_H_
#define _LCOM_CANVAS_H_

#include "../devices/video_card/video.h"
#include "../models/object.h"

int (canvas_draw_arena)(uint32_t new_arena_color, uint32_t new_walls_color);
int (canvas_refresh)(Object* obj, uint16_t old_x, uint16_t old_y);

#endif // _LCOM_CANVAS_H_
