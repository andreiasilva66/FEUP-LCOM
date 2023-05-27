#include <lcom/lcf.h>
#include "video.h"
#include "keyboard.h"
#include "xpm/xpm2.h"

extern uint8_t data;
vbe_mode_info_t info;
void *video_mem;
void *video_mem_sec;
unsigned int vram_size;

 uint16_t* map_heli = NULL;
 uint16_t* map_soldier1 = NULL;
 uint16_t* map_soldier2 = NULL;
 uint16_t* map_soldier3 = NULL;
 uint16_t* map_platforms = NULL;
 uint16_t* map_background_day = NULL;
 uint16_t* map_background_night = NULL;
 uint16_t* map_s_bullet = NULL; 
 uint16_t* map_h_bullet = NULL;
 uint16_t* map_soldier_dead = NULL;
 uint16_t* map_heli_dead = NULL;
uint16_t* map_target = NULL;
uint16_t* map_title = NULL;
uint16_t* map_back_no = NULL;
uint16_t* map_back_yes = NULL;
uint16_t* map_instructions_no = NULL;
uint16_t* map_instructions_yes = NULL;
uint16_t* map_textinstructions = NULL;
uint16_t* map_start_yes = NULL;
uint16_t* map_start_no = NULL;
uint16_t* map_playagain_no = NULL;
uint16_t* map_playagain_yes = NULL;
uint16_t* map_gameover = NULL;
uint16_t* map_explosion1 = NULL;
uint16_t* map_explosion2 = NULL;
uint16_t* map_explosion3 = NULL;

xpm_image_t image_soldier_dead;
xpm_image_t image_heli;
xpm_image_t image_soldier1;
xpm_image_t image_soldier2;
xpm_image_t image_soldier3;
xpm_image_t image_platforms;
xpm_image_t image_background_day;
xpm_image_t image_background_night;
xpm_image_t image_s_bullet;
xpm_image_t image_h_bullet;
xpm_image_t image_heli_dead;
xpm_image_t image_target;
xpm_image_t image_title;
xpm_image_t image_back_no;
xpm_image_t image_back_yes;
xpm_image_t image_instructions_no;
xpm_image_t image_instructions_yes;
xpm_image_t image_textinstructions;
xpm_image_t image_start_yes;
xpm_image_t image_start_no;
xpm_image_t image_playagain_no;
xpm_image_t image_playagain_yes;
xpm_image_t image_gameover;
xpm_image_t image_explosion1;
xpm_image_t image_explosion2;
xpm_image_t image_explosion3;




void (change_buffer)(){
    memcpy(video_mem, video_mem_sec, vram_size);
}

int(set_frame_buffer)(uint16_t mode){
    vbe_get_mode_info(mode, &info);

struct minix_mem_range mr;
unsigned int vram_base;  /* VRAM's physical addresss */
vram_base = info.PhysBasePtr;

uint8_t bytes_per_pixel = (info.BitsPerPixel + 7) / 8;
vram_size = info.XResolution * info.YResolution * bytes_per_pixel;
int r;				    

/* Use VBE function 0x01 to initialize vram_base and vram_size */


/* Allow memory mapping */

mr.mr_base = (phys_bytes) vram_base;	
mr.mr_limit = mr.mr_base + vram_size;  

if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))){
   panic("sys_privctl (ADD_MEM) failed: %d\n", r);
   return 1;}

/* Map memory */

video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

