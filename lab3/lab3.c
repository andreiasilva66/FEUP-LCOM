


#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include <kbc.h>
#include <i8042.h>
#include <lcom/timer.h>



extern uint8_t scancode;
extern int cnt, count;

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
  /* To be completed by the students */
  
  uint8_t irq_set;
  int ipc_st;
  message msg;
  uint8_t bytes_code[2];
  bool twobsc = false;

  if(kbc_subscribe_int(&irq_set))
    return 1;

  while(scancode != ESC_KEY_BREAKCODE){


    if(driver_receive(ANY,&msg,&ipc_st))
      continue;

    if(is_ipc_notify(ipc_st) && msg.m_source==HARDWARE && (irq_set & msg.m_notify.interrupts)){
        kbc_ih();
        if(scancode == TWO_BYTE_CODE){
          bytes_code[0]=scancode;
          twobsc = true;
          continue;
        }
        
          if(twobsc)
            bytes_code[1]=scancode;
          else
            bytes_code[0]=scancode;
        
      kbd_print_scancode(!(scancode & KBC_BREAKCODE), twobsc ? 2 : 1, bytes_code);
      twobsc=false;
    }       
  }         


  return kbc_unsubscrive_int() || kbd_print_no_sysinb(cnt); 
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  
  uint8_t bytes_code[2];
  bool twobsc = false;


  while(scancode!=ESC_KEY_BREAKCODE){

    if(kbc_get_status() || kbc_get_scancode()){
      tickdelay(micros_to_ticks(DELAY_US));
      continue;
    }

    if(scancode==TWO_BYTE_CODE){
      twobsc = true;
      bytes_code[0]=scancode;
      continue;
    }
    if(twobsc){
      bytes_code[1]=scancode;
    }
    else{
      bytes_code[0]=scancode;
    }
      
    kbd_print_scancode(!(scancode & KBC_BREAKCODE), twobsc ? 2 : 1, bytes_code);
    twobsc=false;
  }

  kbc_activate_interrupts();
  return kbd_print_no_sysinb(cnt);
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  
  uint8_t kbc_irq_set;
  uint8_t timer_irq_set;
  int ipc_st;
  message msg;
  uint8_t bytes_code[2];
  bool twobsc = false;

  if(kbc_subscribe_int(&kbc_irq_set) || timer_subscribe_int(&timer_irq_set))
    return 1;

  while(scancode != ESC_KEY_BREAKCODE && (count/60) < n){

    if(driver_receive(ANY,&msg,&ipc_st)){
      continue;
    }

    if(is_ipc_notify(ipc_st) && msg.m_source==HARDWARE){

      if(timer_irq_set & msg.m_notify.interrupts){
        timer_int_handler();
      }

      if((kbc_irq_set & msg.m_notify.interrupts)){
        kbc_ih();
        if(scancode == TWO_BYTE_CODE){
          bytes_code[0]=scancode;
          twobsc = true;
          continue;
        }
        
        if(twobsc)
          bytes_code[1]=scancode;
        else
          bytes_code[0]=scancode;
        
      kbd_print_scancode(!(scancode & KBC_BREAKCODE), twobsc ? 2 : 1, bytes_code);
      twobsc=false;
      count = 0;
      }   
    }  
  }
  return (timer_unsubscribe_int() || kbc_unsubscrive_int()) || kbd_print_no_sysinb(cnt);
}

