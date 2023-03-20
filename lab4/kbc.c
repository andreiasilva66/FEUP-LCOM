#include <lcom/lcf.h>
#include "kbc.h"
#include "i8042.h"

int hook = 3;
uint8_t data = 0;

int(kbc_subscribe_int)(uint8_t *bit_no){
*bit_no = BIT(hook);
return sys_irqsetpolicy(IRQ_12,IRQ_REENABLE | IRQ_EXCLUSIVE,&hook);
}

int(kbc_unsubcribe_int)(uint8_t *bit_no){
return sys_irqrmpolicy(&hook);
}

int(buffer_reader)(int port, uint8_t* value){
  if(sys_outb(port,value)){
    printf("unable to read the port %d", port);
    return EXIT_FAILURE;
  };
}

int(out_buffer_data_reader)(){

  uint8_t stat; 
  uint8_t tries = 10;


  while(tries != 0){
  kbc_status_reader(&stat);
  if(stat & (KBC_PAR_ERROR | KBC_TMT_ERROR)){
    printf("PARTY OR TIMEOUT ERROR");
    return EXIT_FAILURE;
  }
  if(!stat & KBC_AUX_MOUSE){
    printf("Mouse not selected in byte command");
    return EXIT_FAILURE;
  }
  if(!stat & OUT_BFF_FULL){ 
    tickdelay(micros_to_ticks(WAIT_KBC));
    tries--;
    continue;
  }
 return buffer_reader(OUT_BUF,&data);

  }
  return 1;
}

int(kbc_status_reader)(uint8_t* status){

  if(utils_sys_inb(KBC_ST_REG,status)){
    printf("Error reading status");
    return EXIT_FAILURE;
  }

  return 0;
}