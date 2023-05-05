#include <stdio.h>
#include <lcom/lcf.h>
#include "devices/i8042.h"

/* DEVICES */
#include "devices/keyboard.h"
#include "devices/video.h"

/* MODELS */
#include "models/object.h"

/* VIEWS */
#include "view/canvas.h"

#define WAIT 5

int kbc_hook_id, mouse_hook_id;
int mouse_x = 640;
int mouse_y = 512;
uint8_t mouse_packet;
struct packet pp;
bool kbc_ih_error;
bool mouse_ih_error;
 uint8_t data[2];
extern uint8_t scancode;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("./trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("./output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int disable_video(int flag){
    vg_exit();
    return flag;
}

int proj_int_loop(Object* player){
    // global variables
    kbc_hook_id = 0;
    mouse_hook_id = 12;

    // local variables
    int ipc_status;
    message msg;

    //kbc
    uint8_t kbc_bit_no = 0;
    int flag = kbc_subscribe_int(&kbc_bit_no);
    if (flag) return flag;

    //mouse
    uint8_t mouse_bit_no;
    if(mouse_write_cmd(MOUSE_EN_DATA_REP) != 0)return 1;
    if(mouse_subscribe_int(&mouse_bit_no)) return 1;

    uint32_t mouse_mask = BIT(mouse_bit_no);
    uint32_t kbc_mask = BIT(kbc_bit_no);

    uint16_t old_x = player->x;
    uint16_t old_y = player->y;
    
    while (scancode != KBC_ESC){
        flag = driver_receive(ANY, &msg, &ipc_status);
        if (flag){
            printf("driver_receive failed with: %d", flag);
            continue;
        }

        if (!is_ipc_notify(ipc_status)) continue;

        switch(_ENDPOINT_P(msg.m_source)){
            case HARDWARE : {
                bool kbc_int = msg.m_notify.interrupts & kbc_mask;
                bool mouse_int = msg.m_notify.interrupts & mouse_mask;
                if (kbc_int){
                    
                    kbc_get_scancode(data);
 
                    if(scancode == TWO_BYTE) continue;

                    if (kbc_ih_error) return kbc_ih_error;

                    process_scancode(player, data);

                    flag = canvas_refresh(player, old_x, old_y);

                     if (flag) return flag;

                    old_x = player->x; old_y = player->y;
                }

                if(mouse_int){

                    mouse_get_data(&pp);

                    if(mouse_ih_error) return mouse_ih_error;
                    if (mouse_packet < 3) break;

                    mouse_parse_packet(&pp);

                    mouse_x += pp.delta_x;
                    
                    if(mouse_x < 0) mouse_x = 0;
                    if(mouse_x > 1280) mouse_x = 1280;

                    mouse_y -= pp.delta_y;
                    
                    if(mouse_y < 0) mouse_y = 0;
                    if(mouse_y > 1024) mouse_y = 1024;

                    mouse_packet = 0;
                }
            }
            default : break;
        }
    }

    if(mouse_write_cmd(MOUSE_DIS_DATA_REP)) return 1;

    if(mouse_unsubscribe_int()) return 1;

    printf("%d, %d", mouse_x, mouse_y);

    return kbc_unsubscribe_int();
} 

int (proj_main_loop)(){
    Object player = {100, 100};

   
    int flag = set_frame_buffer(0x11A);
    if (flag) return disable_video(flag);

     //draw arena
    flag = canvas_draw_arena(0xFFF0, 0xF09F);
    if (flag) return disable_video(flag);

    // draw player
   flag = vg_draw_rectangle(player.x, player.y, 50, 50, 0x000F);
   if (flag) return disable_video(flag);

    flag = proj_int_loop(&player);
    if (flag) return disable_video(flag);
    
    return vg_exit();

   return 0;
}
