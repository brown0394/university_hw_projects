
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stdio.h"
#include "misc.h"

#define ARRAY_LEN(X) (sizeof(X) / sizeof(X[0])) // 배열 길이
/* function prototype */
void RCC_Configure(void);
void GPIO_Configure(void);
void EXTI_Configure(void);
void USART1_Init(void);
void NVIC_Configure(void);

void EXTI15_10_IRQHandler(void);

void Delay(void);

void sendDataUART1(uint16_t data);
void UpLED();
void DownLED();
void ResetLED();

int upflag=0, downflag=0;
//---------------------------------------------------------------------------------------------------

void RCC_Configure(void) // stm32f10x_rcc.c, .h 참고, 아래에 주석이 묶여있는 기능끼리 합쳐서 함수에 매개변수 전달 하시오!!
{
/////////////////////// TODO: Enable the APB2 peripheral clock using the function 'RCC_APB2PeriphClockCmd'///////////////////////
	
	/* JoyStick Up/Down port clock enable, LED port clock enable */
	
	/* UART 1 TX/RX port clock enable, USART1 clock enable */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Alternate Function IO clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // UASRT CLOCK
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Joystick clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // LED clock 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // USART clock 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

void GPIO_Configure(void) // stm32f10x_gpio.c, .h 참고
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitTypeDef GPIO_InitButton;
    GPIO_InitTypeDef GPIO_InitJoystick;
    

/////////////////////// TODO: Initialize the GPIO pins using the structure 'GPIO_InitTypeDef' and the function 'GPIO_Init'///////
	
    /* LED pin setting, Output */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // speed
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // mode
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* JoyStick down pin setting, Input */
    GPIO_InitJoystick.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitJoystick.GPIO_Mode = GPIO_Mode_IPD ; // mode       GPIO_Mode_IPD #2
    GPIO_Init(GPIOC, &GPIO_InitJoystick);

    /* JoyStick up pin setting, Input */
    GPIO_InitJoystick.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitJoystick.GPIO_Mode = GPIO_Mode_IPD ; // mode       GPIO_Mode_IPD #2
    GPIO_Init(GPIOC, &GPIO_InitJoystick);
    
    /* USER S1 button pin setting, Input */
    GPIO_InitButton.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitButton.GPIO_Mode = GPIO_Mode_IPD ; // mode       GPIO_Mode_IPD #2
    GPIO_Init(GPIOD, &GPIO_InitButton);
    
	
    /* UART pin setting */ // 반드시 Reference Manual의 USART pinout상 Full duplex가 되는 GPIO configuration으로 설정!! 대충 설정해도 되는 경우가 있지만 Reference를 따른다에 의의를 둠
    //USART pinout상 Full duplex가 되는 GPIO configuration
    // TX -> Alternate function push-pull
    // RX -> Input Floating
    // TX, Output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // USART TX - Alternate function push-pull
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    // RX, Input
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // USART RX - mode Input Floating
    GPIO_Init(GPIOA, &GPIO_InitStructure);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void EXTI_Configure(void) // stm32f10x_gpio.c, .h 참고
{
    //EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitTypeDef EXTI_UP;
    EXTI_InitTypeDef EXTI_DOWN;
    EXTI_InitTypeDef EXTI_BUTTON;
////// TODO: Select the GPIO pin (Joystick, button) used as EXTI Line using function 'GPIO_EXTILineConfig'///////////////////////
	// TODO: Initialize the EXTI using the structure 'EXTI_InitTypeDef' and the function 'EXTI_Init'
	
    /* Joystick Down */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
    EXTI_DOWN.EXTI_Line = EXTI_Line2;
    EXTI_DOWN.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_DOWN.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_DOWN.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_DOWN);

    /* Joystick Up */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);
    EXTI_UP.EXTI_Line = EXTI_Line5;
    EXTI_UP.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_UP.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_UP.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_UP);

    /* USER S1 Button */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource11);
    EXTI_BUTTON.EXTI_Line = EXTI_Line11;
    EXTI_BUTTON.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_BUTTON.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_BUTTON.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_BUTTON);
	
	// NOTE: do not select the UART GPIO pin used as EXTI Line here, EXTI Line과 Pin Source는 일치해야한다.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void USART1_Init(void) // stm32f10x_usart.c, .h 참고
{
	USART_InitTypeDef USART1_InitStructure;

	// Enable the USART1 peripheral
	USART_Cmd(USART1, ENABLE);
	
////// TODO: Initialize the USART using the structure 'USART_InitTypeDef' and the function 'USART_Init'//////////////////////////
    /*  BaudRate : 115200
        WordLength or Data : 8 bits
        Parity : None
        StopBits : 1 bit
        Hardware Flow Control of Flow Control : None
    위의 설정대로 통신 설정
     */
    USART1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART1_InitStructure.USART_BaudRate = 115200;
    USART1_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART1_InitStructure.USART_Parity = USART_Parity_No;
    USART1_InitStructure.USART_StopBits = USART_StopBits_1;
    USART1_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART1_InitStructure);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
