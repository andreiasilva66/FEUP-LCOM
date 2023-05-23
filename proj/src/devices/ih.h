#ifndef _LCOM_IH_H_
#define _LCOM_IH_H_


#include <stdio.h>

// Include devices
#include <lcom/timer.h>
#include "keyboard.h"
#include "i8042.h"
#include "video.h"

// Include models 
#include "models/player.h"
#include "models/bullet.h"

// Include views
#include "view/canvas.h"

int init_game();

int proj_int();

int close_game();

void timer_int_h();

void kbc_int_h();

void mouse_int_h();


#endif // _LCOM_IH_H_
