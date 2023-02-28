#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  uint8_t read_back_command = TIMER_RB_CMD | TIMER_RB_SEL(timer) | TIMER_RB_COUNT_; 
  sys_outb(TIMER_CTRL,read_back_command);
  return util_sys_inb(0x40+timer,st);
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {


  union timer_status_field_val val;

  switch (field){

  case tsf_all: {
    val.byte = st;
    break;
  }

  case tsf_initial:{
    st <<= 2;
    st >>= 6;

    switch(st){
      case 1:{
        val.in_mode = LSB_only;
        break;
      }
      case 2:{
        val.in_mode = MSB_only;
        break;
      }
      case 3:{
        val.in_mode = MSB_after_LSB;
        break;
      }
      default:{
        val.in_mode = INVAL_val;
      }
    }
  }

  case tsf_mode:{
    st =<< 4;
    st =>> 5;
    val.count_mode = st;
    break;
  }

  case tsf_base:{
    uint8_t mask = 1;
    val.bcd = st & mask;
    break;
  }
  
  default:{
    return 1;
  }
  }

  return timer_print_config(timer,field,val);
}
