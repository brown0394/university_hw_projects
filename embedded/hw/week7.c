#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stdio.h"
#include "misc.h"
#include "core_cm3.h"
#include "string.h"

#define SETSTEPS 16
#define ARRAY_LEN(X) (sizeof(X) / sizeof(X[0])) // 배열 길이


/* function prototype */
void RCC_Configure(void);
void GPIO_Configure(void);
void EXTI_Configure(void);
void USART1_Init(void);
void NVIC_Configure(void);
void FlushChar(char arr[], int limit);
void CheckCommand(char word);
void ResetLED(void);
void SetLED(void);
void Delay(void);
//---------------------------------------------------------------------------------------------------

void RCC_Configure(void) {
  /* Alternate Function IO clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // A Port clock Enable RX TX
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  // LED Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // USART clock 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // USART clock 
}

void GPIO_Configure(void) // Pin Mode 설정
{
    GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitTypeDef GPIO_InitButton;
       
    /* USER S1 button pin setting, Input */
    GPIO_InitButton.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitButton.GPIO_Mode = GPIO_Mode_IPD ; // mode       GPIO_Mode_IPD #2
    GPIO_Init(GPIOD, &GPIO_InitButton);        
            
    /* USER S2 button pin setting, Input */
    GPIO_InitButton.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitButton.GPIO_Mode = GPIO_Mode_IPD ; // mode       GPIO_Mode_IPD #2
    GPIO_Init(GPIOD, &GPIO_InitButton);
      
    /* LED pin setting, Output */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // speed
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // mode
    GPIO_Init(GPIOD, &GPIO_InitStructure);
      
    // TX -> Alternate function push-pull
    // RX -> Input Floating
    // TX, Output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // USART TX - Alternate function push-pull
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // speed
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    // RX, Input
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // USART RX - mode Input Floating
    GPIO_Init(GPIOA, &GPIO_InitStructure);

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


void EXTI_Configure(void) // stm32f10x_gpio.c, .h 참고
{
    //EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitTypeDef EXTI_BUTTON;

    /* USER S1 Button */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource11);
    EXTI_BUTTON.EXTI_Line = EXTI_Line11;
    EXTI_BUTTON.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_BUTTON.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_BUTTON.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_BUTTON);
      
    /* USER S2 Button */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource12);
    EXTI_BUTTON.EXTI_Line = EXTI_Line12;
    EXTI_BUTTON.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_BUTTON.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_BUTTON.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_BUTTON);
	
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
    USART_Init(USART1, &USART_InitStructure);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
    USART_Init(USART2, &USART_InitStructure);
	// Enable the USART1 peripheral
	USART_Cmd(USART1, ENABLE);
	USART_Cmd(USART2, ENABLE);

    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); // USART1 RX interrupt 설정
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE); // USART2 RX interrupt 설정
/////////////////////////////////////////////////////////1///////////////////////////////////////////////////////////////////////
}

void NVIC_Configure(void) { //USART 인터럽트 우선순위 결정.

    NVIC_InitTypeDef NVIC_USART;
    NVIC_InitTypeDef NVIC_Button;
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);


    // User S1, S2 Button  Use NVIC_InitStructure
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_Button.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Button.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_Button.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_Button.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_Button);

    // UART1 Use NVIC_InitUSART
    NVIC_EnableIRQ(USART1_IRQn); // 'NVIC_EnableIRQ' is only required for USART setting
    NVIC_USART.NVIC_IRQChannel = USART1_IRQn;
    NVIC_USART.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_USART.NVIC_IRQChannelSubPriority = 0x01; 
    NVIC_USART.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_USART);
    // UART2 Use NVIC_InitUSART
    NVIC_EnableIRQ(USART2_IRQn); // 'NVIC_EnableIRQ' is only required for USART setting
    NVIC_USART.NVIC_IRQChannel = USART2_IRQn;
    NVIC_USART.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_USART.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_USART.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_USART);

}

void ResetLED(){ // LED off
    GPIO_ResetBits(GPIOD, GPIO_Pin_2);
    GPIO_ResetBits(GPIOD, GPIO_Pin_3);
    GPIO_ResetBits(GPIOD, GPIO_Pin_4);
    GPIO_ResetBits(GPIOD, GPIO_Pin_7);
}

