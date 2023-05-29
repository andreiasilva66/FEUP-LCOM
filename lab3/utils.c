<<<<<<< HEAD
#include <lcom/lcf.h>

#include <stdint.h>

#ifdef LAB3
uint32_t cntt = 0;
#endif

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
  #ifdef LAB3
  cntt++;
  #endif
   
  *value = (uint8_t) val32;

  return 0;


  /* To be implemented by the students */

}

int (util_sys_outb)(int port, uint8_t *cmd){

  //uint32_t cmdd = (uint32_t) *cmd;

  if(sys_outb(port,*cmd) != 0) return EXIT_FAILURE;

  #ifdef LAB3
  cntt++;
  #endif

  return 0;


}
=======
#include <lcom/lcf.h>

#include <stdint.h>

int count = 0;

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb == NULL){
    return 1;
  }
  *lsb = (uint8_t) val;
  return OK;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb == NULL){
    return 1;
  }
  *msb = (uint8_t) (val >> 8);
  return OK;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t val = *value;
  int flag = sys_inb(port, &val);
  *value = val;
  count++;
  return flag;
}

>>>>>>> c35a06cedcec12ab30a0b352a92eb14825bd1a0e
