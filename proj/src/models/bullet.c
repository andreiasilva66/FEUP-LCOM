
#include <lcom/lcf.h>
#include <math.h>

#include "bullet.h"
#include "player.h"

uint32_t n_player_bullets=0;
uint32_t n_heli_bullets=0;


Bullet player_bullets[10];
Bullet heli_bullets[10];


void (initialize_bullets)(){
    Bullet bullet = {0,0,0,0,0,0,false};
    for(int i = 0 ; i<10 ; i++){
        player_bullets[i]=bullet;
        heli_bullets[i]=bullet;
    }
}

int (draw_bullet)(Bullet *bullet){
    
    uint32_t arena_color = 0xFFF0;

    if (bullet->old_x!=0 || bullet->old_y!=0){
        int flag = vg_draw_rectangle(bullet->old_x, bullet->old_y, 20, 20, arena_color);
        if (flag) return flag;
    }

    return vg_draw_rectangle(bullet->x, bullet->y, 20, 20, 0xFFF);
    
}

void player_update_bullets(){
    
    for(unsigned i = 0;i<10;i++){
        if(!player_bullets[i].in_game)
            continue;
        player_bullets[i].old_x=player_bullets[i].x;
        player_bullets[i].old_y=player_bullets[i].y;
        player_bullets[i].x += player_bullets[i].vx;
        player_bullets[i].y += player_bullets[i].vy;
        if(player_bullets[i].y<=50 || player_bullets[i].y >= 1004-50 || player_bullets[i].x <= 50 || player_bullets[i].x >= 1230-20){
            vg_draw_rectangle(player_bullets[i].old_x, player_bullets[i].old_y, 20, 20, 0xFFF0);
            player_bullets[i].in_game=false;
            return;
    }
    draw_bullet(&player_bullets[i]);
    }
}

void player_create_bullet( Player* obj,struct packet *pp, Mouse *mouse){

    if(n_player_bullets == 10)
        return;

    int delta_x = mouse->x - obj->x;
    int delta_y = mouse->y - obj->y;
    double alpha = atan2((double)delta_y, (double)delta_x);
    player_bullets[n_player_bullets].x = obj->x;
    player_bullets[n_player_bullets].y = obj->y;
    player_bullets[n_player_bullets].old_x = 0;
    player_bullets[n_player_bullets].old_y = 0;
    player_bullets[n_player_bullets].in_game = true;
    player_bullets[n_player_bullets].vx = (int16_t)round(cos(alpha) * 5.0);
    player_bullets[n_player_bullets].vy = (int16_t)round(sin(alpha) * 5.0);  

    n_player_bullets++;
}

void heli_update_bullets(){
    for(unsigned i = 0;i<10;i++){
        if(!heli_bullets[i].in_game)
            continue;
        heli_bullets[i].old_x=heli_bullets[i].x;
        heli_bullets[i].old_y=heli_bullets[i].y;
        heli_bullets[i].x += heli_bullets[i].vx;
        heli_bullets[i].y += heli_bullets[i].vy;
        if(heli_bullets[i].y<=50 || heli_bullets[i].y >= 1004-50 || heli_bullets[i].x <= 50 || heli_bullets[i].x >= 1230-20){
            vg_draw_rectangle(heli_bullets[i].old_x, heli_bullets[i].old_y, 20, 20, 0xFFF0);
            heli_bullets[i].in_game=false;
            return;
    }
    draw_bullet(&heli_bullets[i]);
    }
}


