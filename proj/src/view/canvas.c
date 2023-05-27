#include <lcom/lcf.h>

#include "canvas.h"
#include "devices/video.h"
#include "devices/keyboard.h"
#include "xpm/xpm_id.h"

uint32_t walls_color;
uint32_t arena_color;


int (canvas_draw_menu)(Mouse *mouse){
    vg_draw_xpm(TITLE_XPM_ID, 310, 200);

    if(mouse->x >= 500 && mouse->x <=700 && mouse->y >= 400 && mouse->y <= 500){
        vg_draw_xpm(START_YES_XPM_ID,500,400);
        vg_draw_xpm(INSTRUCT_NO_XPM_ID,400, 600);
    }
    else if(mouse->x >= 400 && mouse->x <=750 && mouse->y >= 600 && mouse->y <= 680){
        vg_draw_xpm(START_NO_XPM_ID,500,400);
        vg_draw_xpm(INSTRUCT_YES_XPM_ID,400, 600);
    }
    else{
        vg_draw_xpm(START_NO_XPM_ID,500,400);
        vg_draw_xpm(INSTRUCT_NO_XPM_ID,400, 600);
    }

    return 0;
}

int (canvas_draw_instructions)(Mouse *mouse){
    vg_draw_xpm(TITLE_XPM_ID, 310, 200);
    vg_draw_xpm(INSTRUCTEXT_XPM_ID,400,400);
    if(mouse->x >= 450 && mouse->x <=650 && mouse->y >= 900 && mouse->y <= 1000){
        vg_draw_xpm(BACK_YES_XPM_ID,500, 900);
    }
    else{
        vg_draw_xpm(BACK_NO_XPM_ID,500, 900);
    }
    return 0;
}



int (canvas_draw_game_over)(Mouse *mouse){
    vg_draw_xpm(TITLE_XPM_ID, 310, 200);
    vg_draw_xpm(GAMEOVER_XPM_ID, 400, 400);
    if(mouse->x >= 400 && mouse->x <=750 && mouse->y >= 600 && mouse->y <= 700){
        vg_draw_xpm(PLAYAGAIN_YES_XPM_ID, 400, 600);
    }
    else{
        vg_draw_xpm(PLAYAGAIN_NO_XPM_ID, 400, 600);
    }
    return 0;
}

void (draw_background)(){
    vg_draw_xpm(BACKGROUND_DAY_XPM_ID,0,0);
}

void draw_mouse(Mouse *mouse){
    vg_draw_xpm(TARGET_XPM_ID, mouse->x-18, mouse->y-18);
}
