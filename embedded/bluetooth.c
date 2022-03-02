#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stdio.h"
#include "misc.h"
#include "core_cm3.h"
#include "string.h"

#define ARRAY_LEN(X) (sizeof(X) / sizeof(X[0])) // 배열 길이


/* function prototype */
void RCC_Configure(void);
void GPIO_Configure(void);
void USART1_Init(void);
void NVIC_Configure(void);
//---------------------------------------------------------------------------------------------------

void RCC_Configure(void) {
  /* Alternate Function IO clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // A Port clock Enable RX TX
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // USART clock 
}

void GPIO_Configure(void) // Pin Mode 설정
{
    GPIO_InitTypeDef GPIO_InitStructure;
     
    // TX -> Alternate function push-pull
    // RX -> Input Floating
    // TX, Output

    //USART2
    // TX, Output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // USART TX - Alternate function push-pull
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // speed
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    // RX, Input
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // USART RX - mode Input Floating
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void USART1_2_Init(void) // USART_BaudRate 9600 설정 및 기타 설정도 모두 Putty 설정과 동일하게.
{
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
    USART_Init(USART2, &USART_InitStructure);
	// Enable the USART1 peripheral
	USART_Cmd(USART2, ENABLE);

    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE); // USART2 RX interrupt 설정
/////////////////////////////////////////////////////////1///////////////////////////////////////////////////////////////////////
}

void NVIC_Configure(void) { //USART 인터럽트 우선순위 결정.

    NVIC_InitTypeDef NVIC_USART;
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    // UART2 Use NVIC_InitUSART
    NVIC_EnableIRQ(USART2_IRQn); // 'NVIC_EnableIRQ' is only required for USART setting
    NVIC_USART.NVIC_IRQChannel = USART2_IRQn;
    NVIC_USART.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_USART.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_USART.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_USART);

}


void USART2_IRQHandler() { // bluetooth terminal input
    uint16_t word;
    
    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET){
        word = USART_ReceiveData(USART2);
    	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    }
}

const char msg_Bluetooth[] = "AT+BTSCAN\r";


int main(void)
{
    SystemInit();

    RCC_Configure();

    GPIO_Configure();


    USART1_2_Init();
      

    NVIC_Configure();
    for (int i=0; i < ARRAY_LEN(msg_Bluetooth); i++){
        while ((USART2->SR & USART_SR_TC) == 0);
        USART_SendData(USART2, msg_Bluetooth[i]);
    }    
    while (1) {
    }
    return 0;
}
