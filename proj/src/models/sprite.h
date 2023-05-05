#ifndef _LCOM_SPRITE_H_
#define _LCOM_SPRITE_H_

#include "../devices/video.h"

typedef struct Sprite
{
    uint16_t height;
    uint16_t width;
    uint32_t color;
    uint32_t *colors;
    uint8_t pressed; 
};

Sprite create_sprite (xpm_map_t sprite);
void destroy_sprite (Sprite *sprite);













#endif