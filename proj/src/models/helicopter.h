#ifndef _LCOM_HELICOPTER_H_
#define _LCOM_HELICOPTER_H_

#include <stdint.h>

#include "devices/keyboard.h"
#include "player.h"

typedef struct {
  uint16_t x;
  uint16_t y;
  uint8_t hp;
  bool alive;
} Helicopter;

void update_heli_move(Helicopter* heli);

void helicopter_shoot(Helicopter* heli ,Player* player);

void draw_helicopter(Helicopter* heli);

void destroy_helicopter(Helicopter * heli);

void init_helicopter(Helicopter * heli);


#endif // _LCOM_HELICOPTER_H_
