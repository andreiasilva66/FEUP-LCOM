#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
#define TIMER_SELECT(timer) (timer << 6)

uint32_t timerCount = 0;
int hook;

<<<<<<< HEAD
 uint32_t cnt = 0;
 int hook = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  uint8_t st;
  uint8_t lsb;
  uint8_t msb;
  
  if(timer_get_conf(timer,&st) != 0){
    return EXIT_FAILURE;
  }

  if(freq < 19 || freq > TIMER_FREQ) return 1; // 2^16 --------- TIMER_FREQ/freq --------- 

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
=======
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if(freq < (1193181 / 0xffff) || freq > 1193181){
    return 1;
  }
  uint8_t control_word = 0;
  uint16_t f;
  uint8_t lsb;
  uint8_t msb;

  timer_get_conf(timer, &control_word);  // Obter 4 bits menos significativos do timer

  control_word <<= 4;
  control_word >>= 4;

  control_word |= TIMER_SELECT(timer); // Seleccionar o timer
  control_word |= TIMER_LSB_MSB;  // Seleccionar as partes do contador do TIMER que se pretende alterar
  sys_outb(TIMER_CTRL, control_word);  // Passar control word para TIMER CONTROL
  f = TIMER_FREQ / freq;
  util_get_LSB(f, &lsb);
  util_get_MSB(f, &msb);
  sys_outb(0x40 + timer, lsb);  // Passar lsb para o timer 0;
  sys_outb(0x40 + timer, msb);  // Passar msb para o timer 0;
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  hook = *bit_no;
<<<<<<< HEAD
    
    return sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook);

 
=======
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook);
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook);
<<<<<<< HEAD

}

void (timer_int_handler)() {
  
  cnt++;
  
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if( timer < 0 || timer > 2) return EXIT_FAILURE;
  uint8_t read_back_command = TIMER_RB_CMD | TIMER_RB_SEL(timer) | TIMER_RB_COUNT_; 
  sys_outb(TIMER_CTRL,read_back_command);
  util_sys_inb(TIMER_0 + timer,st); 
  return 0;
=======
}

void (timer_int_handler)() {
  timerCount++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

  uint8_t read_back_command = TIMER_RB_CMD | TIMER_RB_SEL(timer) | TIMER_RB_COUNT_; 
  sys_outb(TIMER_CTRL,read_back_command);
  return util_sys_inb(0x40 + timer, st);
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {


 union timer_status_field_val val;

<<<<<<< HEAD
  switch (field)
  {

  printf("field %s", field);
  case tsf_all:
    val.byte = st;
    break;

  case tsf_initial:

  printf("st %d \n",st);
  st <<= 2;
  printf("st %d \n",st);
   st >>= 6;
   printf("st %d \n",st);

    switch (st){
    
    case 0x01:
    printf("mode 1 \n");
    val.in_mode = LSB_only;
      break;

    case 0x02:
    
    printf("mode 2 \n");
    val.in_mode = MSB_only;
    break;

    case 0x03:
    
    printf("mode 3 \n");
    val.in_mode = MSB_after_LSB;
    break;  
    
    default:
    
    printf("mode 4");
    val.in_mode = INVAL_val;
      break;

    }
    break;

  case tsf_mode:
  printf("sss  ST %d \n",st);
  
  st =(st & (BIT(3) | BIT(2) | BIT(1)));
  st >>= 1;
  printf("ST, %d \n",st);

  if(st == 0x06) st = 0x02;
  if(st == 0x07) st = 0x03;
 printf("ST, %d \n",st);
  val.count_mode = st;
  break;

  case tsf_base:
  printf("s");

  val.bcd = st & BIT(0);
  break;

  default:
  printf("fdafs");  
  break;
  }

=======
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
    break;
  }

  case tsf_mode:{
    uint8_t mask = ~BIT(2);
    st <<= 4;
    st >>= 5;

    if(st == 7 || st == 6){ // Compatibilidade com produtos Intel como referido na ficha
      st &= mask;
    }

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

>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
  return timer_print_config(timer,field,val);
}



