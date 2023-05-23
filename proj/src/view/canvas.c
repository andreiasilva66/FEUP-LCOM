#include <lcom/lcf.h>

#include "canvas.h"

uint32_t walls_color;
uint32_t arena_color;

int (canvas_draw_arena)(uint32_t new_arena_color, uint32_t new_walls_color){
    arena_color = new_arena_color;
    walls_color = new_walls_color;

    return vg_draw_rectangle(0, 0, 1230, 50, walls_color) ||
        vg_draw_rectangle(1230, 0, 50, 1024, walls_color) ||
        vg_draw_rectangle(0, 0, 50, 1024, walls_color) ||
        vg_draw_rectangle(50, 974, 1180, 50, walls_color) ||
        vg_draw_rectangle(50, 50, 1180, 924, arena_color);
}

int (canvas_refresh)(Player* obj, Helicopter* heli){
    if (obj->x == obj->old_x && obj->y == obj->old_y) return 0;

    int flag = vg_draw_rectangle(obj->old_x, obj->old_y, 50, 50, arena_color);
    if (flag) return flag;

    switch (obj->frame%3)
    {
    case 0:
        vg_draw_rectangle(obj->x, obj->y, 50, 50, 0x000F);
        break;
    
    case 1:
        vg_draw_rectangle(obj->x, obj->y, 50, 50, 0x0F00);
        break;

    case 2:
        vg_draw_rectangle(obj->x, obj->y, 50, 50, 0xF000);
        break;

    default:
        vg_draw_rectangle(obj->x, obj->y, 50, 50, 0x000F);
        break;
    }

    vg_draw_rectangle(heli->old_x, heli->old_y, 100, 50, arena_color);

    return vg_draw_rectangle(heli->x, heli->y, 100, 50, 0x000F);
    
}
