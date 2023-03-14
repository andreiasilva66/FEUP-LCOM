#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {

  *lsb = (uint8_t) val;
  

  return 1;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */

    uint16_t arcade = val >> 8;

    *msb = (uint8_t) arcade;



  return 1;
}

int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t val32;

  if(sys_inb(port, &val32) != 0) return EXIT_FAILURE;
   
  *value = (uint8_t) val32;

  return 0;


  /* To be implemented by the students */

}
