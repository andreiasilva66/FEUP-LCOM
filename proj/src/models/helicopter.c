#include <lcom/lcf.h>

#include "helicopter.h"
#include "Bullet.h"
#include "object.h"
#include "devices/i8042.h"


typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t old_x;
  uint16_t old_y;
  uint8_t hp;
} Helicopter;



void movement(Object* obj){


}

void shooting(Object* obj, Bullet)
