#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"

typedef struct{
  uint16_t x;
  uint16_t y;
} Mouse;


int(kbc_subscribe_int)(uint8_t *bit_no);

int(kbc_unsubscribe_int)();

int(kbc_get_status)(uint8_t *st);

int(kbc_read_out_buffer)(uint8_t *data, uint8_t * st);

int(kbc_send_cmd)(uint8_t port, uint8_t cmd);

int(kbc_reenable_int)();

int(mouse_subscribe_int)(uint8_t *bit_no);

int(mouse_unsubscribe_int)();

int(mouse_write_cmd)(uint8_t cmd); 

int (mouse_parse_packet)(struct packet *pp);

int (mouse_get_data)(struct packet *pp);

int(kbc_get_scancode)(uint8_t* data);

int check_status(uint8_t st);

bool leftKeyPressed();

bool rightKeyPressed();

void pressLeftKey(bool is_pressed);

void pressRightKey(bool is_pressed);

#endif

