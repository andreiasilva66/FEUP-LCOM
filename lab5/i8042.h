<<<<<<< HEAD

#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define IRQ_KEYBOARD    1
#define IRQ_MOUSE       12

#define BREAK_ESC       0x81
#define MAKE_CODE       BIT(7)
#define TWO_BYTES       0xE0
#define ENABLE_INT      BIT(0)

#define TIMEOUT_ERROR   BIT(6)
#define PARITY_ERROR    BIT(7)
#define FULL_OUT_BUFFER BIT(0)
#define FULL_IN_BUFFER  BIT(1)

#define KBC_STATUS_REG  0x64
#define KBC_IN_CMD      0x64
#define KBC_OUT_CMD     0x60
#define KBC_READ_CMD    0x20
#define KBC_WRITE_CMD   0x60

#define WAIT_KBC        20000
#define MAX_ATTEMPS     10

#define MOUSE_LB            BIT(0)
#define MOUSE_RB            BIT(1)
#define MOUSE_MB            BIT(2)
#define FIRST_BYTE          BIT(3)
#define MOUSE_X_SIGNAL      BIT(4)
#define MOUSE_Y_SIGNAL      BIT(5)
#define MOUSE_X_OVERFLOW    BIT(6)
#define MOUSE_Y_OVERFLOW    BIT(7)
#define DISABLE_DATA_REPORT 0xF5
#define ENABLE_DATA_REPORT  0xF4
#define ENABLE_STREAM_MODE  0xEA
#define MOUSE_READ_DATA     0xEB
#define WRITE_BYTE_MOUSE    0xD4

#define ACK 0xFA    
#define NACK 0xFE

#endif /* _LCOM_I8042_H_ */
=======
#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define DELAY_US 20000
#define KBD_ESC 0x81
#define KBD_CMD_REG 0x64


#define KBD_IRQ 1

#define KBD_ST_IBF BIT(1)
#define KBD_OUT_BUF 0x60

#define KBD_PAR_ERR BIT(7)
#define KBD_TO_ERR BIT(6)


#define TWO_BYTE 0xE0
#define MAKE 0x80

#define OUT_BUF 0x60
#define IN_BUF 0x64
#define IN_BUF_ARGS 0x60
#define STAT_REG 0x64

#define READ_CMD_BYTE 0x20
#define WRITE_CMD_BYTE 0x60
#define KBD_REENABLE_INT BIT(0)

#endif
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
