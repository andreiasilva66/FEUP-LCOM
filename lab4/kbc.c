#include "kbc.h"
#include "i8042.h"
#include <lcom/lcf.h>

int hook, hook2, cnt = 0;
uint8_t data;
int16_t delta_x = 0, delta_y = 0;
bool vertex = false;
extern bool done;
typedef enum { INIT,
               DRAW,
               COMP } state_t;
 static state_t st = INIT;

void(gesture_handler)(struct mouse_ev *evt, uint8_t x_len, uint8_t tolerance) {

  
  

  switch (st) {
    case INIT:
      printf("INIT ");
      if ((evt->type == LB_PRESSED) || (evt->type == RB_PRESSED && vertex == true)  ) {
        st = DRAW;
      }
      break;
    case DRAW:

      printf("DRAW-%d-%d-%d-%d ",vertex,delta_x,evt->delta_x,delta_y );
      if (   evt->type == LB_RELEASED && vertex == false) {
        if ((delta_x >= x_len) && (delta_y / delta_x) > 1) {
          printf("DRAW 1");
          delta_x = 0;
          delta_y = 0;
          vertex = true;
          st = INIT;
        }
        else {
          printf("DRAW 2");
          vertex = false;
          st = INIT;
        }
      }
      else if (evt->type == MOUSE_MOV && vertex == false) {
if(evt->delta_x <= 0 || evt->delta_y >= 0)
        if (abs(evt->delta_x > tolerance) || abs(evt->delta_y > tolerance)) {
          printf("DRAW 3 ");
          st = INIT;
          vertex = false;
        }

        if (evt->delta_x != 0 && (evt->delta_y) / (evt->delta_x) <= 1 && vertex == false){
          st = INIT;
        printf("DRAW 4 ");}
        else {
          printf("DRAW 5 ");
          delta_x += evt->delta_x;
          delta_y += evt->delta_y;
        }
      }

      else if (evt->type == RB_RELEASED && vertex == true) {

        if ((delta_x >= x_len) && (delta_y / delta_x) < -1) {
          printf("DRAW 6");
          st = COMP; 
          done = true; 
          
          //return true;
        }
        else {
          printf("DRAW 7");
          vertex = false;
          st = INIT;
        }
      }
      else if (evt->type == MOUSE_MOV && vertex == true) {if(evt->delta_x <= 0 || evt->delta_y >= 0)
        if (abs(evt->delta_x > tolerance) || abs(evt->delta_y > tolerance)) {
          printf("DRAW 8");
          st = INIT;
          vertex = false;
        }

        if (evt->delta_x != 0 && (evt->delta_y) / (evt->delta_x) >= -1 && vertex == true) {
          st = INIT;
          vertex = false;
          printf("DRAW 9");
        }
        else {
          printf("DRAW 10");
          delta_x += evt->delta_x;
          delta_y += evt->delta_y;
        }
      }
      
      break;

    case COMP:

      printf("COMplete");
      done = true;
      break;
  }
}
void time_int_handlerr() {
  cnt++;
}

int(timer_subscribe_int)(uint8_t *bit_no) {
  hook2 = *bit_no;
  return sys_irqsetpolicy(0, IRQ_REENABLE, &hook2);
}

int(mouse_subscribe_int)(uint8_t *bit_no) {
  hook = *bit_no;
  return sys_irqsetpolicy(12, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook);
}

int(mouse_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook);
}
int(timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook2);
}

int(kbc_status_reader)(uint8_t *stat) {
  if (util_sys_inb(KBC_STAT_REG, stat))
    return EXIT_FAILURE;

  return 0;
}

int(buffer_reader)(int port, uint8_t *value) {
  if (util_sys_inb(port, value))
    return EXIT_FAILURE;
  return 0;
}

int(buff_writter)(int port, uint8_t value) {
  if (sys_outb(port, value)) {
    return EXIT_FAILURE;
  }
  return 0;
}

int(data_reader)(int port) {

  int tries = 5;
  uint8_t status;

  while (tries) {

    if (kbc_status_reader(&status)) {
      printf("error reading status");
      return EXIT_FAILURE;
    }

    if (status & KBC_OBF) {

      if (buffer_reader(KBC_OUT_BUF, &data)) {
        printf("Error reading buffer");
        return EXIT_FAILURE;
      }
    }

    if (!(status & (KBC_PARITY | KBC_TIMEOUT)) && (status & KBC_AUX)) {

      //  printf("leitura bem sucedia %d   ", tries);
      return 0;
    }

    tickdelay(micros_to_ticks(DELAY_US));
    tries--;
  }

  return 1;
}

int(cmd_writter)(int port, uint8_t value) {

  int tries = 5;
  uint8_t status;

  while (tries) {

    kbc_status_reader(&status);

    if ((status & KBC_IBF) == 0) {
      sys_outb(port, value);
      return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US));
    tries--;
  }

  return 1;
}

void(pack_setter)(struct packet *pack) {
  pack->rb = pack->bytes[0] & BIT(1);
  pack->mb = pack->bytes[0] & BIT(2);
  pack->lb = pack->bytes[0] & BIT(0);
  pack->delta_x = (pack->bytes[0] & BIT(4)) ? (0xFF00 | pack->bytes[1]) : (pack->bytes[1]);
  pack->delta_y = (pack->bytes[0] & BIT(5)) ? (0xFF00 | pack->bytes[2]) : (pack->bytes[2]);
  pack->x_ov = pack->bytes[0] & BIT(6);
  pack->y_ov = pack->bytes[0] & BIT(7);
}

void(mouse_ih)() {

  // printf("mouse_ih()  ");
  data_reader(KBC_OUT_BUF);
}

int(mouse_write_cmd)(uint8_t cmd) {
  uint8_t ack_flag;
  do {
    cmd_writter(0x64, 0xD4);
    cmd_writter(0x60, cmd);
    util_sys_inb(KBC_IN_BUF_ARG, &ack_flag);
  } while (ack_flag != KBC_ACK);
  return 0;
}
