#ifndef _LCOM_VALUES_H_
#define _LCOM_VALUES_H_

#include <lcom/lcf.h>

//hook
#define TIMER_HOOK 0
#define KBC_HOOK 12
#define MOUSE_HOOK 3

//rtc 
#define NIGHT_TIME_BEGIN 18
#define NIGHT_TIME_END 6

//resolution 
#define Y_RESOLUTION 1024
#define  X_RESOLUTION 1280
#define VIDEO_MODE 0x11A

//player
#define PLAYER_WIDTH 22
#define PLAYER_HEIGHT 47
#define PLAYER_HP 100
#define PLAYER_INI_Y (924)
#define PLAYER_INI_X 100 
#define PLAYER_SPEED 8


//helicopter
#define HELI_WIDTH 200
#define HELI_HEIGHT 130
#define HELI_HP 200
#define HELI_INI_X 1330 
#define HELI_INI_Y 100
#define HELI_VX 1
#define HELI_VY 1

//bullets
#define BLTS_WIDTH 9
#define BLTS_HEIGHT 9
#define BULLETS 10
#define HELI_BLTS_DMG 20
#define PLAYER_BLTS_DMG 10




//mouse
#define MOUSE_WIDTH 36
#define MOUSE_HEIGHT 36
#define MOUSE_INI_X 640
#define MOUSE_INI_Y 512


//menu 
#define MENU_WIDTH 500  
#define MENU_HEIGHT 100
#define MENU_POS_X 400
#define MENU_POS_Y 300
#define MENU_DIST  200
#endif
