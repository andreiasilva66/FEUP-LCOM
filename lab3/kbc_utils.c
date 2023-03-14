
#include <lcom/lcf.h>
#include "i8042.h"
#include "kbc_utils.h"




uint8_t data;
int hook; 

void (kbc_ih)(){

  if(data_reader() != 0){
    printf("error reading data");
    return;
  }

  return;

}

int (KBC_subscribe_int)(uint8_t *bit_no) {
   hook = *bit_no;
    return sys_irqsetpolicy(1,IRQ_REENABLE | IRQ_EXCLUSIVE,&hook);
}

int (KBC_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook);
}

int (status_reader)(uint8_t *stat){

if(util_sys_inb(KBC_STAT_REG,stat) != 0){
  printf("Error checking the status");
  return 1;
}
 
 return 0;

}

int (buffer_reader)(int port){

  return util_sys_inb(port,&data);

}

int (data_reader)(){

  uint8_t stat;

  status_reader(&stat);

  if(stat & KBC_OUT_FUL){

    buffer_reader(KBC_OUT_BFR);

  }

  if((stat & (KBC_PARITY | KBC_TIMEOUT))){
    printf("Error in bit 7 or 6 or not keyboard ");
    return EXIT_FAILURE;
  }

  return 0;
}



