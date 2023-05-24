
#include "menu.h"
#include "view/canvas.h"
#include "models/bullet.h"
extern Player player;
extern Helicopter heli;
extern Bullet player_bullets[BULLETS];
extern Bullet heli_bullets[BULLETS];



extern GameState game_state; 

void restore_game_def(){

  //player
  player.x = PLAYER_INI_X; //subs pelos valores reais
  player.y = PLAYER_INI_Y;
  player.frame = 0;
  player.old_x = PLAYER_INI_X;
  player.old_y = PLAYER_INI_Y;
  player.hp = PLAYER_HP;

  heli.x = HELI_INI_X;
  heli.y = HELI_INI_Y;
  heli.old_x = HELI_INI_X;
  heli.old_y = HELI_INI_Y;
  heli.hp = HELI_HP;

  for(int i = 0; i< BULLETS; i++){
    heli_bullets[i].in_game=false;
    player_bullets[i].in_game=false;
  }
}

void menu_mouse(Mouse *mouse, struct packet *pp){
  switch (game_state)
  {
  case MAINMENU:
    main_menu_mouse(mouse, pp);
    break;

  case INSTRUCTIONS:
    instructions_mouse(mouse, pp);
    break;

  case MODE:
    mode_mouse(mouse, pp);
    break;

  case GAMEOVER:
    game_over_mouse(mouse, pp);
    break;

  default:
    break;
  }
}


void main_menu_mouse(Mouse *mouse, struct packet *pp){
  if(pp->lb){
    
      if(mouse->x >= MENU_POS_X && mouse->x <= MENU_POS_X + MENU_WIDTH && mouse->y >= MENU_POS_Y && mouse->y <= MENU_POS_Y + MENU_HEIGHT){
        game_state = GAME;
        canvas_draw_arena(0xFFF0, 0xF09F);
      }
      else if(mouse->x >= MENU_POS_X && mouse->x <=  MENU_POS_X + MENU_WIDTH && mouse->y >= MENU_DIST + MENU_POS_Y && mouse->y <= MENU_DIST + MENU_POS_Y + MENU_HEIGHT){
        game_state =  INSTRUCTIONS; 
        canvas_draw_instructions();
      }
      else if(mouse->x >= MENU_POS_X && mouse->x <= MENU_POS_X + MENU_WIDTH && mouse->y >= 2*MENU_DIST + MENU_POS_Y && mouse->y <= 2*MENU_DIST + MENU_POS_Y + MENU_HEIGHT){
        game_state =  MODE; 
        canvas_draw_mode();
      }

    }
}

void instructions_mouse(Mouse *mouse, struct packet *pp){
  if(pp->lb){
    if(mouse->x >= MENU_POS_X && mouse->x <= MENU_POS_X + MENU_WIDTH && mouse->y >= 2*MENU_DIST + MENU_POS_Y && mouse->y <= 2*MENU_DIST + MENU_POS_Y + MENU_HEIGHT){
          game_state =  MAINMENU; 
          canvas_draw_menu();
        }
  }
}

void mode_mouse(Mouse *mouse, struct packet *pp){
  if(pp->lb){
    if(mouse->x >= MENU_POS_X && mouse->x <= MENU_POS_X + MENU_WIDTH && mouse->y >= 2*MENU_DIST + MENU_POS_Y && mouse->y <= 2*MENU_DIST + MENU_POS_Y + MENU_HEIGHT){
          game_state =  MAINMENU; 
          canvas_draw_menu();
        }
  }
}

void game_over_mouse(Mouse *mouse, struct packet *pp){
  if(pp->lb){
    if(mouse->x >= MENU_POS_X && mouse->x <= MENU_POS_X + MENU_WIDTH && mouse->y >= MENU_DIST + MENU_POS_Y && mouse->y <= MENU_DIST + MENU_POS_Y + MENU_HEIGHT){
          game_state =  MAINMENU; 
          canvas_draw_menu();
          restore_game_def(); // bullets, player , helicopter
        }
  }
}


