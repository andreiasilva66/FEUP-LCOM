#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int count = 0;
int hook;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  
  if(freq<19 || freq>TIMER_FREQ){
    return 1;
  }
  
  uint16_t divisor = TIMER_FREQ/freq;

  uint8_t msb = 0;
  uint8_t lsb = 0;

  if(util_get_LSB(divisor,&lsb) || util_get_MSB(divisor,&msb)) 
    return 1;

  uint8_t st =0;
  if(timer_get_conf(timer,&st))
    return 1;
  
  st = (st & 0xCF) | TIMER_LSB_MSB;
  
   
  return sys_outb(TIMER_CTRL,st) || sys_outb(TIMER_0+timer,lsb) || sys_outb(TIMER_0+timer,msb);

}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */

  hook=*bit_no;

  return sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook);
  
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  return  sys_irqrmpolicy(&hook);

}

void (timer_int_handler)() {
  /* To be implemented by the students */
  
  count++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  /* To be implemented by the students */
  
  uint8_t rbc = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  if(sys_outb(TIMER_CTRL,rbc))
    return 1;
  
  return util_sys_inb(TIMER_0+timer,st);
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  /* To be implemented by the students */
  
  union timer_status_field_val val;


  switch(field){
    case tsf_all:
      val.byte = st;
      break;
    case tsf_initial:
      val.in_mode = (st & (BIT(4)|BIT(5)))>>4;
      break;
    case tsf_mode:
      val.count_mode = (st & (BIT(1) | BIT(2) | BIT(3))) >>1;
      break;
    case tsf_base:
      val.bcd = st & BIT(0); 
  }

  return timer_print_config(timer,field,val);
}
