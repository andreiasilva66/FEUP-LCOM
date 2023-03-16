#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>



#define KBC_ESC 0x81
#define KBC_OUT_BFR 0x60
#define KBC_CMD_RED 0x60
#define KBC_ST_REG 0x64
#define KBC_CMD_REG 0x64
#define KBC_OBF 0xC0
#define KBC_PAR_ERR BIT(7)
#define KBC_TO_ERR  BIT(6)
#define WAIT_KBC 2000
#define TWO_SCAN_CODE 0xE0
#define KBC_STAT_REG 0x64
#define KBC_2BYTE_CODE 0xE0
#define KBC_MSB_SCNCD BIT(7)
#define KBC_PARITY BIT(7)
#define KBC_TIMEOUT BIT(6)
#define KBC_AUX BIT(5)
#define KBC_OUT_FUL BIT(0)
#define KBC_ST_IBF BIT(1)
#endif
