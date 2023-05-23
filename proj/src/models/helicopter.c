#include <lcom/lcf.h>

#include "helicopter.h"
#include "Bullet.h"
#include "player.h"
#include "devices/i8042.h"


typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t old_x;
  uint16_t old_y;
  uint8_t hp;
} Helicopter;



void movement(Helicopter * heli, Player* player){
  if(player->x > heli->x){
    heli->old_x=heli->x;
    heli->x++;
  }
  else{
    heli->old_x=heli->x;
    heli->x--;
  }
}

void shooting(Helicopter* heli ,Player* player);
