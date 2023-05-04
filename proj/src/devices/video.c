#include <lcom/lcf.h>
#include "video.h"
#include "keyboard.h"

extern uint8_t data;
vbe_mode_info_t info;
void *video_mem;

void *(vg_init)(uint16_t mode){
    vbe_get_mode_info(mode, &info);

struct minix_mem_range mr;
unsigned int vram_base;  /* VRAM's physical addresss */
vram_base = info.PhysBasePtr;
unsigned int vram_size;  /* VRAM's size, but you can use the frame-buffer size, instead */

// adicionamos 7 ao BitsPerPixel para garantirmos o n.º de bytes suficientes uma vez que fazermos uma divisão inteira
//ex: 15 / 8 = 1, porém precisamos de 2 bytes;
// 15+7 = 22      22/8 = 2   fica resolvido o problema
uint8_t bytes_per_pixel = (info.BitsPerPixel + 7) / 8;
vram_size = info.XResolution * info.YResolution * bytes_per_pixel;
int r;				    

/* Use VBE function 0x01 to initialize vram_base and vram_size */


/* Allow memory mapping */

mr.mr_base = (phys_bytes) vram_base;	
mr.mr_limit = mr.mr_base + vram_size;  

if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
   panic("sys_privctl (ADD_MEM) failed: %d\n", r);

/* Map memory */

video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

if(video_mem == MAP_FAILED){
   panic("couldn't map video memory");
}
    memset(video_mem, 0, vram_size);
    reg86_t r86;
    memset(&r86, 0, sizeof(r86));
    r86.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
    r86.bx = 1<<14|mode; // set bit 14: linear framebuffer
    r86.intno = 0x10;

    if( sys_int86(&r86) != OK ) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return NULL;
    }
    return video_mem;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    uint8_t bytes = (info.BitsPerPixel+7) / 8;
    uint8_t* ptr = (uint8_t*) video_mem + (y * info.XResolution + x) * bytes;
    for(uint16_t i = 0; i < len ; i++){
        for(uint8_t j = 0; j < bytes; j++){
            *ptr = color >> (j * 8);
            ptr++;
        }
    }
    return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
    if(x > info.XResolution || y > info.YResolution){
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

// keyboard loop
int(keyboard_loop)() {
    int r = 0;
    uint8_t bit = 0;
    if(kbc_subscribe_int(&bit)) return 1;
    uint32_t kanna = BIT(bit);
    
    int ipc_status;
    message msg;
 
    while(data != KBD_ESC) {
        /* Get a request message. */
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */				
                    if (msg.m_notify.interrupts & kanna) { /* subscribed interrupt */
                        if(kbc_read_out_buffer(&data)) return 1;
                        kbc_ih();
                    }
                    break;
                default:
                    break; /* no other notifications expected: do nothing */	
            }
        } else { /* received a standard message, not a notification */
            /* no standard messages expected: do nothing */
        }
    }
    if(kbc_unsubscribe_int()){
        return 1;
    }
    return 0;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){
    uint8_t bytes = (info.BitsPerPixel+7) / 8;
    uint8_t* ptr = (uint8_t*) video_mem + (y * info.XResolution + x) * bytes;
    for(uint8_t j = 0; j < bytes; j++){
        *ptr = color >> (j * 8);
        ptr++;
    }
    return 0;
}

int (vg_draw_xpm) (xpm_map_t xpm, uint16_t x, uint16_t y){
    if(x > info.XResolution || y > info.YResolution){
        return 1;
    }
    xpm_image_t image;
    uint8_t* map;

    map = xpm_load(xpm, XPM_INDEXED, &image);

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
            vg_draw_pixel(j,i,map[counter]);
            counter++;
        }
        counter += extra_x;
    }

    return 0;
}

int (vg_update)(xpm_map_t xpm, uint16_t old_x, uint16_t old_y, uint16_t new_x, uint16_t new_y){
    xpm_image_t image;
    uint8_t* map;

    map = xpm_load(xpm, XPM_INDEXED, &image);

    if(vg_draw_rectangle(old_x, old_y, image.width, image.height,0)){
        return 1;
    }

    if(vg_draw_xpm(xpm, new_x, new_y)){
        return 1;
    }
    return 0;
}
