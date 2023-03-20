#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "i8042.h"

int(kbc_subscribe_int)(uint8_t *bit_no);
int(kbc_unsubcribe_int)();
int(buffer_reader)(int port, uint8_t* value);
int(buffer_writter)(int port, uint8_t* value);
int(out_buffer_data_reader)(),
int(kbc_status_reader)(uint8_t* status);

