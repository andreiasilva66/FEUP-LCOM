
#include <lcom/lcf.h>
#include "ih.h"

uint32_t timer_mask; 
uint32_t mouse_mask;
uint32_t kbc_mask;

Mouse mouse = {640, 512, 0, 0};
uint8_t mouse_packet = 0;
struct packet pp;
bool kbc_ih_error;
bool mouse_ih_error;
bool jumping = false;
uint8_t data[2];
extern uint8_t scancode;
extern uint32_t n_player_bullets;
extern uint32_t n_heli_bullets;
uint32_t reloadtime = 60*3;
Player player = {100, 1004-80, 100, 1004-80, 100, 0};
Helicopter heli = {200, 100, 200, 100, 100};
bool finished = false; 

int init_game(){

    initialize_bullets();
   
    int flag = set_frame_buffer(0x11A);
    if (flag) return vg_exit();

     //draw arena
    flag = canvas_draw_arena(0xFFF0, 0xF09F);
    if (flag) return vg_exit();

    flag = vg_draw_rectangle(player.x, player.y, 50, 50, 0x000F);
    if (flag) return vg_exit();

    flag = vg_draw_rectangle(heli.x, heli.y, 100, 50, 0x000F);
    if (flag) return vg_exit();

    uint8_t timer_bit_no=0;
    if(timer_subscribe_int(&timer_bit_no)) return 1;

    //kbc
    uint8_t kbc_bit_no = 12;
    flag = kbc_subscribe_int(&kbc_bit_no);
    if (flag) return flag;

    //mouse
    uint8_t mouse_bit_no=3;
    if(mouse_write_cmd(MOUSE_EN_DATA_REP) != 0)return 1;
    if(mouse_subscribe_int(&mouse_bit_no)) return 1;

    timer_mask = BIT(timer_bit_no); 
    mouse_mask = BIT(mouse_bit_no);
    kbc_mask = BIT(kbc_bit_no);

    return 0;
}

int proj_int(){

    // local variables
    int ipc_status;
    message msg;
    
    int flag = driver_receive(ANY, &msg, &ipc_status);
    if (flag){
        printf("driver_receive failed with: %d", flag);
        return 0;
    }

    if (!is_ipc_notify(ipc_status)) return 0;

    switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE : {
            bool timer_int = msg.m_notify.interrupts & timer_mask;
            bool kbc_int = msg.m_notify.interrupts & kbc_mask;
            bool mouse_int = msg.m_notify.interrupts & mouse_mask;
            if (timer_int){
                timer_int_h();
            }
            if (kbc_int){
                kbc_int_h();
            }

            if(mouse_int){
                mouse_int_h();
            }
        }
        default : break;
        }

    return 0;
} 

int close_game(){
    if(mouse_write_cmd(MOUSE_DIS_DATA_REP)) return vg_exit();

    if(mouse_unsubscribe_int()) return vg_exit();

    if(timer_unsubscribe_int()) return vg_exit();

    if(kbc_unsubscribe_int()) return vg_exit();

    return vg_exit();
}

void timer_int_h(){

    movement(&heli);

  if(n_player_bullets==10){
    if(reloadtime==0){
      reloadtime = 60*3;
      n_player_bullets=0;
      }
    reloadtime--;
  }

  if(jumping){
      jump(&player,10);

      int flag = canvas_refresh(&player, &heli);

      if (flag) finished = true;

      player.old_x = player.x; player.old_y = player.y;
  }

  if(n_player_bullets){
      player_update_bullets();
  }
  
}

void kbc_int_h(){
    kbc_get_scancode(data);

    if(scancode==KBC_ESC) finished=true;
 
    if(scancode == TWO_BYTE) return;

    if (kbc_ih_error) finished=true;

    process_scancode(&player, data);

    int flag = canvas_refresh(&player, &heli);

    if (flag) finished=true;

    update_pos(&player);
  
}

void mouse_int_h(){
    if(mouse_get_data(&pp)) return;

    if (mouse_packet != 3) return;

    mouse_parse_packet(&pp);

    mouse.old_x=mouse.x;
    mouse.old_y=mouse.y;

    mouse.x += pp.delta_x;
    
    if(mouse.x <= 50) mouse.x = 50;
    if(mouse.x >= 1260-50) mouse.x = 1260-50;

    mouse.y -= pp.delta_y;
    
    if(mouse.y <= 50) mouse.y = 50;
    if(mouse.y >= 1004-50) mouse.y = 1004-50;

    process_packet(&player, &pp, &mouse);

    mouse_packet = 0;
}


