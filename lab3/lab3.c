#include <lcom/lcf.h>

#include "i8042.h"
#include "kbc_utils.h"
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

extern uint8_t data;
extern uint32_t cntt;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {

// check status 
// read ports 
// get data 
uint8_t hook = 2;
uint32_t irq_set = BIT(hook);

KBC_subscribe_int(&hook);

uint8_t code[2];
int r,ipc_status;
message msg;
bool db = false;;


while(data != KBC_ESC){

  if((r = driver_receive(ANY,&msg,&ipc_status)) != 0){
    printf("driver_receive failed with: %d", r);
    continue;
  }

  if(is_ipc_notify(ipc_status)) {
    switch(_ENDPOINT_P(msg.m_source)){ 
    case HARDWARE:
      if(msg.m_notify.interrupts & irq_set){

        kbc_ih();
          printf( "codigo atual %d / t", data);

        if (data == TWO_SCAN_CODE) {

              code[0] = data;
              db = true;
              continue;
             // printf("code of double %d \t", code[0]);
            
            }

            else{ 
              if(db){code[1] = data;
              db = false;}
              else {code[0] = data;
                    }
             // printf("code of first %d \t", code[1]);

              kbd_print_scancode( !(data & KBC_MSB_SCNCD) , code[0] == TWO_SCAN_CODE ? 2 : 1, code);
              code[1] = 0x00;
              
            }

        
      break;}
      default:
      break;
      
      }}
}

KBC_unsubscribe_int();
kbd_print_no_sysinb(cntt);


return 0;
}

int(kbd_test_poll)() {

  //dar pool ao status register até OBF e AUX tarem topc
  uint8_t cmd;
  uint8_t code[2];
  bool db = false;

  buffer_reader(KBC_CMD_RED);
  cmd = data;
  data = 0x00;

  while(data != KBC_ESC){

    if(data_reader() != 0){
      continue;
    }

    if (data == TWO_SCAN_CODE) {

              code[0] = data;
              db = true;
              continue;
             // printf("code of double %d \t", code[0]);
            
            }

            else{ 
              if(db){code[1] = data;
              db = false;}
              else {code[0] = data;
                    }
             // printf("code of first %d \t", code[1]);

              kbd_print_scancode( !(data & KBC_MSB_SCNCD) , code[0] == TWO_SCAN_CODE ? 2 : 1, code);
              code[1] = 0x00;
             
            }
  }



  KBD_activate_interrupt(); 
  kbd_print_no_sysinb(cntt);
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}




/*
  kbc_ih();

            if (data == TWO_SCAN_CODE) {

              code[1] = data;
              code[0]
            }

            else {
              code[0] = data;
              kbd_print_scancode(code[1] == TWO_SCAN_CODE, code[1] == TWO_SCAN_CODE ? 2 : 1, code);
            }
            */


