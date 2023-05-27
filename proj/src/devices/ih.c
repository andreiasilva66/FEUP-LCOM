
#include <lcom/lcf.h>
#include "ih.h"
#include "game/menu.h"
#include "devices/video.h"

uint32_t timer_mask; 
uint32_t mouse_mask;
uint32_t kbc_mask;

extern Rtc rtc;
Mouse mouse = {640, 512};
uint8_t mouse_packet = 0;
struct packet pp;
bool kbc_ih_error;
bool mouse_ih_error;
uint8_t data[2];
extern uint8_t scancode;
extern uint32_t n_player_bullets;
extern uint32_t n_heli_bullets;
extern uint32_t timer_cnt;
uint32_t reloadtime = 60*3;
Player player = {PLAYER_INI_X, PLAYER_INI_Y, PLAYER_HP, 0};
Helicopter heli = {HELI_INI_X, HELI_INI_Y, 1, 1, HELI_HP, true};
bool finished = false;
GameState game_state = MAINMENU; 
extern uint32_t heli_shoot_time;

int init_game(){

    /*
    memccpy(&rtc, 0, sizeof(rtc));
    rtc_update();
    */

    initialize_bullets();
    initialize_platforms();
   
    int flag = set_frame_buffer(0x11A);
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

    vg_load_xpm();

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

    if(mouse_write_cmd(MOUSE_DIS_DATA_REP))
        return vg_exit();

    free_buffer();

    return vg_exit();
}

void timer_int_h(){

    timer_int_handler();
    
    switch(game_state){
        case MAINMENU:
            draw_background();  
            draw_player(&player);
            canvas_draw_menu(&mouse);
            break;

        case INSTRUCTIONS:
            draw_background();  
            draw_player(&player);
            canvas_draw_instructions(&mouse);
            break;

        case GAME: 
            
            if(n_player_bullets==10){
                if(reloadtime==0){
                reloadtime = 60*3;
                n_player_bullets=0;
                }
                reloadtime--;
            }

            if(timer_cnt % (heli_shoot_time) == 0){
                helicopter_shoot(&heli,&player);
            }

            // add difficulty
            if(timer_cnt % (60*30) == 0){
                helicopter_add_difficulty(&heli);                
            }


            // Update objects
            player_update_bullets(&heli);
            heli_update_bullets(&player);
            update_heli_move(&heli);
            player_update_mov(&player);

            // update frames
            if(timer_cnt%(30)==0){
                player.frame++;
            }

            // draw
            draw_background();   
            draw_remaining_bullets(BULLETS - n_player_bullets); 
            draw_hp_bar(player.hp);           
            draw_player(&player);
            draw_helicopter(&heli);
            draw_c_bullets();
            draw_platforms();

            break;

        case GAMEOVER:
            draw_background();   
            draw_remaining_bullets(BULLETS - n_player_bullets); 
            draw_hp_bar(player.hp);           
            draw_player(&player);
            draw_helicopter(&heli);
            draw_c_bullets();
            canvas_draw_game_over(&mouse);
            break;

        default:
            break;
    }

    draw_mouse(&mouse);
    
    change_buffer();
}

void kbc_int_h(){
    kbc_get_scancode(data);

    if(scancode==KBC_ESC) finished=true;
 
    if(scancode == TWO_BYTE) return;

    if (kbc_ih_error) finished=true;

    process_scancode(&player, data);
  
}

void mouse_int_h(){
    if(mouse_get_data(&pp)) return;

    if (mouse_packet != 3) return;

    mouse_parse_packet(&pp);

    mouse.x += pp.delta_x;
    
    if(mouse.x <= 50) mouse.x = 50;
    if(mouse.x >= 1260-50) mouse.x = 1260-50;

    mouse.y -= pp.delta_y;
    
    if(mouse.y <= 50) mouse.y = 50;
    if(mouse.y >= 1004-50) mouse.y = 1004-50;

    if(game_state == MAINMENU || game_state == INSTRUCTIONS || game_state == GAMEOVER){
        menu_mouse(&mouse, &pp);
        }
    else if(game_state == GAME){
        process_packet(&player, &pp, &mouse);
    }

    mouse_packet = 0;
}


