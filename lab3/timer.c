<<<<<<< HEAD
#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

 uint32_t cnt = 0;
 int hook = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  uint8_t st;
  uint8_t lsb;
  uint8_t msb;
  
  if(timer_get_conf(timer,&st) != 0){
    return EXIT_FAILURE;
  }

  uint16_t fq = TIMER_FREQ / freq;  

  st &= 0x0F;

  switch (timer) 
  {
  case 0:
    st |= (TIMER_SEL0 | TIMER_LSB_MSB);
    break;
    case 1:
    st |= (TIMER_SEL1 | TIMER_LSB_MSB);
    break;
    case 2:
    st |= (TIMER_SEL2 | TIMER_LSB_MSB);
    break;
  
  default:
    break;
  }

   util_get_LSB(fq,&lsb);
   util_get_MSB(fq,&msb);

   sys_outb(TIMER_CTRL,st);
   sys_outb(TIMER_0 + timer,lsb);
   sys_outb(TIMER_0 +timer,msb);



  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  hook = *bit_no;
    
    return sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook);

 
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook);

}

void (timer_int_handler)() {
  
  cnt++;
  
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  
  uint8_t read_back_command = TIMER_RB_CMD | TIMER_RB_SEL(timer) | TIMER_RB_COUNT_; 
  sys_outb(TIMER_CTRL,read_back_command);
  util_sys_inb(TIMER_0 + timer,st); 
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {


 union timer_status_field_val val;

  switch (field)
  {
  case tsf_all:
    val.byte = st;
    break;

  case tsf_initial:

  st <<= 2;
   st >>= 6;

    switch (st){
    
    case 1:
    val.in_mode = LSB_only;
      break;

    case 2:
    val.in_mode = MSB_only;
    break;

    case 3:
    val.in_mode = MSB_after_LSB;
    break;
    
    default:
    val.in_mode = INVAL_val;
      break;

    }


  case tsf_mode:

  val.count_mode =(st & (BIT(3) | BIT(2) | BIT(1)));

  case tsf_base:

  val.bcd = st & BIT(0);
  break;

  default:
  break;
  }

  return timer_print_config(timer,field,val);
}



=======
#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
#define TIMER_SEL(timer) (timer << 6)

int timer_hook_id = 0;
int cnt = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint16_t f = (uint16_t)(TIMER_FREQ / freq);
  uint8_t status = 0;
  if(timer_get_conf(timer, &status)){
    return 1;
  }
  status &= 0x0F;
  uint8_t cw = TIMER_SEL(timer) | status;
  cw |= TIMER_LSB_MSB;
  if(sys_outb(TIMER_CTRL, cw)){
    return 1;
  }
  uint8_t lsb = 0;
  uint8_t msb = 0;
  if(util_get_LSB(f, &lsb)  || util_get_MSB(f,&msb)){
    return 1;
  }
  if(sys_outb(0x40 + timer, lsb)){
    return 1;
  }
  if(sys_outb(0x40 + timer, msb)){
    return 1;
  }
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = timer_hook_id;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&timer_hook_id);
}

void (timer_int_handler)() {
  ++cnt;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(timer > 2){
    return 1;
  }
  uint32_t rb = (uint32_t)TIMER_RB_CMD|TIMER_RB_COUNT_|TIMER_RB_SEL(timer);
  int out_flag = sys_outb(TIMER_CTRL, rb);
  if(out_flag == 1){
    return 1;
  }

  return util_sys_inb(0x40 + timer, st);

}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  union timer_status_field_val val;
  switch(field){
    case tsf_all: {
      val.byte = st;
      break;
    }
    case tsf_initial: {
      enum timer_init init;
      st = st << 2;
      st = st >> 6;
      if(st == 1){
        init = LSB_only;
      } else if (st == 2){
        init = MSB_only;
      } else if (st == 3){
        init = MSB_after_LSB;
      } else {
        init = INVAL_val;
      }
      val.in_mode = init;
      break;
    }
    case tsf_mode: {
      uint8_t mask = ~BIT(2);
      st = st << 4;
      st = st >> 5;
      if(st == 6 || st == 7){
        st &= mask;
      }
      val.count_mode = st;
      break;
    }
      
    case tsf_base: {
      uint8_t mask = 1;
      st = st & mask;
      val.bcd = st;
      break;
    }
    default:
      return 1;

  }
  
  return timer_print_config(timer, field, val);

}
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
