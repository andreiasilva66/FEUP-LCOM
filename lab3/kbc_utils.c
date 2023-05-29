
#include "kbc_utils.h"
#include "i8042.h"
#include <lcom/lcf.h>

// perguntar sobre a note 2 do slide 19 do teclado

uint8_t data = 0x00;
int hookKBC;
int counter = 0;

void(kbc_ih)() {

  if (data_reader() != 0) {
    printf("error reading data");
    return;
  }

  return;
}

int(KBC_subscribe_int)(uint8_t *bit_no) {
  hookKBC = *bit_no;
  return sys_irqsetpolicy(1, IRQ_REENABLE | IRQ_EXCLUSIVE, &hookKBC);
}



int(KBC_unsubscribe_int)() {
  return sys_irqrmpolicy(&hookKBC);
}

int(status_reader)(uint8_t *stat) {

  if (util_sys_inb(KBC_STAT_REG, stat) != 0) {
    printf("Error checking the status");
    return 1;
  }

  return 0;
}

int(buffer_reader)(int port) {

  return util_sys_inb(port, &data);
}

int(data_reader)() {

  int tries = 10;
  uint8_t stat;

  while (tries != 0) {
    status_reader(&stat);

    if ((stat & (KBC_PARITY | KBC_TIMEOUT)) || (((stat & KBC_AUX) != 0))) {
      printf("Error in bit 7 or 6 or not keyboard ");
      return EXIT_FAILURE;
    }

    if ((stat & KBC_OUT_FUL) != 0) {

      buffer_reader(KBC_OUT_BFR);
      return 0;
    }

    else {

      tickdelay(micros_to_ticks(WAIT_KBC)); // porque meter tickdelay?
      tries--;
    }
    // onde colocar o return
  }
  return 1;
}

int(buffer_writter)(int port, uint8_t *cmd) {

  int tries = 10;
  uint8_t stat;

  while (tries != 0) {

    if (status_reader(&stat) != 0) {
      printf("problem reading status");
      return EXIT_FAILURE;
    }

    if ((stat & KBC_ST_IBF) == 0) {
      uint8_t entry = 0x60;
      //uint32_t entry2 = (uint32_t) *cmd;
      sys_outb(KBC_CMD_REG, entry);
        //sys_outb(0x60, entry2);
        sys_outb(0x60, *cmd);
      return 0;
    }
    tickdelay(micros_to_ticks(WAIT_KBC));
    tries--;
  }
  return 1;
}

int(KBD_activate_interrupt)() {

  uint8_t stat;
  uint8_t commando = 0x20;
 // printf("etapa1");
  buffer_writter(KBC_ST_REG, &commando);
 // printf("etapa2");
  buffer_reader(0x60);
 // printf("etapa3");
  stat = data;
//  printf("etapa4 %d",stat);
  stat = stat | (BIT(0));
 // printf("etapa5 %d",stat);
  commando = 0x60;  
//  printf("etapa5");
  buffer_writter(KBC_ST_REG, &commando);
 // printf("etapa6 \n");
  buffer_writter(KBC_OUT_BFR, &stat);
 // printf("sussy files %d", stat);
  

  return 0;
}
