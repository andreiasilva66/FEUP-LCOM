#include <lcom/lcf.h>
#include "videocard.h"
#include <math.h>

uint8_t* frame_buffer;
vbe_mode_info_t info;

int (set_graphic_mode)(uint16_t submode){
   reg86_t r; 

  r.ax = 0x4F02; 
  r.bx = 1 << 14 | submode;
  r.intno = 0x10;

  if(sys_int86(&r) != OK) return 1;
  return 0;
}

int (set_frame_buffer)(uint16_t mode){
  int r;

  memset(&info,0,sizeof(info));
  if(vbe_get_mode_info(mode,&info) != 0) return 1;

  unsigned int bytes_per_pixel = (info.BitsPerPixel + 7) / 8;

  unsigned int buffer_size = info.XResolution * info.YResolution * bytes_per_pixel;

  struct minix_mem_range mr;
  mr.mr_base = info.PhysBasePtr;
  mr.mr_limit = info.PhysBasePtr + buffer_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
   panic("sys_privctl (ADD_MEM) failed: %d\n", r);

   frame_buffer = vm_map_phys(SELF,(void *)mr.mr_base,buffer_size);

   if(frame_buffer == MAP_FAILED) panic("couldn't map video memory");

}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){

if(x > info.XResolution || y > info.YResolution) return 1;
  unsigned int bpp = (info.BitsPerPixel + 7) / 8; 
  unsigned int position = (x + y * info.XResolution) * bpp ;
  if( memcpy(&frame_buffer[position],&color,bpp) == NULL) return 1;
  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
  for(int i = 0 ; i < len; i++){
    if(vg_draw_pixel(x+i,y,color) != 0) return 1; 
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){

  for(int i = 0;i < height; i++){

    if(vg_draw_hline(x,y+i,width,color) != 0) {
      vg_exit();
      return 1;
    }

  }

}

int (normalize_color)(uint32_t color, uint32_t *new_color){

  if(info.BitsPerPixel == 16){ 
  uint8_t r = getRed(color);
  uint8_t g = getGreen(color);
  uint8_t b = getBlue(color);

  r = r  & 0x1F;
  g = g  & 0x3F;
  b = b  & 0x1F;
  *new_color = 0x00000000;
  *new_color = (r << 11 | g << 5 | b);
  }

  if(info.BitsPerPixel == 24){

    color = color & (0x00FFFFFF);

  }

  else return *new_color = color;
}





uint8_t getRed (uint32_t color) {

return color >> 16 & 0xFF;
}

uint8_t getGreen (uint32_t color) {

return color >> 8 & 0xFF;
}
uint8_t getBlue (uint32_t color) {

return color & 0xFF;
}

int (print_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y){
  xpm_image_t img;

  uint8_t* colors = xpm_load(xpm,XPM_INDEXED,&img);

     for (int h = 0 ; h < img.height ; h++) {
    for (int w = 0 ; w < img.width ; w++) {
      if (vg_draw_pixel(x + w, y + h, *colors) != 0) return 1;
      colors++; // avança para a próxima cor
    }
  }
  return 0;

}


