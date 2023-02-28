#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {

  *lsb = (uint8_t) val;

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {

  uint16_t arcade = val >> 8;

  *msb = (uint8_t) arcade;

  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t val32;

  sys_inb(port, &val32);
   
  *value = (uint8_t) val32;

  return 0;
}
