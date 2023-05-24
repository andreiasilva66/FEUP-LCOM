
#include <lcom/lcf.h>
#include "ih.h"
#include "game/menu.h"

uint32_t timer_mask; 
uint32_t mouse_mask;
uint32_t kbc_mask;

extern Rtc rtc;
Mouse mouse = {640, 512};
uint8_t mouse_packet = 0;
struct packet pp;
bool kbc_ih_error;
bool mouse_ih_error;
bool jumping = false;
uint8_t data[2];
extern uint8_t scancode;
extern uint32_t n_player_bullets;
extern uint32_t n_heli_bullets;
extern uint32_t timer_cnt;
uint32_t reloadtime = 60*3;
Player player = {PLAYER_INI_X, PLAYER_INI_Y, PLAYER_HP, 0};
Helicopter heli = {HELI_INI_X, HELI_INI_Y, HELI_HP};
bool finished = false;
GameState game_state = MAINMENU; 

int init_game(){

    /*
    memccpy(&rtc, 0, sizeof(rtc));
    rtc_update();
    */

    initialize_bullets();
   
    int flag = set_frame_buffer(0x11A);
    if (flag) return vg_exit();

    //draw menu
    canvas_draw_menu();

     //draw arena
    //flag = canvas_draw_arena(0xFFF0, 0xF09F);
    // if (flag) return vg_exit();

    // flag = vg_draw_rectangle(player.x, player.y, 50, 50, 0x000F);
    // if (flag) return vg_exit();

    // flag = vg_draw_rectangle(heli.x, heli.y, 100, 50, 0x000F);
    // if (flag) return vg_exit();

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
                if(game_state == GAME){ 
                canvas_draw_arena(0xFFF0, 0xF09F);
                draw_helicopter(&heli);
                draw_player(&player);
                draw_c_bullets();
                }
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
    timer_int_handler();
    change_buffer();
    switch(game_state){
        case MAINMENU:
            break;
        case GAME: 
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
            }

            if(n_player_bullets) player_update_bullets(&heli);
            if(n_heli_bullets) heli_update_bullets(&player);
            
            if(timer_cnt%(60*2)==0){
                shooting(&heli,&player);
            }
            /* 
            if(player.hp == 0)  destroy player and print game over image and return to menu button 
            if(heli.hp == 0)  destroy heli, stop the movement and the bullets(players loses control?) , destruction animation, game won image and return to menu button  */
            movement(&heli);
            break;
        case GAMEOVER:
            vg_draw_rectangle(MENU_POS_X,MENU_DIST + MENU_POS_Y,MENU_WIDTH,MENU_HEIGHT,0);
            break;
        default:
            break;
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

    if(game_state == MAINMENU || game_state == INSTRUCTIONS || game_state == MODE || game_state == GAMEOVER){
        menu_mouse(&mouse, &pp);
        draw_mouse(&mouse);
        }
    else if(game_state == GAME){
        process_packet(&player, &pp, &mouse);
    }

    mouse_packet = 0;
}


