#ifndef _LCOM_BULLET_H_
#define _LCOM_BULLET_H_
#include <lcom/lcf.h>
#include <stdint.h>
#include "player.h"
#include "helicopter.h"
#include "devices/values.h"
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
void heli_update_bullets(Player * player);
void player_update_bullets(Helicopter * heli);
void player_create_bullet( Player* obj,struct packet *pp, Mouse *mouse);
void heli_create_bullet( Helicopter* obj,Player* target);
void verify_player_collision (Player * player, Bullet* bullet);
void verify_heli_collision (Helicopter * heli, Bullet* bullet);

#endif // _LCOM_BULLET_H_
