
// IMPORTANT: you must include the following line in all your C files
#include "kbc.h"
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

extern uint8_t data;
extern int cnt;
bool done = false;
typedef enum { INIT,
               DRAW,
               COMP } state_t;
extern  state_t st;

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

int(mouse_test_packet)(uint32_t cnt) {

  uint8_t hook = 3;
  uint8_t irq_set = BIT(hook);
  int r, ipc_status, counter = 0;
  message msg;
  struct packet pack;
  bool startPacket;

  mouse_write_cmd(MOUSE_EN_DATA_REP);
  mouse_subscribe_int(&hook);

  while (cnt != 0) { /* Run until it has exceeeded time*/
    /* Get a request message */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set) {
            mouse_ih();

            if (data & BIT(3)) {
              startPacket = true;
            }
            if (startPacket) {
              pack.bytes[counter] = data;
              counter++;
              // printf("iteraçao %d",counter);
            }
            if (counter == 3) {
              pack_setter(&pack);
              mouse_print_packet(&pack);
              startPacket = false;

              counter = 0;
              // printf("iteraçao2  ");
            }
            // printf("  count %d ", counter);
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
  }

  mouse_unsubscribe_int();
  mouse_write_cmd(MOUSE_DIS_DATA_REP);

  return 0;
}

int(mouse_test_async)(uint8_t idle_time) {
  uint8_t hook = 4;
  uint8_t hook2 = 6;
  uint8_t irq_set = BIT(hook), irq_set2 = BIT(hook2);

  mouse_write_cmd(MOUSE_EN_DATA_REP);
  mouse_subscribe_int(&hook);
  timer_subscribe_int(&hook2);

  int r, ipc_status, counter = 0;

  message msg;
  struct packet pack;
  bool startPacket = false;

  while (cnt / sys_hz() < idle_time) { /* Run until it has exceeeded time*/
    /* Get a request message */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set2) {

            cnt++;
            printf("%d ", cnt);
          }
          if (msg.m_notify.interrupts & irq_set) {

            mouse_ih();

            if (data & BIT(3)) {
              startPacket = true;
            }
            if (startPacket) {
              pack.bytes[counter] = data;
              counter++;
              // printf("iteraçao %d",counter);
            }
            if (counter == 3) {
              pack_setter(&pack);
              mouse_print_packet(&pack);
              startPacket = false;

              counter = 0;
            }
            cnt = 0;
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
  }

  mouse_unsubscribe_int();
  timer_unsubscribe_int();
  mouse_write_cmd(MOUSE_DIS_DATA_REP);

  return 0;
}




int(mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {

  uint8_t hook = 8;
  int irq_set = BIT(hook);
  int ipc_status, r;
  message msg;

   mouse_write_cmd(MOUSE_EN_DATA_REP);
  mouse_subscribe_int(&hook);

  bool startPacket;
  int counter = 0;
  struct packet pack;
  struct mouse_ev *event;
 
  

  while (!done) { /* Run until it has exceeeded time*/
    /* Get a request message */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
     switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
    if (msg.m_notify.interrupts & irq_set) {

      mouse_ih();
      

      if (data & BIT(3)) {
        startPacket = true;
      }
      if (startPacket) {
        pack.bytes[counter] = data;
        counter++;
        // printf("iteraçao %d",counter);
      }
      if (counter == 3) {
        pack_setter(&pack);
        //mouse_print_packet(&pack);

        event = mouse_detect_event(&pack);
        gesture_handler(event, x_len, tolerance);
       
        startPacket = false;
        counter = 0;
      }
      cnt = 0;
    }
    break;
    default:
      break; /* no other notifications expected: do nothing */
  }
}
printf("SSS");
  mouse_unsubscribe_int();
  mouse_write_cmd(MOUSE_DIS_DATA_REP);
  return 0; 
}


int(mouse_test_remote)(uint16_t period, uint8_t cnt) {

  
  return 1;
}
