#ifndef _LCOM_IH_H_
#define _LCOM_IH_H_


#include <stdio.h>

// Include menu
#include "game/menu.h"
#include "Graphic.Macros.h"

// Include devices
#include "timer.h"
#include "keyboard.h"
#include "i8042.h"
#include "video.h"
#include "rtc.h"

// Include models 
#include "models/player.h"
#include "models/bullet.h"
#include "models/helicopter.h"
#include "models/platforms.h"

// Include views
#include "view/canvas.h"

// Include xpm
#include "../xpm/xpm_sprites.h"


int init_game();

int proj_int();

int close_game();

void timer_int_h();

void kbc_int_h();

void mouse_int_h();


#endif // _LCOM_IH_H_
