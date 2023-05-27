#ifndef _LCOM_PLAYER_H_
#define _LCOM_PLAYER_H_
#include <lcom/lcf.h>
#include <stdint.h>

#include "../devices/keyboard.h"
#include "../devices/values.h"
#include "platforms.h"



#define MOVE_UP_MAKE 0x11
#define MOVE_DOWN_MAKE 0x1f 
#define MOVE_LEFT_MAKE 0x1e 
#define MOVE_RIGHT_MAKE 0x20
#define MOVE_UP_BREAK 0x91
#define MOVE_DOWN_BREAK 0x9f 
#define MOVE_LEFT_BREAK 0x9e 
#define MOVE_RIGHT_BREAK 0xa0 

typedef struct {
    uint16_t x;
    uint16_t y;
    uint8_t hp; // between 0 and 100 
    uint8_t frame;
} Player;

void moveUp(Player* obj, uint16_t speed);
void moveDown(Player* obj, uint16_t speed);
void moveLeft(Player* obj, uint16_t speed);
void moveRight(Player* obj, uint16_t speed);
void jump(Player* obj, uint16_t speed);

void process_scancode(Player* obj, uint8_t* data);
void process_packet(Player* obj, struct packet *pp, Mouse *mouse);
void draw_mouse(Mouse *mouse);
void draw_hp_bar(uint8_t hp);
void draw_player(Player * player);
void player_update_mov(Player *player);
int check_collision_player(Player *player, Platform platform[], bool jump_down);

#endif // _LCOM_PLAYER_H_
