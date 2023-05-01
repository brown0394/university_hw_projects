#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "core_cm3.h"
//flash load C:\team04\team4\flashclear.axf
//flash load C:\team04\team4\Debug\team4.axf

void Delay(int d){
  int i=0;
  for(i=0; i<1000000; i++){
    ;
  }
}
void sendDataUART1(uint16_t data) {
   USART_SendData(USART1, data);
   /* Wait till TC is set */
}

void sendDataUART2(uint16_t data) {
   USART_SendData(USART2, data);
   /* Wait till TC is set */
}

void RCC_Configure() {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //uart
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //usart rx tx
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //usart with pc
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //usart2 with phone
}


void USART_Configure() {

   //rx,tx 설정하는것
   GPIO_InitTypeDef Rx_pc, Tx_pc;
   GPIO_InitTypeDef Rx_phone, Tx_phone;
   USART_InitTypeDef usart1;
   USART_InitTypeDef usart2;
   Tx_pc.GPIO_Mode = GPIO_Mode_AF_PP;
   Tx_pc.GPIO_Pin = GPIO_Pin_9;
   Tx_pc.GPIO_Speed = GPIO_Speed_50MHz;
   Rx_pc.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   Rx_pc.GPIO_Pin = GPIO_Pin_10;
   Rx_pc.GPIO_Speed = GPIO_Speed_50MHz;


   Tx_phone.GPIO_Mode = GPIO_Mode_AF_PP;
   Tx_phone.GPIO_Pin = GPIO_Pin_2;
   Tx_phone.GPIO_Speed = GPIO_Speed_50MHz;
   Rx_phone.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   Rx_phone.GPIO_Pin = GPIO_Pin_3;
   Rx_phone.GPIO_Speed = GPIO_Speed_50MHz;

   GPIO_Init(GPIOA, &Tx_pc);
   GPIO_Init(GPIOA, &Rx_pc);
   GPIO_Init(GPIOA, &Tx_phone);
   GPIO_Init(GPIOA, &Rx_phone);

   usart1.USART_BaudRate = 9600;
   usart1.USART_WordLength = USART_WordLength_8b;
   usart1.USART_StopBits = USART_StopBits_1;
   usart1.USART_Parity = USART_Parity_No;
   usart1.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx);
   usart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
   USART_Init(USART1, &usart1);
   USART_Cmd(USART1, ENABLE);
   USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

   usart2.USART_BaudRate = 9600;
   usart2.USART_WordLength = USART_WordLength_8b;
   usart2.USART_StopBits = USART_StopBits_1;
   usart2.USART_Parity = USART_Parity_No;
   usart2.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx);
   usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
   USART_Init(USART2, &usart2);
   USART_Cmd(USART2, ENABLE);
   USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void NVIC_Configure() {
   NVIC_InitTypeDef nvic;
   nvic.NVIC_IRQChannelPreemptionPriority = 1;
   nvic.NVIC_IRQChannelSubPriority = 1;
   nvic.NVIC_IRQChannelCmd = ENABLE;
   nvic.NVIC_IRQChannel = USART1_IRQn;
   NVIC_Init(&nvic);

   nvic.NVIC_IRQChannel = USART2_IRQn;
   NVIC_Init(&nvic);
}

void USART1_IRQHandler() {
   unsigned char d;
   while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
   d = (unsigned char) USART_ReceiveData(USART1);
   sendDataUART2(d);
   USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

void USART2_IRQHandler() {
   unsigned char d;
   while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
   d = (unsigned char) USART_ReceiveData(USART2);
   sendDataUART1(d);
   USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}

int main() {
   SystemInit();
   RCC_Configure();
   USART_Configure();
   NVIC_Configure();
   while(1){}
}