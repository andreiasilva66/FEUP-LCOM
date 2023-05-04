// IMPORTANT: you must include the following line in all your C files
#include "kbc.h"
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

int hook;
int cnt;
uint8_t timmer;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapacked" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}
enum t12332_time_units {

  miliseconds,
  microseconds,
  seconds
};

int(pp_test_alarm)(int timer, int interval, enum t13223_time_units unit) {

  int hook = 3;
  uint8_t irq_set = BIT(hook);

  subscribe_int(&hook);
  int r, ipc_status;
  message msg;
  int time;
  uint8_t timerr;
  bool printed = false;

  switch (unit) {

    case miliseconds:
      time = 0x00;

    case microseconds:
      time = 0x01;

    case seconds:
      time = 0x02;
  }
  switch (timer) {

    case 0:
      timerr = 0x00;
    case 1:
      timerr = BIT(6);
    case 2:
      timerr = BIT(7);
  }
  uint8_t Ctrl_Word = timerr | BIT(4) | time;
  writter(0x23, Ctrl_Word);
  uint8_t MSB = get_MSB(interval);
  uint8_t LSB = get_LSB(interval);

  writter(0x20 + timer, LSB);
  writter(0x20 + timer, LSB);

  while (printed == false) { /* Run until it has exceeeded time*/
    /* Get a request message */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set) {
            timer_ih();
            pp_print_alarm(timer,interval,unit);
            printed = true;


          }
          break;
          default:
          break;
      }
    }
  }
}

int(subscribe_int)(uint8_t *bit_no) {
  hook = *bit_no;
  return sys_irqsetpolicy(10, IRQ_REENABLE, &hook);
}

int(unsub)(uint8_t *bit_no) {
  return sys_irqrmpolicy(&hook);
}

int(writter)(int port, uint8_t value) {
  sys_outb(port, value);
  return 0;
}

int(writter)(int port, uint8_t value) {
  sys_outb(port, value);
  return 0;
}

uint8_t(get_LSB)(uint16_t *value) {
  uint8_t res = (uint8_t) *value;
  return res;
}

uint8_t(get_MSB)(uint16_t *value) {
  uint8_t res = (uint8_t) *value >> 8;
  return res;
}


void(timer_ih)(){
  uint8_t stat;
  if(sys_inb(0x23,&stat) != 0) return 1;
  if(((stat & BIT(0)) && timmer == 0) || ((stat & BIT(1)) && timmer == 2) || ((stat & BIT(3)) && timmer == 3)) return 0;

}
