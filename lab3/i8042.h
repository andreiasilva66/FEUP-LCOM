#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

/* I/O Port Adresses */
#define KBC_IN_BUD 0x64
#define KBC_OUT_BUF 0x60
#define KBC_STATUS_REGISTER 0x64      // reading the KBC state
#define KBC_NOT_NAME 0x64             // writing KBC commands

/* KBC KEYCODES */
#define MAKECODE_ESC 0x01
#define BREAKCODE_ESC 0x81

/* Status Byte Parsing */
#define KBC_NONE 0                    // Usefull when only need to know output buffer
#define KBC_OUT_BUFFER_FULL BIT(0)
#define KBC_IN_BUFFER_FULL BIT(1)
#define KBC_INHIBIT_FLAG BIT(4)       // 0 if keyboard is inhibited
#define KBC_AUX BIT(5)
#define KBC_TIMEOUT_ERR BIT(6)
#define KBC_PARITY_ERR BIT(7)

/* KBC COMMANDS */
#define KBC_WRITE_CMD 0x60
#define KBC_READ_CMD 0x20

/* KBC INTERRUPTS */
#define KBC_IRQ 1;


#endif