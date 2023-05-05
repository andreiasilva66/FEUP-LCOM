#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {

  *lsb = (uint8_t) val;
<<<<<<< HEAD
  
=======
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e

  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {

  uint16_t arcade = val >> 8;

  *msb = (uint8_t) arcade;

<<<<<<< HEAD


  return 1;
=======
  return 0;
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
}

int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t val32;

<<<<<<< HEAD
  if(sys_inb(port, &val32) != 0) return EXIT_FAILURE;
=======
  sys_inb(port, &val32);
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
   
  *value = (uint8_t) val32;

  return 0;
<<<<<<< HEAD


  /* To be implemented by the students */

=======
>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
}
