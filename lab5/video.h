#ifndef _LCOM_VIDEO_H
#define _LCOM_VIDEO_H

#include <lcom/lcf.h>

// keyboard loop
int(keyboard_loop)();

// graphic
void *(vg_init)(uint16_t mode);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int (vg_draw_xpm) (xpm_map_t xpm, uint16_t x, uint16_t y);
int (vg_update)(xpm_map_t xpm, uint16_t old_x, uint16_t old_y, uint16_t new_x, uint16_t new_y);

#endif
