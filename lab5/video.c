#include <lcom/lcf.h>

void *(vg_init)(uint16_t mode){
    vbe_mode_info_t info;
    vbe_get_mode_info(mode, &info);
    reg86_t r86;
    memset(&r86, 0, sizeof(r86));
    r86.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
    r86.bx = 1<<14|mode; // set bit 14: linear framebuffer
    r86.intno = 0x10;

    if( sys_int86(&r86) != OK ) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return NULL;
    }

void *video_mem;         /* frame-buffer VM address 
				   (static global variable*/ 


struct minix_mem_range mr;
unsigned int vram_base;  /* VRAM's physical addresss */
vram_base = info.PhysBasePtr;
unsigned int vram_size;  /* VRAM's size, but you can use the frame-buffer size, instead */

// adicionamos 7 ao BitsPerPixel para garantirmos o n.º de bytes suficientes uma vez que fazermos uma divisão inteira
//ex: 15 / 8 = 1, porém precisamos de 2 bytes;
// 15+7 = 22      22/8 = 2   fica resolvido o problema
vram_size = info.XResolution * info.YResolution * (info.BitsPerPixel + 7) / 8;
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
    memset(video_mem, 0x35, vram_size);
    return video_mem;
}