if(video_mem == MAP_FAILED){
   panic("couldn't map video memory");
   return 1;
}
    //memset(video_mem, 0, vram_size);
    reg86_t r86;
    memset(&r86, 0, sizeof(r86));
    r86.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
    r86.bx = 1<<14|mode; // set bit 14: linear framebuffer
    r86.intno = 0x10;

    if( sys_int86(&r86) != OK ) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return 1;
    }
    video_mem_sec = malloc(vram_size);
    return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    uint8_t bytes = (info.BitsPerPixel+7) / 8;
    uint8_t* ptr = (uint8_t*) video_mem_sec + (y * info.XResolution + x) * bytes;
    for(uint16_t i = 0; i < len ; i++){
        for(uint8_t j = 0; j < bytes; j++){
            *ptr = color >> (j * 8);
            ptr++;
        }
    }
    return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
    if(x > info.XResolution || y > info.YResolution || x<0 || y<0){
        return 1;
    }
    if((x + width) > info.XResolution){
        width = info.XResolution - x; // o que falta desenhar
    }
    if((y + height) > info.YResolution){
        height = info.YResolution - y; // o que falta desenhar
    }
    for (uint16_t i = 0; i < height; i++){
        vg_draw_hline(x, i+y, width, color);
    }
    return 0;
}


int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){
    if(x >= info.XResolution || y >= info.YResolution){
        return 0;
    }
    uint8_t bytes = (info.BitsPerPixel+7) / 8;
    uint8_t* ptr = (uint8_t*) video_mem_sec + (y * info.XResolution + x) * bytes;
    for(uint8_t j = 0; j < bytes; j++){
        *ptr = color >> (j * 8);
        ptr++;
    }
    return 0;
}

int (vg_load_xpm)(){
    //xpm_image_t image;

          map_heli = (uint16_t*) xpm_load(heli_xpm, XPM_5_6_5, &image_heli);
          map_soldier1 = (uint16_t*) xpm_load(soldado1,XPM_5_6_5,&image_soldier1);
          map_soldier2 = (uint16_t*) xpm_load(soldado2,XPM_5_6_5,&image_soldier2);
          map_soldier3 = (uint16_t*) xpm_load(soldado3,XPM_5_6_5,&image_soldier3);
          map_soldier_dead = (uint16_t*) xpm_load(soldado_morto,XPM_5_6_5,&image_soldier_dead);
         // map_platforms = _mortouint16_t*) xpm_load(xpm,XPM_5_6_5,&image_platforms);
          //map_background_night = (uint16_t*) xpm_load(xpm,XPM_5_6_5,&image_background_night);
          map_background_day = (uint16_t*) xpm_load(background_day,XPM_5_6_5,&image_background_day);
          map_h_bullet = (uint16_t*) xpm_load(bala_heli,XPM_5_6_5,&image_h_bullet);
          map_s_bullet = (uint16_t*) xpm_load(bala_soldado,XPM_5_6_5,&image_s_bullet); 
          map_heli_dead = (uint16_t*) xpm_load(heli_destruido,XPM_5_6_5,&image_heli_dead);
          map_target = (uint16_t*) xpm_load(target,XPM_5_6_5,&image_target);
          map_gameover = (uint16_t*) xpm_load(gameover,XPM_5_6_5,&image_gameover);
          map_playagain_no = (uint16_t*) xpm_load(playagain_no,XPM_5_6_5,&image_playagain_no);
          map_playagain_yes = (uint16_t*) xpm_load(playagain_yes,XPM_5_6_5,&image_playagain_yes);
          map_title = (uint16_t*) xpm_load(title,XPM_5_6_5,&image_title);
          map_back_no = (uint16_t*) xpm_load(back_no,XPM_5_6_5,&image_back_no);
          map_back_yes = (uint16_t*) xpm_load(back_yes,XPM_5_6_5,&image_back_yes);
          map_instructions_no = (uint16_t*) xpm_load(instructions_no,XPM_5_6_5,&image_instructions_no);
          map_instructions_yes = (uint16_t*) xpm_load(instructions_yes,XPM_5_6_5,&image_instructions_yes);
          map_start_no = (uint16_t*) xpm_load(start_no,XPM_5_6_5,&image_start_no);
          map_start_yes = (uint16_t*) xpm_load(start_yes,XPM_5_6_5,&image_start_yes);
          map_textinstructions = (uint16_t*) xpm_load(textinstructions,XPM_5_6_5,&image_textinstructions);
          map_explosion1 = (uint16_t*) xpm_load(explosion1,XPM_5_6_5,&image_explosion1);
          map_explosion2 = (uint16_t*) xpm_load(explosion2,XPM_5_6_5,&image_explosion2);
          map_explosion3 = (uint16_t*) xpm_load(explosion3,XPM_5_6_5,&image_explosion3);
          return 0;
    }


