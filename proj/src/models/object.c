#include <lcom/lcf.h>

#include "object.h"

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
    if(obj->x + 50 + speed >= 1230){
        obj->x += (1230 - obj->x - 50);
    } else {
        obj->x += speed;
    }
}

void process_scancode(Object* obj, uint8_t* scancodes){
    

    if (MOVE_UP(scancodes)){
        moveUp(obj, 10);
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
