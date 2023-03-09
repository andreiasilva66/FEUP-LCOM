#include <lcom/lcf.h>
#include <stdint.h>

#ifdef LAB3
extern int sys_IN_CALLS;
#endif

int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t val32 = 0x00;

  #ifdef LAB3
  sys_IN_CALLS ++;
  #endif

  if(sys_inb(port, &val32) != 0){
    return 1;
  }

  sys_inb(port, &val32);

  *value = (uint8_t) val32;

  return 0;
}
