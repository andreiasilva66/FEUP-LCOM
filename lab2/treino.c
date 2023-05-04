#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

#define BIT(n) (1 << (n))
int hook_id = 0;
bool one_shot = false; 
uint8_t timer;
int port = 5;

void timer_ih(){ 
uint8_t stat;
if(sys_inb(port,&stat)) return 1;

if(timer == 0 && (stat & BIT(1)) || (timer == 2)) one_shot = true;

}

int function(int time, int interval,enum sus unit){

  uint8_t ctrl;

  switch(time){

    case 0:

      ctrl |= BIT(1);
      break; 

    case 1:

      ctrl |= BIT(2);
      break;

  }

  switch(unit){

    case mili: 
      ctrl |=
      break;

  default:
  return 1;
  }

  if(sys_outb(CTRL_REG_ST,ctrl)) return 1;

  uint8_t lsb = (uint8_t) interval;
  uint8_t msb = (uint8_t)  interval >> 8;

  if(sys_outb(INPORT,lsb)) return 1;
  if(sys_outb(INPORT,msb)) return 1;
   
   bool end = false;
   

}






}

