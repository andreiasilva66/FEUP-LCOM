#ifndef _LCOM_VIDEO_H
#define _LCOM_VIDEO_H

#include <lcom/lcf.h>



// graphic
void (change_buffer)();
int (set_frame_buffer)(uint16_t mode);
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int (vg_load_xpm)();
int (vg_draw_xpm) (uint8_t id, uint16_t x, uint16_t y);
// int (vg_update)(xpm_map_t xpm, uint16_t old_x, uint16_t old_y, uint16_t new_x, uint16_t new_y);
void free_buffer();


#endif
