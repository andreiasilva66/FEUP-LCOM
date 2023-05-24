#ifndef _LCOM_IH_H_
#define _LCOM_IH_H_


#include <stdio.h>

// Include menu
#include "game/menu.h"

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

// Include views
#include "view/canvas.h"


int init_game();

int proj_int();

int close_game();

void timer_int_h();

void kbc_int_h();

void mouse_int_h();


#endif // _LCOM_IH_H_
