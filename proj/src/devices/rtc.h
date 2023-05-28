#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include "rtc_Macros.h"

// RTC Data

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} Rtc;

// Methods

int (rtc_output)(uint8_t command, uint8_t *output);
int (rtc_available)();
int (rtc_binary_mode)();
uint8_t (rtc_convert_to_binary)(uint8_t bcd);
int (rtc_update)();


#endif
