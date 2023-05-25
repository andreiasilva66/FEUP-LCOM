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
    int16_t vx;
    int16_t vy;
    bool in_game;
} Bullet;

void (initialize_bullets)();

// draw

int (draw_bullet)(Bullet* bullet);
void draw_c_bullets();


// helicopter

void heli_update_bullets(Player * player);
void heli_create_bullet( Helicopter* obj,Player* target);
void verify_heli_collision (Helicopter * heli, Bullet* bullet);


// player

void player_update_bullets(Helicopter * heli);
void player_create_bullet( Player* obj,struct packet *pp, Mouse *mouse);
void verify_player_collision (Player * player, Bullet* bullet);


#endif // _LCOM_BULLET_H_
