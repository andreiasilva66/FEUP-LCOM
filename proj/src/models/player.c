#include <lcom/lcf.h>

#include "bullet.h"
#include "devices/i8042.h"
#include "bullet.h"
#include "xpm/xpm_sprites.h"
#include "xpm/xpm_id.h"
#include "devices/video.h"
#include "xpm/xpm_sprites.h"

bool jumping = false;
bool jump_down = false;
int y_ini;
int y_ground = PLAYER_INI_Y;

extern u_int32_t n_bullets;

void jump(Player *obj, uint16_t speed) {

  if (jump_down) {
    if (obj->y == y_ground || check_collision_player(obj, &platforms[4], jump_down)) {
      jumping = false;
      jump_down = false;
      return;
    }
    moveDown(obj, 4);
  }
  else {
    if (obj->y == y_ini - 120) {
      jump_down = true;
      return;
    }
    moveUp(obj, 4);
  }
}

void moveUp(Player *obj, uint16_t speed) {

  if (obj->y - speed <= 50) {
    obj->y -= (obj->y - 50);
  }
  else {
    obj->y -= speed;
  }
}

void moveDown(Player *obj, uint16_t speed) {
  if (obj->y + 50 + speed >= 974) {
    obj->y += (974 - obj->y - 50);
  }
  else {
    obj->y += speed;
  }
}


void moveLeft(Player *obj, uint16_t speed) {

  if (jumping == false && obj->y != y_ground && !check_collision_player(obj, &platforms[4], jump_down)) {
    jumping = true;
    jump_down = true;
  }
  else if (obj->x - speed <= 50) {
    obj->x -= (obj->x - 50);
  }

  else {
    obj->x -= speed;
  }
}

void moveRight(Player *obj, uint16_t speed) {

     if (jumping ==false && obj->y != y_ground && !check_collision_player(obj, &platforms[4], jump_down)) {
    jumping = true;
    jump_down = true;
  }

  else if (obj->x + 50 + speed > 1230) {
    obj->x += (1230 - obj->x - 50);
  }
  else {
    obj->x += speed;
  }} 

void process_scancode(Player* obj, uint8_t* scancodes){

  switch (*scancodes) {
    case MOVE_RIGHT_MAKE:
      pressRightKey(true);
      break;

    case MOVE_LEFT_MAKE:
      pressLeftKey(true);
      break;

    case MOVE_UP_MAKE:
      if (jumping)
        break;
      jumping = true;
      y_ini = obj->y;
      break;

    case MOVE_RIGHT_BREAK:
      pressRightKey(false);
      break;

    case MOVE_LEFT_BREAK:
      pressLeftKey(false);
      break;

    default:
      break;
  }
}


void process_packet(Player *player, struct packet *pp, Mouse *mouse) {
  if (pp->lb) {
    player_create_bullet(player, pp, mouse);
  }
}

void draw_hp_bar(uint8_t hp) {
    switch (hp)
    {
    case 0:
      vg_draw_xpm(HP_0,40, Y_RESOLUTION-50);
      
      break;
    case 20:
      vg_draw_xpm(HP_20,40, Y_RESOLUTION-50);
     
      break;
    case 40:
      vg_draw_xpm(HP_40,40, Y_RESOLUTION-50);
     
      break;
    case 60:
      vg_draw_xpm(HP_60,40, Y_RESOLUTION-50);
     
      break;
    case 80:
      vg_draw_xpm(HP_80,40, Y_RESOLUTION-50);
     
      break;
    case 100:
      vg_draw_xpm(HP_100,40, Y_RESOLUTION-50);
     
      break;
    default:
      break;
    }

}

void draw_player(Player * player){
    if(player->hp == 0){
        vg_draw_xpm(SOLDIER_DEAD_XPM_ID, player->x, player->y);
        return;
    }
    switch (player->frame%3)
    {
    case 0:
        vg_draw_xpm(SOLDIER1_XPM_ID,player->x, player->y);
        //vg_draw_rectangle(player->x, player->y, 50, 50, 0x000F);
        break;
    
    case 1:
        vg_draw_xpm(SOLDIER2_XPM_ID, player->x, player->y);
        //vg_draw_rectangle(player->x, player->y, 50, 50, 0x0F00);
        break;

    case 2:
        vg_draw_xpm(SOLDIER3_XPM_ID, player->x, player->y);
        //vg_draw_rectangle(player->x, player->y, 50, 50, 0xF000);
        break;

    default:
        break;
    }    



}

void player_update_mov(Player *player) {
  if (jumping) {
    jump(player, 5);
  }
  if (leftKeyPressed()) {
    moveLeft(player, 5);
  }
  else if (rightKeyPressed()) {
    moveRight(player, 5);
  }
}

int check_collision_player(Player *player, Platform platform[], bool jump_down) {
  for (int i = 0; i < 4; i++) {
    Platform *platform = &platforms[i];
    uint16_t player_left = player->x;
    uint16_t player_right = player->x + PLAYER_WIDTH;
    uint16_t player_top = player->y;
    uint16_t player_bottom = player->y + PLAYER_HEIGHT;

    uint16_t platform_left = platform->x;
    uint16_t platform_right = platform->x + platform->width;
    uint16_t platform_top = platform->y;
    // uint16_t platform_bottom = platform->y + platform->height;

    if ((player_left < platform_right && player_right > platform_left && player_bottom > platform_top) && !(player_top > platform_top - PLAYER_HEIGHT + 4 && player_left < platform_right && player_right > platform_left)) {
      // Player collided with the current platform
      return 1;
    }
  }
  jump_down = true;
  // Player did not collide with any platform
  return 0;
}



