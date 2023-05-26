#include <lcom/lcf.h>

#include "helicopter.h"
#include "bullet.h"
#include "devices/video.h"


#include "devices/i8042.h"
bool isRight = true;
bool isGoingUp = true;
uint32_t heli_shoot_time = 60 * 2;

void update_heli_move(Helicopter* heli) {
  if(!heli->alive){
    destroy_helicopter(heli);
    return;
  }
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

void helicopter_shoot(Helicopter* heli ,Player* player){
  heli_create_bullet(heli,player);
}

void draw_helicopter(Helicopter* heli){
  if(!heli->alive){
    vg_draw_xpm(11, heli->x, heli->y);
  }
  else{
    vg_draw_xpm(1, heli->x, heli->y);
  }
  //vg_draw_rectangle(heli->x, heli->y, 100, 50, 0x000F);
}

void init_helicopter(Helicopter * heli){
  heli->x = HELI_INI_X;
  heli->y = HELI_INI_Y;
  heli->hp = 200;
  heli->alive = true;
}

void destroy_helicopter(Helicopter * heli){
  if(heli->y < Y_RESOLUTION){
    heli->y+=5;
  }
  else{
    init_helicopter(heli);
  }
}

void helicopter_add_difficulty(Helicopter * heli){
  heli->vx++;
  heli->vy++;
  if(heli_shoot_time > 30){
    heli_shoot_time -= 20;
  }
}

