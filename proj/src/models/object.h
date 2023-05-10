#ifndef _LCOM_OBJECT_H_
#define _LCOM_OBJECT_H_

#include <stdint.h>

#include "../devices/keyboard.h"

#define MOVE_UP(scancodes) (scancodes[0] == 0x11 || (scancodes[0] == 0xE0 && scancodes[1] == 0x48))
#define MOVE_DOWN(scancodes) (scancodes[0] == 0x1f || (scancodes[0] == 0xE0 && scancodes[1] == 0x50))
#define MOVE_LEFT(scancodes) (scancodes[0] == 0x1e || (scancodes[0] == 0xE0 && scancodes[1] == 0x4b))
#define MOVE_RIGHT(scancodes) (scancodes[0] == 0x20 || (scancodes[0] == 0xE0 && scancodes[1] == 0x4d))

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t old_x;
    uint16_t old_y;
    uint8_t frame;
} Object;

void moveUp(Object* obj, uint16_t speed);
void moveDown(Object* obj, uint16_t speed);
void moveLeft(Object* obj, uint16_t speed);
void moveRight(Object* obj, uint16_t speed);
void jump(Object* obj, uint16_t speed);

void process_scancode(Object* obj, uint8_t* data);
void process_packet(Object* obj, struct packet *pp, Mouse *mouse);
void update_pos(Object* obj);

#endif // _LCOM_OBJECT_H_
