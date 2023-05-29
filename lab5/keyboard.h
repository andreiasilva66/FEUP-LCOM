<<<<<<< HEAD
#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"

int (keyboard_subscribe_interrupts)(uint8_t *bit_no);

int (keyboard_unsubscribe_interrupts)();

void (kbc_ih)();

int (keyboard_restore)();

#endif
=======
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"

void(kbc_ih)();

int(kbc_subscribe_int)(uint8_t *bit_no);

int(kbc_unsubscribe_int)();

int(kbc_get_status)(uint8_t *st);

int(kbc_read_out_buffer)(uint8_t *data);

int(kbc_print_codes)();

int(kbc_send_cmd)(uint8_t port, uint8_t cmd);

int(kbc_reenable_int)();

int check_status(uint8_t st);

#endif

>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
