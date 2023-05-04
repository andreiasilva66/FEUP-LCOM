#include <lcom/lcf.h>

#include "keyboard.h"
#include "timer.c"
#include "videocard.h"

extern vbe_mode_info_t info;
extern uint8_t scancode;
extern int counter;

int main(int argc, char *argv[]) {

  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/Labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/Labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(waiting_ESC_key)() {

  int ipc_status;
  message msg;
  uint8_t keyboard_mask;

  if (keyboard_subscribe_interrupts(&keyboard_mask) != 0)
    return 1;

  while (scancode != BREAK_ESC) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("driver_receive failed");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & keyboard_mask)
            kbc_ih();
          break;
        default:
          break;
      }
    }
  }

  if (keyboard_unsubscribe_interrupts() != 0)
    return 1;
  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {

  if (set_graphic_mode(mode) != 0)
    return 1;
  sleep(delay);
  vg_exit();

  // Mudança para o modo gráfico
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

  set_frame_buffer(mode);
  set_graphic_mode(mode);
  uint32_t new_color;
  uint16_t collor;
  normalize_color(color, new_color);
  if (info.BitsPerPixel == 16)
    collor = new_color;
  vg_draw_rectangle(x, y, width, height, color);
  waiting_ESC_key();
  vg_exit();

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

  set_frame_buffer(mode);
  set_graphic_mode(mode);

  unsigned int Xres = info.XResolution;
  unsigned int Yres = info.YResolution;
  unsigned int I_X = Xres / no_rectangles;
  unsigned int I_Y = Yres / no_rectangles;

  for (int i = 0; i < no_rectangles; i++) {
    for (int j = 0; j < no_rectangles; i++) {
    }
  }

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

  set_frame_buffer(0x105);
  set_graphic_mode(0x105);
  print_xpm(xpm,x,y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  return 1;
}
