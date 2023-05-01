#include "stm32f10x.h"



int main(void)
{ 
      GPIO_InitTypeDef GPIO_InitStructure;     
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
             GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // speed
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // mode
    GPIO_Init(GPIOD, &GPIO_InitStructure);
GPIO_SetBits(GPIOD, GPIO_Pin_7);
  while(1) {

  }
  return 0;
}