#include <lcom/lcf.h>

#include "object.h"
#include "devices/i8042.h"
#include "bullet.h"

extern bool jumping;
bool jump_down = false;
int y_ini;
extern u_int32_t n_bullets;

void jump(Object* obj, uint16_t speed){

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

void moveUp(Object* obj, uint16_t speed){

    if(obj->y - speed <= 50){
        obj->y -= (obj->y - 50);
    } else {
        obj->y -= speed;
    }
}

void moveDown(Object* obj, uint16_t speed){
    if(obj->y + 50 + speed >= 974){
        obj->y += (974 - obj->y - 50);
    } else {
        obj->y += speed;
    }
}

void moveLeft(Object* obj, uint16_t speed){
    
    if(obj->x - speed <= 50){
        obj->x -= (obj->x - 50);
    }else{
        obj->x -= speed;
    }
}

void moveRight(Object* obj, uint16_t speed){
    
    if(obj->x + 50 + speed >= 1230-50){
        obj->x += (1230 - obj->x - 50);
    } else {
        obj->x += speed;
    }
}

void process_scancode(Object* obj, uint8_t* scancodes){
    
    obj->frame++;

    if (MOVE_UP(scancodes)){
        if(jumping)
            return;
        jumping=true;
        y_ini=obj->y;
        //moveUp(obj, 10);
    }
    else if (MOVE_DOWN(scancodes)){
        moveDown(obj, 10);
    }
    else if (MOVE_LEFT(scancodes)){
        moveLeft(obj, 10);
    }
    else if (MOVE_RIGHT(scancodes)){
        moveRight(obj, 10);
    }

}

void draw_mouse(Mouse *mouse){
    uint32_t arena_color = 0xFFF0;
    if(mouse->x == mouse->old_x && mouse->y == mouse->old_y) return;

    if (mouse->old_x!=0 || mouse->old_y!=0){
        vg_draw_rectangle(mouse->old_x, mouse->old_y, 20, 20, arena_color);
    }
    
    vg_draw_rectangle(mouse->x, mouse->y, 20, 20, 0x000);
}

void process_packet(Object* obj, struct packet *pp, Mouse *mouse){
    if(pp->lb){
        player_create_bullet(obj,pp, mouse);
    }
    draw_mouse(mouse);
    
}

void update_pos(Object* obj){
    obj->old_x=obj->x;
    obj->old_y=obj->y;
}