int (vg_draw_xpm) (uint8_t id, uint16_t x, uint16_t y){
    if(x > info.XResolution || y > info.YResolution){
        return 1;
    }
    xpm_image_t image;
    uint16_t* map;
    switch (id) {
        case 1:
            image = image_heli;
            map = map_heli;
            break;
        case 2:
            image = image_soldier1;
            map = map_soldier1;
            break;
        case 3:
            image = image_soldier2;
            map = map_soldier2;
            break;
        case 4:
            image = image_soldier3;
            map = map_soldier3;
            break;
        case 5:
            image = image_platforms;
            map = map_platforms;
            break;
        case 6:
            image = image_background_day;
            map = map_background_day;
            break;
        case 7:
            image = image_background_night;
            map = map_background_night;
            break;
        case 8:
            image = image_s_bullet;
            map = map_s_bullet;
            break;
        case 9:
            image = image_h_bullet;
            map = map_h_bullet;
            break;
        case 10:
            image = image_soldier_dead;
            map = map_soldier_dead;
            break;
        case 11:
            image = image_heli_dead;
            map = map_heli_dead;
            break;
        case 12:
            image = image_target;
            map = map_target;
            break;
        case 13:
            image = image_explosion1;
            map = map_explosion1;
            break;
        case 14:
            image = image_explosion2;
            map = map_explosion2;
            break;
        case 15:
            image = image_explosion3;
            map = map_explosion3;
            break;
        case 16:
            image = image_back_no;
            map = map_back_no;
            break;
        case 17:
            image = image_back_yes;
            map = map_back_yes;
            break;
        case 18:
            image = image_gameover;
            map = map_gameover;
            break;
        case 19:
            image = image_instructions_no;
            map = map_instructions_no;
            break;
        case 20:
            image = image_instructions_yes;
            map = map_instructions_yes;
            break;
        case 21:
            image = image_playagain_no;
            map = map_playagain_no;
            break;
        case 22:
            image = image_playagain_yes;
            map = map_playagain_yes;
            break;
        case 23:
            image = image_start_no;
            map = map_start_no;
            break;
        case 24:
            image = image_start_yes;
            map = map_start_yes;
            break;
        case 25:
            image = image_textinstructions;
            map = map_textinstructions;
            break;
        case 26:
            image = image_title;
            map = map_title;
            break;
        default:
            break;
    }
    uint32_t counter = 0;
    uint32_t extra_x = 0;

    uint32_t width, height;
    
    if(x+image.width <= info.XResolution){
        width = x+image.width;
    } else {
        width = info.XResolution;
        extra_x = x+image.width - width;
    }

    if(y + image.height <= info.YResolution){
        height = y+image.height;
    } else {
        height = info.YResolution;
    }

    for(uint16_t i = y; i < height; i++){
        for(uint16_t j = x; j < width; j++){
            if(map[counter] != 0xFFFF){
                vg_draw_pixel(j,i,map[counter]);
            }
            counter++;
        }
        counter += extra_x;
    }
    return 0;
}

// int (vg_update)(xpm_map_t xpm, uint16_t old_x, uint16_t old_y, uint16_t new_x, uint16_t new_y){
//     xpm_image_t image;
//     uint8_t* map;

//     map = xpm_load(xpm, XPM_INDEXED, &image);

//     if(vg_draw_rectangle(old_x, old_y, image.width, image.height,0)){
//         return 1;
//     }

//     if(vg_draw_xpm(xpm, 0, new_x, new_y)){
//         return 1;
//     }
//     return 0;
// }


void free_buffer(){
    free(video_mem_sec);
}
