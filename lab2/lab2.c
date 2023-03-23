#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

#include <i8254.h>

extern int count;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  /* To be implemented by the students */

  uint8_t timer_status = 0;

  return (timer_get_conf(timer,&timer_status) || timer_display_conf(timer,timer_status,field));

}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  
  return timer_set_frequency(timer,freq);
}

int(timer_test_int)(uint8_t time) {
  /* To be implemented by the students */
  
  uint8_t hook = 1;
  message msg;
  int ipc_st;
  uint32_t irq_set = BIT(hook);

  if(timer_subscribe_int(&hook))
    return 1;

  while(time){
    if(driver_receive(ANY,&msg,&ipc_st))
      continue;

    if(is_ipc_notify(ipc_st)){
      
      if(msg.m_source == HARDWARE){

        if(msg.m_notify.interrupts & irq_set){
          timer_int_handler();
          if(count%60==0){
            time--;
            timer_print_elapsed_time();}
        }
      }
    }
  }
  
  return timer_unsubscribe_int();
}
