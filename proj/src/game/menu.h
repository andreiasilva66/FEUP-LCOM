#ifndef _LCOM_MENU_H_
#define _LCOM_MENU_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include "devices/keyboard.h"
#include "devices/values.h"

typedef enum {
    MAINMENU,
    INSTRUCTIONS,
    INTRO,
    GAME,
    GAMEOVER
} GameState;

void menu_mouse(Mouse *mouse, struct packet *pp);
void main_menu_mouse(Mouse *mouse, struct packet *pp);
void instructions_mouse(Mouse *mouse, struct packet *pp);
void mode_mouse(Mouse *mouse, struct packet *pp);
void game_over_mouse(Mouse *mouse, struct packet *pp);

#endif // _LCOM_MENU_H_
