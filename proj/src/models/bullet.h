#ifndef _LCOM_BULLET_H_
#define _LCOM_BULLET_H_

#include <stdint.h>
#include "object.h"

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t old_x;
    uint16_t old_y;
    //uint16_t traj;
} Bullet;

void update_bullets();
int (draw_bullets)();
void create_bullet(Object* obj,struct packet *pp);


#endif // _LCOM_BULLET_H_
