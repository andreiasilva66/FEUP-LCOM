#include <lcom/lcf.h>
#include "platforms.h"


void initialize_platforms(){
  Platform platform = {0,0,0,0};
  for(int i = 0; i < 3 ; i++){
    platforms[i] = platform;

  }
    platforms_location(850,900,100,20,1);
    /*platforms_location(,50,100,20,2);
    platforms_location(50,50,100,20,3);
    platforms_location(50,50,100,20,4);*/


}

void platforms_location(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint8_t number){

  platforms[number].x = x;
  platforms[number].y = y;
  platforms[number].width = width;
  platforms[number].height = height;

}

void update_platforms_position(uint8_t scroll_speed){
for(int i = 0; i < 3 ; i++){
platforms[i].x -= scroll_speed;
}}

void draw_platforms(){

  for(int i = 0 ; i < 4; i++){ 

  vg_draw_rectangle(platforms[i].x,platforms[i].y,platforms[i].width,platforms[i].height,0xff);
  }

}



