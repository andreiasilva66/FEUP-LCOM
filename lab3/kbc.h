#ifndef LAB3_KBC_H
#define LAB3_KBC_H



#include <stdbool.h>
#include <stdint.h>



int (kbc_activate_interrupts)();

int (kbc_get_status)();

int(kbc_get_scancode)();

void (kbc_ih) ();

int (kbd_print_scancode)(bool make, uint8_t size, uint8_t *bytes);

int (kbd_print_no_sysinb) (uint32_t cnt);

int (kbc_subscribe_int)(uint8_t *irq_set);

int (kbc_unsubscrive_int)();

#endif // LAB3_KBC_H
