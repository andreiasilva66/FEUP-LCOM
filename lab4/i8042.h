#ifndef LCOM_I8042_H_
#define LCOM_I8042_H_
#include <lcom/lcf.h>


#define OUT_BUF 0x64
#define IRQ_12 12 // pq é que isto n está a ler
#define KBC_ST_REG 0x64
#define KBC_PAR_ERROR BIT(7);
#define KBC_TMT_ERROR BIT(6);
#define KBC_AUX_MOUSE BIT(5);
#define OUT_BFF_FULL BIT(0);

#endif