////// TODO: Enable the USART1 RX interrupts using the function 'USART_ITConfig' and the argument value 'Receive Data register not empty interrupt'
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); // USART RX interrupt 설정
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void NVIC_Configure(void) { // stm32f10x.h, misc.c, .h 참고

    NVIC_InitTypeDef NVIC_DOWN;
    NVIC_InitTypeDef NVIC_UP;
    NVIC_InitTypeDef NVIC_Button;
    NVIC_InitTypeDef NVIC_USART;
    
    // You Define Using NVIC_InitTypeDef Button, Up, Down Like GPIO_Configure
    /*  Priority Group : 0
        Preemtion Priority : Joystick down = up = User S1 = UART 1
        Sub Priority 순서 : Joystick down -> up -> User S1 -> UART 1
    위의 설정대로 IRQ 우선순위 설정
     */
////// TODO: fill the arg Priority Group 0///////////////////////////////////////////////////////////////////////////////////////
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////// TODO: Initialize the NVIC using the structure 'NVIC_InitTypeDef' and the function 'NVIC_Init'/////////////////////////////
	

    // Joystick Down Use NVIC_InitDown
    NVIC_EnableIRQ(EXTI2_IRQn);
    NVIC_DOWN.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_DOWN.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_DOWN.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_DOWN.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_DOWN);
    
    // Joystick Up Use NVIC_InitUp
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_UP.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_UP.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_UP.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_UP.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_UP);

    // User S1 Button  Use NVIC_InitStructure
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_Button.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Button.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_Button.NVIC_IRQChannelSubPriority = 0x02;
    NVIC_Button.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_Button);
    
    // UART1 Use NVIC_InitUSART
    NVIC_EnableIRQ(USART1_IRQn); // 'NVIC_EnableIRQ' is only required for USART setting
    NVIC_USART.NVIC_IRQChannel = USART1_IRQn;
    NVIC_USART.NVIC_IRQChannelPreemptionPriority = 0x00; // TODO
    NVIC_USART.NVIC_IRQChannelSubPriority = 0x03; // TODO
    NVIC_USART.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_USART);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


char preword = 'a';
void USART1_IRQHandler() {
	uint16_t word;
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){
    	// the most recent received data by the USART1 peripheral
        word = USART_ReceiveData(USART1);
        if(word == 'd'){
            ResetLED();
            downflag = 1;
            upflag = 0;
        }
        else if(word == 'u'){
            ResetLED();
            downflag = 0;
            upflag = 1;
        }
        else if(word == 'r'){
            ResetLED();
            downflag = 0;
            upflag = 0;
        }
        else if(preword == 't'&& word == 'g'){
            ResetLED();
            if(upflag){
              downflag=1;
              upflag=0;
            }
            else{
              downflag=0;
              upflag=1;
            }
        }
        preword = word;

////////// TODO implement, UART로 키보드 입력 'd' or 'u' 에 맞게 동작 (d= down, u= up 방향으로 LED 방향 변경)//////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // clear 'Read data register not empty' flag
    	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}


void EXTI15_10_IRQHandler(void) { // when the button is pressed
    char msg_Usart1[] = "Team05\r\n";
    int i=0;
	if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
          if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11) == Bit_RESET) {
////////////// TODO implement, USER S1 Button 동작 작성 UART 1 Send///////////////////////////////////////////////////////////////
            for (; i < ARRAY_LEN(msg_Usart1); i++)
            {
                sendDataUART1(msg_Usart1[i]);
                //printf("%c",msg_Usart1[i]);
            }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
        EXTI_ClearITPendingBit(EXTI_Line11);
	}
}

