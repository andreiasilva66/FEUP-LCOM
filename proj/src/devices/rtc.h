#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>

// Macros

#define RTC_INPUT_PORT      0x70
#define RTC_OUTPUT_PORT     0x71

#define RTC_AVAILABLE               10
#define RTC_COUNTING_MODE           11

#define RTC_INTERRUPT_RQ    8

#define SECONDS    0
#define MINUTES    2
#define HOURS      4   
#define DAY        7
#define MONTH      8
#define YEAR       9

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
int (rtc_convert_to_binary)(uint8_t bcd);
int (rtc_update)();

int (rtc_int_handler)();
int (rtc_subscribe_int)(uint8_t *bit_no);
int (rtc_unsubscribe_int)();

#endif