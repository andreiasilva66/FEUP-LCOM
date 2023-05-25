#include <lcom/lcf.h>

#include "bullet.h"
#include "devices/i8042.h"
#include "bullet.h"
#include "xpm/xpm2.h"
#include "devices/video.h"

bool jumping = false;
bool jump_down = false;
int y_ini;

extern u_int32_t n_bullets;

void jump(Player* obj, uint16_t speed){

    if(jump_down){
        if(obj->y == y_ini){
            jumping = false;
            jump_down = false;
            return;
        }
        moveDown(obj,4);
    }
    else{
        if(obj->y == y_ini - 80){
            jump_down= true;
            return;
        }
        moveUp(obj,4);
    }
}

void moveUp(Player* obj, uint16_t speed){

    if(obj->y - speed <= 50){
        obj->y -= (obj->y - 50);
    } else {
        obj->y -= speed;
    }
}

void moveDown(Player* obj, uint16_t speed){
    if(obj->y + 50 + speed >= 974){
        obj->y += (974 - obj->y - 50);
    } else {
        obj->y += speed;
    }
}

void moveLeft(Player* obj, uint16_t speed){
    
    if(obj->x - speed <= 50){
        obj->x -= (obj->x - 50);
    }else{
        obj->x -= speed;
    }
}

void moveRight(Player* obj, uint16_t speed){
    
    if(obj->x + 50 + speed >= 1230-50){
        obj->x += (1230 - obj->x - 50);
    } else {
        obj->x += speed;
    }
}

void process_scancode(Player* obj, uint8_t* scancodes){

    switch (*scancodes)
    {
    case MOVE_RIGHT_MAKE:
        pressRightKey(true);
        break;

    case MOVE_LEFT_MAKE:
        pressLeftKey(true);
        break;

    case MOVE_UP_MAKE:
        if(jumping)
            break;
        jumping=true;
        y_ini=obj->y;
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

void draw_mouse(Mouse *mouse){
    
    vg_draw_rectangle(mouse->x, mouse->y, 20, 20, 0xFF0000);
}

void process_packet(Player* player, struct packet *pp, Mouse *mouse){
    if(pp->lb){
        player_create_bullet(player,pp, mouse);
    }
    
}

void draw_hp_bar(uint8_t hp){

    vg_draw_rectangle(40,Y_RESOLUTION - 20, 100, 50,0xFFF0);
    vg_draw_rectangle(40, Y_RESOLUTION - 20, hp, 50,0x00FF00);

}

void draw_player(Player * player){
    if(player->hp == 0){
        vg_draw_xpm(soldado_morto, 0, player->x, player->y);
        return;
    }

    switch (player->frame%3)
    {
    case 0:
        vg_draw_xpm(soldado1, 0,player->x, player->y);
        //vg_draw_rectangle(player->x, player->y, 50, 50, 0x000F);
        break;
    
    case 1:
        vg_draw_xpm(soldado3, 0, player->x, player->y);
        //vg_draw_rectangle(player->x, player->y, 50, 50, 0x0F00);
        break;

    case 2:
        vg_draw_xpm(soldado2, 0, player->x, player->y);
        //vg_draw_rectangle(player->x, player->y, 50, 50, 0xF000);
        break;

    default:
        vg_draw_rectangle(player->x, player->y, 50, 50, 0x000F);
        break;
    }    



}


void player_update_mov(Player *player){
    if(jumping){
        jump(player,5);
    }
    if(leftKeyPressed()){
        moveLeft(player, 5);
    }
    else if(rightKeyPressed()){
        moveRight(player, 5);
    }
}


