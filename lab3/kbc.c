#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
#include <utils.h>
#include <i8042.h>

int kbc_hook=2;
uint8_t scancode =0;
uint8_t kbc_status;

int (kbc_get_status)(){
  return util_sys_inb(KB_STATUS,&kbc_status) || (kbc_status & KBC_PARITY_ERROR) || (kbc_status & KBC_TIMEOUT_ERROR);
}

int(kbc_get_scancode)(){
  if(OUTBUFFER_FULL & kbc_status){
    return util_sys_inb(OUT_BUF,&scancode);
  }
  return 1;
}


void (kbc_ih) (){   // status read 7 6 5 
  if(kbc_get_status())
    printf("Error in the kbc status");
  if(kbc_get_scancode())
    printf("Error getting the scancode");
}

int (kbc_subscribe_int)(uint8_t *irq_set){
  *irq_set = BIT(kbc_hook);
  return sys_irqsetpolicy(KEYBOARD_IRQ,IRQ_REENABLE|IRQ_EXCLUSIVE,&kbc_hook);  

}



int (kbc_unsubscrive_int()){
  return sys_irqrmpolicy(&kbc_hook);
}


int (kbc_activate_interrupts)(){
  uint8_t stat;

  sys_outb(KB_STATUS,READ_COMMAND_BYTE);

  util_sys_inb(OUT_BUF,&stat);
  stat |= OUTBUFFER_FULL;
  sys_outb(KB_STATUS,WRITE_COMMAND_BYTE);
  sys_outb(OUT_BUF,stat);

  return 0;
}