void SetLED(){ // LED ON
    GPIO_SetBits(GPIOD, GPIO_Pin_2);
    GPIO_SetBits(GPIOD, GPIO_Pin_3);
    GPIO_SetBits(GPIOD, GPIO_Pin_4);
    GPIO_SetBits(GPIOD, GPIO_Pin_7);
}

void FlushChar(char arr[], int limit) { //Flush input char buffer
  for (int i = 0; i < limit; ++i) {
      arr[i] = '\0';
  }
}

void CheckCommand(char word) { // Check the input string wether it's LED ON or LED OFF
  static char command[8]; //Command buffer
  static int comidx = 0; // Command index counter
  switch (word) {
    case ' ': {
      if (comidx>0 && command[comidx-1] == 'D') {command[comidx++]=word; break;} // when space is following after 'D' store in buffer
      FlushChar(command, comidx); //else flush the buffer
      comidx=0; 
      break;
    }
    case '\r': {break;}// terminal's new line : \r\n
    case '\n': {comidx = 0; break;}
    default: {
      command[comidx++]=word;
      if (strcmp(command, "LED ON") == 0) {
         SetLED();
         FlushChar(command, comidx);
         comidx = 0;
      }
      else if (strcmp(command, "LED OFF") == 0) {
         FlushChar(command, comidx);
         comidx = 0;
         ResetLED();
      }
      else if (comidx == 8) {//if string is bigger than buffer, flush it
        FlushChar(command, comidx);
        comidx = 0;
      }
      break;
    }
  }
}

void USART1_IRQHandler() {// putty창에 입력했을 경우 .
    uint16_t word;

    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){
        word = USART_ReceiveData(USART1);
        //USART_SendData(USART1, word); //can be used instead of force echo on Putty setting
        USART_SendData(USART2, word);
    	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}

void USART2_IRQHandler() { // bluetooth terminal input
    uint16_t word;
    
    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET){
        word = USART_ReceiveData(USART2);
        CheckCommand(word);
        USART_SendData(USART1, word);
    	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    }
}

void Delay(void) {
	int i;
	for (i = 0; i < 5000000; i++) {}
}

const char msg_AutoSetting[SETSTEPS][10] = {"0\r", "MON_05\r"/*name*/, "1\r", "2\r",
"5555\r"/*password*/, "t\r", "3\r", "4\r"/*con mode*/, "5\r", "1\r", "4\r", "2\r", 
"1\r", "3\r", "1\r", "t\r"/*UART CONFIG*/};

const char msg_Bluetooth[] = "AT+BTSCAN\r";

void EXTI15_10_IRQHandler(void) { // when the button is pressed
    int go = 0;
    static int pressed = 0;
	if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
          if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11) == Bit_RESET) {
            for (int i = 0; i < SETSTEPS; i++)
            {
              for(int j = 0; j < ARRAY_LEN(msg_AutoSetting[i]); j++) {
                if(go) {go = 0; break;}
                if(msg_AutoSetting[i][j] == '\r') go = 1;
                while ((USART2->SR & USART_SR_TC) == 0);
                USART_SendData(USART1, msg_AutoSetting[i][j]);
                USART_SendData(USART2, msg_AutoSetting[i][j]);      
              }
                if(i < SETSTEPS-1){Delay();}
            }
          }
        EXTI_ClearITPendingBit(EXTI_Line11);
	}

        if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
          if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12) == Bit_RESET) {
            if(pressed == 0){
               for (int i=0; i < ARRAY_LEN(msg_Bluetooth); i++){
                while ((USART2->SR & USART_SR_TC) == 0);
                USART_SendData(USART1, msg_Bluetooth[i]);
                USART_SendData(USART2, msg_Bluetooth[i]);
              }           
              pressed+=35000;
            }
            else{--pressed;}
          }     
        EXTI_ClearITPendingBit(EXTI_Line11);
        }
}

int main(void)
{
    SystemInit();

    RCC_Configure();

    GPIO_Configure();
      EXTI_Configure();

    USART1_2_Init();
      
    ResetLED();

    NVIC_Configure();
                     for (int i=0; i < ARRAY_LEN(msg_Bluetooth); i++){
                while ((USART2->SR & USART_SR_TC) == 0);
                USART_SendData(USART2, msg_Bluetooth[i]);
              }    
    while (1) {
    }
    return 0;
}
