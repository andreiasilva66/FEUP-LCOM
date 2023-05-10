#include <stdio.h>
#include <lcom/lcf.h>
#include "devices/i8042.h"

/* DEVICES */
#include <lcom/timer.h>
#include "devices/keyboard.h"
#include "devices/video.h"

/* MODELS */
#include "models/object.h"

/* VIEWS */
#include "view/canvas.h"

#include "models/bullet.h"

#define WAIT 5

int kbc_hook_id, mouse_hook_id, timer_hook_id;
Mouse mouse = {640, 512, 0, 0};
uint8_t mouse_packet = 0;
struct packet pp;
bool kbc_ih_error;
bool mouse_ih_error;
bool jumping = false;
uint8_t data[2];
extern uint8_t scancode;
extern uint32_t n_bullets;

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
    timer_hook_id = 3;

    // local variables
    int ipc_status;
    message msg;

    //timer
    uint8_t timer_bit_no;
    if(timer_subscribe_int(&timer_bit_no)) return 1;

    //kbc
    uint8_t kbc_bit_no = 0;
    int flag = kbc_subscribe_int(&kbc_bit_no);
    if (flag) return flag;

    //mouse
    uint8_t mouse_bit_no;
    if(mouse_write_cmd(MOUSE_EN_DATA_REP) != 0)return 1;
    if(mouse_subscribe_int(&mouse_bit_no)) return 1;

    uint32_t timer_mask = BIT(timer_bit_no); 
    uint32_t mouse_mask = BIT(mouse_bit_no);
    uint32_t kbc_mask = BIT(kbc_bit_no);
    
    while (scancode != KBC_ESC){
        flag = driver_receive(ANY, &msg, &ipc_status);
        if (flag){
            printf("driver_receive failed with: %d", flag);
            continue;
        }

        if (!is_ipc_notify(ipc_status)) continue;

        switch(_ENDPOINT_P(msg.m_source)){
            case HARDWARE : {
                bool timer_int = msg.m_notify.interrupts & timer_mask;
                bool kbc_int = msg.m_notify.interrupts & kbc_mask;
                bool mouse_int = msg.m_notify.interrupts & mouse_mask;
                if (timer_int){
                    if(jumping){
                        jump(player,10);

                        flag = canvas_refresh(player);

                        if (flag) return flag;

                        player->old_x = player->x; player->old_y = player->y;
                    }

                    if(n_bullets){
                        update_bullets();
                    }


                }
                if (kbc_int){
                    
                    kbc_get_scancode(data);
 
                    if(scancode == TWO_BYTE) continue;

                    if (kbc_ih_error) return kbc_ih_error;

                    process_scancode(player, data);

                    flag = canvas_refresh(player);

                    if (flag) return flag;

                    update_pos(player);

                }

                if(mouse_int){
                    
                    if(mouse_get_data(&pp)) return 1;
                    if (mouse_packet != 3) break;

                    mouse_parse_packet(&pp);

                    mouse.old_x=mouse.x;
                    mouse.old_y=mouse.y;

                    mouse.x += pp.delta_x;
                    
                    if(mouse.x < 0) mouse.x = 0;
                    if(mouse.x > 1280) mouse.x = 1280;

                    mouse.y -= pp.delta_y;
                    
                    if(mouse.y < 0) mouse.y = 0;
                    if(mouse.y > 1024) mouse.y = 1024;

                    process_packet(player, &pp, &mouse);

                    mouse_packet = 0;

                }
            }
            default : break;
        }
    }

    if(mouse_write_cmd(MOUSE_DIS_DATA_REP)) return 1;

    if(mouse_unsubscribe_int()) return 1;

    if(timer_unsubscribe_int()) return 1;

    return kbc_unsubscribe_int();
} 

int (proj_main_loop)(){
    Object player = {100, 100, 100, 100, 0};

   
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
