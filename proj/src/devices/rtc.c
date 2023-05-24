#include "rtc.h"

// Global Variables
rtc_info info;


// Methods
int rtc_output(uint8_t command, uint8_t *output){
    if(sys_outb(RTC_INPUT_PORT, command) != 0){
        return 1;
    }
    if(util_sys_inb(RTC_OUTPUT_PORT, output) != 0){
        return 1
    }
    return 0;
}

int rtc_available(){
    uint8_t output;
    if(rtc_output(RTC_AVAILABLE, &output) != 0){
        return 1;
    }
    return result & BIT(7);
}