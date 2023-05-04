#include "i8042.h"

#define DELAY_US 20000


int(mouse_subscribe_int)(uint8_t * bit_no);
int(mouse_write_cmd)(uint8_t cmd);
void(mouse_ih)();
void(pack_setter)(struct packet *pack);
int(cmd_writter)(int port, uint8_t value);
int(data_reader)(int port);
int(buff_writter)(int port, uint8_t value);
int(buffer_reader)(int port, uint8_t *value);
int(kbc_status_reader)(uint8_t *stat);
int(mouse_unsubscribe_int)();
int(mouse_subscribe_int)(uint8_t *bit_no);
void gesture_handler(struct mouse_ev *evt, uint8_t x_len, uint8_t tolerance);
void(timer_int_handlerr)();


