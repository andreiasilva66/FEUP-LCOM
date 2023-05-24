#include <lcom/lcf.h>

#include "helicopter.h"
#include "bullet.h"

#include "devices/i8042.h"
bool isRight = true;
bool isGoingUp = true;

void movement(Helicopter* heli) {
  if (isGoingUp) {
    heli->y++;
  } else {
    heli->y--;
  }

  if (heli->y >= 120) {
    isGoingUp = false;
  } else if (heli->y <= 100) {
    isGoingUp = true;
  }

  if (heli->x < 100 && !isRight) {
    heli->x++;
  } else if (heli->x > 900 && isRight) {
    heli->x--;
  } else {
    if (isRight) {
      heli->x++;
    } else {
      heli->x--;
    }
  }

  if (heli->x >= 900) {
    isRight = false;
  } else if (heli->x <= 100) {
    isRight = true;
  }
}

void shooting(Helicopter* heli ,Player* player){
  heli_create_bullet(heli,player);
}

void draw_helicopter(Helicopter* heli){
  vg_draw_rectangle(heli->x, heli->y, 100, 50, 0x000F);
}
