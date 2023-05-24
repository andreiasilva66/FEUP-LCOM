#include <lcom/lcf.h>
#include <math.h>

#include "bullet.h"
#include "game/menu.h"
#include "view/canvas.h"

extern GameState game_state;

uint32_t n_player_bullets=0;
uint32_t n_heli_bullets=0;


Bullet player_bullets[BULLETS];
Bullet heli_bullets[BULLETS];


void (initialize_bullets)(){
    Bullet bullet = {0,0,0,0,0,0,false};
    for(int i = 0 ; i<BULLETS ; i++){
        player_bullets[i]=bullet;
        heli_bullets[i]=bullet;
    }
}

int (draw_bullet)(Bullet *bullet){
    
    uint32_t arena_color = 0xFFF0;

    if (bullet->old_x!=0 || bullet->old_y!=0){
        int flag = vg_draw_rectangle(bullet->old_x, bullet->old_y, BLTS_WIDTH, BLTS_HEIGHT, arena_color);
        if (flag) return flag;
    }

    return vg_draw_rectangle(bullet->x, bullet->y, 20, 20, 0xFFF);
    
}

void player_update_bullets(Helicopter * heli){
    
    for(unsigned i = 0;i<BULLETS;i++){
        if(!player_bullets[i].in_game)
            continue;
        player_bullets[i].old_x=player_bullets[i].x;
        player_bullets[i].old_y=player_bullets[i].y;
        player_bullets[i].x += player_bullets[i].vx;
        player_bullets[i].y += player_bullets[i].vy;
        if(player_bullets[i].y<=50 || player_bullets[i].y >= Y_RESOLUTION-50 || player_bullets[i].x <= 50 || player_bullets[i].x >= X_RESOLUTION-BLTS_WIDTH){
            vg_draw_rectangle(player_bullets[i].old_x, player_bullets[i].old_y, 20, 20, 0xFFF0);
            player_bullets[i].in_game=false;
            return;
    }
    draw_bullet(&player_bullets[i]);
    verify_heli_collision(heli, &player_bullets[i]);
    }
}

void player_create_bullet( Player* obj,struct packet *pp, Mouse *mouse){

    if(n_player_bullets == BULLETS)
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

void heli_create_bullet( Helicopter* obj, Player* target){

    if(n_heli_bullets == BULLETS)
        n_heli_bullets=0;

    int delta_x = target->x - obj->x;
    int delta_y = target->y - obj->y;
    double alpha = atan2((double)delta_y, (double)delta_x);
    heli_bullets[n_heli_bullets].x = obj->x;
    heli_bullets[n_heli_bullets].y = obj->y;
    heli_bullets[n_heli_bullets].old_x = 0;
    heli_bullets[n_heli_bullets].old_y = 0;
    heli_bullets[n_heli_bullets].in_game = true;
    heli_bullets[n_heli_bullets].vx = (int16_t)round(cos(alpha) * 5.0);
    heli_bullets[n_heli_bullets].vy = (int16_t)round(sin(alpha) * 5.0);  

    n_heli_bullets++;
}
 

void heli_update_bullets(Player * player){
    for(unsigned i = 0;i<BULLETS;i++){
        if(!heli_bullets[i].in_game)
            continue;
        heli_bullets[i].old_x=heli_bullets[i].x;
        heli_bullets[i].old_y=heli_bullets[i].y;
        heli_bullets[i].x += heli_bullets[i].vx;
        heli_bullets[i].y += heli_bullets[i].vy;
        if(heli_bullets[i].y<=50 || heli_bullets[i].y >= Y_RESOLUTION-50 || heli_bullets[i].x <= 50 || heli_bullets[i].x >= X_RESOLUTION-BLTS_WIDTH){
            vg_draw_rectangle(heli_bullets[i].old_x, heli_bullets[i].old_y, BLTS_WIDTH, BLTS_HEIGHT, 0xFFF0);
            heli_bullets[i].in_game=false;
            return;
        }
        draw_bullet(&heli_bullets[i]);
        verify_player_collision(player, &heli_bullets[i]);
    }
}

void verify_player_collision (Player * player, Bullet* bullet){

    if( bullet->x + BLTS_WIDTH >= player->x && bullet->x <= player->x + PLAYER_WIDTH && bullet->y + BLTS_HEIGHT >= player->y && bullet->y <= player->y + BLTS_WIDTH){
        bullet->in_game = false;
        player->hp -= HELI_BLTS_DMG;
        draw_hp_bar(player->hp);
        printf("player: %d \n", player->hp);
    }
    if(player->hp == 0 || player->hp>100){
        game_state = GAMEOVER;
    }

    
}

void verify_heli_collision (Helicopter * heli, Bullet* bullet){

    if( bullet->x + BLTS_WIDTH >= heli->x && bullet->x <= heli->x + HELI_WIDTH && bullet->y + BLTS_HEIGHT >= heli->y && bullet->y <= heli->y + HELI_HEIGHT){
        bullet->in_game = false;
        heli->hp -= PLAYER_BLTS_DMG;
        printf("heli: %d \n", heli->hp);
    }
}




