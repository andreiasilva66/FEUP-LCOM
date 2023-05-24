#ifndef _LCOM_PLAYER_H_
#define _LCOM_PLAYER_H_
#include <lcom/lcf.h>
#include <stdint.h>

#include "../devices/keyboard.h"


#define MOVE_UP(scancodes) (scancodes[0] == 0x11 || (scancodes[0] == 0xE0 && scancodes[1] == 0x48))
#define MOVE_DOWN(scancodes) (scancodes[0] == 0x1f || (scancodes[0] == 0xE0 && scancodes[1] == 0x50))
#define MOVE_LEFT(scancodes) (scancodes[0] == 0x1e || (scancodes[0] == 0xE0 && scancodes[1] == 0x4b))
#define MOVE_RIGHT(scancodes) (scancodes[0] == 0x20 || (scancodes[0] == 0xE0 && scancodes[1] == 0x4d))

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
#endif // _LCOM_PLAYER_H_
