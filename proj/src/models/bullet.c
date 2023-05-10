#include <lcom/lcf.h>

#include "bullet.h"


uint32_t n_bullets=0;
Bullet bullets [10];

int (draw_bullets)(Bullet *bullet){
    printf("desenha \n");
    uint32_t arena_color = 0xFFF0;

    if (bullet->x == bullet->old_x && bullet->y == bullet->old_y) return 0;

    if (bullet->old_x!=0 || bullet->old_y!=0){
        int flag = vg_draw_rectangle(bullet->old_x, bullet->old_y, 20, 20, arena_color);
        if (flag) return flag;
    }

    return vg_draw_rectangle(bullet->x, bullet->y, 20, 20, 0xFFFF);
    
}

void update_bullets(){
    printf("update \n");
    bullets[0].old_x=bullets[0].x;
    bullets[0].old_y=bullets[0].y;
    bullets[0].y-=1;
    if(bullets[0].y<10){
        n_bullets--;
        vg_draw_rectangle(bullets[0].old_x, bullets[0].old_y, 20, 20, 0xFFF0);
        return;
    }
    draw_bullets(&bullets[0]);
    printf("%d \n",bullets[0].y);
    printf("%d \n",bullets[0].old_y);
}

void create_bullet(Object* obj,struct packet *pp){
    printf("cria");
  Bullet bullet = {obj->x, obj->y, 0, 0};
  if(n_bullets == 10)
    return;
  bullets[n_bullets]=bullet;
  n_bullets++;

  draw_bullets(&bullet);
}
