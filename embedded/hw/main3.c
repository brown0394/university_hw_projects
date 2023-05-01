#include "stm32f10x.h"

// defind port
#define PORT_clock 0x40021000
#define PORT_B 0x40010C00
#define PORT_C 0x40011000
#define PORT_D 0x40011400


//defind offset
#define APB2ENR 0x18
#define CRL 0X00
#define CRH 0X04
#define IDR 0X08
#define BSRR 0X10
#define BRR 0X14

//joystict button
#define DOWN 0X04
#define LEFT 0X08
#define RIGHT 0X10
#define UP 0X20

// Register 주소 간편하게 쓰기위한 선언
#define reg *(volatile unsigned int *)

// LED 및 User s1 button setting
#define PD2 0x4 
#define PD3 0x8
#define PD4 0x10
#define PD7 0x80
#define PD11 0x800

_Bool check_push(){
  return !(reg(PORT_D+IDR) & PD11); // Push 됐다면 True 아니라면  False
}

int main(void)
{ reg (PORT_clock + APB2ENR) = 0x38; // clock enable PB, PC, PD
  reg (PORT_D+CRL) &=  ~0xF00FFF00; // Init mode PD2,PD3,PD4,PD7
  reg (PORT_D+CRL) = 0x30033300; // Configuration set output mode max Speed 50MHz PD2,PD3,PD4,PD7
  
  reg (PORT_C+CRL) &= ~0x0FFFF00;//Init mode PC2, PC3, PC4, PC5
  reg (PORT_C+CRL) = 0x0888800;//Configuration PC2, PC3, PC4, PC5
  reg (PORT_D+CRH) &= ~0xF000; // Init mode
  reg (PORT_D+CRH) = 0x8000; // Configuration set
  

  while(1) {
    
    if(!(reg(PORT_C+IDR) & UP)){ //up
      //printf("UP\n");
      if(check_push()) reg(PORT_D + BSRR) = PD7;
      else reg(PORT_D + BRR) = PD7;
    }
    else if(!(reg(PORT_C+IDR) & DOWN)){
      //printf("DOWN\n");
      if(check_push()) reg(PORT_D + BSRR) = PD3;
      else reg(PORT_D + BRR) = PD3;
    }
    else if(!(reg(PORT_C+IDR) & LEFT)){
      //printf("LEFT\n");
      if(check_push()) reg(PORT_D + BSRR) = PD4;
      else reg(PORT_D + BRR) = PD4;
    }
    else if(!(reg(PORT_C+IDR) & RIGHT)){
      //printf("RIGHT\n");
      if(check_push()) reg(PORT_D + BSRR) = PD2;
      else reg(PORT_D + BRR) = PD2;
    }
  }
  return 0;
}