#ifndef _KBC_UTILS_H_
#define _KBC_UTILS_H_
#include <lcom/lcf.h>



int (status_reader)(uint8_t *stat);
int (buffer_reader)(int port);
int (data_reader)();
void (kbc_ih)();
int (KBC_subscribe_int)(uint8_t *bit_no);
int (KBC_unsubscribe_int)();
int (buffer_writter)(int port, uint8_t *cmd);
int(KBD_activate_interrupt)();





#endif