// "EXTI2_IRQHandler", "EXTI9_5_IRQHandler" 중 맞는 것으로 아래 두개 IRQ 동작 완성////////////////////////////////////////////////////
// TODO: Create Joystick up interrupt handler functions (up 방향으로 LED 방향 변경)
void EXTI9_5_IRQHandler(void) { // when the button is pressed 
//Up

	if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
        ResetLED();
////////////// TODO implement, USER S1 Button 동작 작성 UART 1 Send///////////////////////////////////////////////////////////////
		downflag = 0;
        upflag = 1;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EXTI_ClearITPendingBit(EXTI_Line5);
        EXTI_ClearFlag(EXTI_Line5);
	}
}
// TODO: Create Joystick down interrupt handler functions (down 방향으로 LED 방향 변경)
//Down
void EXTI2_IRQHandler(void) { // when the button is pressed

	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
        ResetLED();
  ////////////// TODO implement, USER S1 Button 동작 작성 UART 1 Send///////////////////////////////////////////////////////////////
        downflag = 1;
        upflag = 0;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EXTI_ClearITPendingBit(EXTI_Line2);
        EXTI_ClearFlag(EXTI_Line2);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Delay(void) {
	int i;

	for (i = 0; i < 2000000; i++) {}
}

void sendDataUART1(uint16_t data) {
	/* Wait till TC is set */
	while ((USART1->SR & USART_SR_TC) == 0);
	USART_SendData(USART1, data);
}
void ResetLED(){
    GPIO_ResetBits(GPIOD, GPIO_Pin_2);
    GPIO_ResetBits(GPIOD, GPIO_Pin_3);
    GPIO_ResetBits(GPIOD, GPIO_Pin_4);
    GPIO_ResetBits(GPIOD, GPIO_Pin_7);
}

void UpLED(){
    ResetLED();
    if(upflag == 0) return;
    GPIO_SetBits(GPIOD, GPIO_Pin_2);
    Delay();
    GPIO_ResetBits(GPIOD, GPIO_Pin_2);
    if(upflag == 0) return;
    GPIO_SetBits(GPIOD, GPIO_Pin_3);
    Delay();
    GPIO_ResetBits(GPIOD, GPIO_Pin_3);
    if(upflag == 0) return;
    GPIO_SetBits(GPIOD, GPIO_Pin_4);
    Delay();
    GPIO_ResetBits(GPIOD, GPIO_Pin_4);
    if(upflag == 0) return;
    GPIO_SetBits(GPIOD, GPIO_Pin_7);
    Delay();
    GPIO_ResetBits(GPIOD, GPIO_Pin_7);
}

void DownLED(){
    ResetLED();
    if(downflag == 0) return;
    GPIO_SetBits(GPIOD, GPIO_Pin_7);
    Delay();
    GPIO_ResetBits(GPIOD, GPIO_Pin_7);
    if(downflag == 0) return;
    GPIO_SetBits(GPIOD, GPIO_Pin_4);
    Delay();
    GPIO_ResetBits(GPIOD, GPIO_Pin_4);
    if(downflag == 0) return;
    GPIO_SetBits(GPIOD, GPIO_Pin_3);
    Delay();
    GPIO_ResetBits(GPIOD, GPIO_Pin_3);
    if(downflag == 0) return;
    GPIO_SetBits(GPIOD, GPIO_Pin_2);
    Delay();
    GPIO_ResetBits(GPIOD, GPIO_Pin_2);
}

void dofun(){
    if(upflag){
        UpLED();
    }
    else if(downflag){
        DownLED();
    }
}

      
////////// TODO: implement //////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    1. 4개 LED가 순차로 아래방향으로 흐르듯이 켜지고 꺼지는 동작
    2. Joystick up 과 UART1 키보드 입력 'u'에 맞춰서 up(윗) 방향으로 LED가 흐르듯이 켜지고 꺼지는 동작으로 전환
    3. Joystick down 과 UART1 키보드 입력 'd'에 맞춰서 down(아랫) 방향으로 LED가 흐르듯이 켜지고 꺼지는 동작으로 전환
    4. S1 버튼 입력에 맞춰서 UART1으로 "TEAM00" SEND (00은 각 조번호로)
 */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    upflag = 1;
    SystemInit();

    RCC_Configure();

    GPIO_Configure();

    EXTI_Configure();

    USART1_Init();

    NVIC_Configure();
    while (1) {
        dofun();
    	Delay();
    }
    return 0;
}
