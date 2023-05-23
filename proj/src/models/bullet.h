#ifndef _LCOM_BULLET_H_
#define _LCOM_BULLET_H_
#include <lcom/lcf.h>
#include <stdint.h>
#include "object.h"
#include "devices/keyboard.h"

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t old_x;
    uint16_t old_y;
    int16_t vx;
    int16_t vy;
    bool in_game;
} Bullet;


int (draw_bullet)(Bullet* bullet);
void (initialize_bullets)();
void heli_update_bullets();
void player_update_bullets();
void player_create_bullet(Object *obj,struct packet *pp, Mouse *mouse);

#endif // _LCOM_BULLET_H_
