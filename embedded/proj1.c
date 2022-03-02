#include <stdio.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include <stm32f10x_tim.h>
#include "lcd.h"
#include "touch.h"


#define WIDTH 10
#define HEIGHT 304

#define MAX_LCD_POSX 240
#define MAX_LCD_POSY 304

#define ARRAY_LEN(X) (sizeof(X) / sizeof(X[0])) //       
#define INITIALANGLE 1700
#define BUFFERSIZE 6

void RCC_Configure();
void GPIO_Configure();
void NVIC_Configure();
void USART1_2_Init();
void TIM_Configure();
void InitMotor();
void changeDoor();
int32_t HCSR04GetDistance();
void FlushChar(char arr[], int limit);
void CheckCommand(char word);
void init();
void TIM_start();
void TIM_stop();
void Main_Screen();
void GAME_PAUSE();
void Light_value_check();



// right key 눌려져있는지 확인
int isRight = 0;
// left key 눌려져있는지 확인
int isLeft = 0;
// clock 설정
double const spd = (double)340 / 10000 / 2;
uint32_t dist = 10000000000;  //distance measured
uint32_t motorPulse = INITIALANGLE;
uint32_t lastdist = 0;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
TIM_OCInitTypeDef TIM_OCInitStruct;

int start = 0,end = 0,TIM_FLAG = 0,Pause_Flag = 0;
uint16_t touch_x = 0, touch_y = 0;
int MyScreen = 0; // 0 = Main_Screen, 1 = Gaming_Screen -1 = Game_Over_Screen

// GAME OVER시 Cancle 눌리면 나타나는 초기화면

uint16_t value_pressure,value_light;
uint16_t pending = 0;
uint16_t doorflag = 0;

void RCC_Configure(void)
{
   /* JoyStick Up/Down port clock enable, LED port clock enable */
   
   /* UART 1 TX/RX port clock enable, USART1 clock enable */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /* Alternate Function IO clock enable */
   //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // UASRT CLOCK
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE); // Joystick clock
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
      // TIM2 : Hypersomic distance measure cycle. TIM3 : Hypersonic PWM. TIM4 : Motor PWM.
      
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // USART clock 
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // pressure adc
      
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); // light 센서
}

// 핀 설정 


void GPIO_Configure(void) // stm32f10x_gpio.c, .h 참고
{
    GPIO_InitTypeDef GPIO_InitJoystick;
    // PB0, PB8, PA6, PC2 , PC3, PC4, PA2, PA3

    GPIO_InitTypeDef GPIO_InitStructure; 
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//PD11 for dc motor
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOD, GPIO_Pin_11);
    
    /*motor*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
   
    /* hypersonic */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//trigger PB0
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//echo PA6
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
     ///////pressure adc
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
     ///////light adc
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    


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

    //game setting
    /* JoyStick LEFT pin setting, Input */
    GPIO_InitJoystick.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitJoystick.GPIO_Mode = GPIO_Mode_IPD ; // mode       GPIO_Mode_IPD #2
    GPIO_Init(GPIOC, &GPIO_InitJoystick);

    /* JoyStick RIGHT pin setting, Input */
    GPIO_InitJoystick.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitJoystick.GPIO_Mode = GPIO_Mode_IPD ; // mode       GPIO_Mode_IPD #2
    GPIO_Init(GPIOC, &GPIO_InitJoystick);

}

void ADC_Configure(void){
   
   ADC_InitTypeDef ADC_12,ADC_11;
   ADC_DeInit(ADC1); //ADC1 initiation
   ADC_12.ADC_Mode = ADC_Mode_Independent;
   ADC_12.ADC_ScanConvMode = DISABLE;
   ADC_12.ADC_ContinuousConvMode = ENABLE;
   ADC_12.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
   ADC_12.ADC_DataAlign = ADC_DataAlign_Left;
   ADC_12.ADC_NbrOfChannel = 1;
   ADC_Init(ADC1, &ADC_12);
   ADC_RegularChannelConfig(ADC1, ADC_Channel_12,1, ADC_SampleTime_239Cycles5);
   ADC_ITConfig(ADC1,ADC_IT_EOC,DISABLE);
   ADC_Cmd(ADC1, ENABLE);


   ADC_DeInit(ADC2); //ADC2 initiation
   ADC_11.ADC_Mode = ADC_Mode_Independent;
   ADC_11.ADC_ScanConvMode = DISABLE;
   ADC_11.ADC_ContinuousConvMode = ENABLE;
   ADC_11.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
   ADC_11.ADC_DataAlign = ADC_DataAlign_Left;
   ADC_11.ADC_NbrOfChannel = 2;
   ADC_Init(ADC2, &ADC_11);
   ADC_RegularChannelConfig(ADC2, ADC_Channel_11,1, ADC_SampleTime_239Cycles5);
   ADC_ITConfig(ADC2,ADC_IT_EOC,DISABLE);
   ADC_Cmd(ADC2, ENABLE);
      
   ADC_ResetCalibration(ADC1);
   while (ADC_GetResetCalibrationStatus(ADC1));
   ADC_StartCalibration(ADC1);
   while (ADC_GetCalibrationStatus(ADC1));
   ADC_SoftwareStartConvCmd(ADC1,ENABLE);

   
   ADC_ResetCalibration(ADC2);
   while (ADC_GetResetCalibrationStatus(ADC2));
   ADC_StartCalibration(ADC2);
   while (ADC_GetCalibrationStatus(ADC2));
   ADC_SoftwareStartConvCmd(ADC2,ENABLE);
}

// EXIT 설정

void EXTI_Configure(void) // stm32f10x_gpio.c, .h 참고
{
    //EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitTypeDef EXTI_RIGHT;
    EXTI_InitTypeDef EXTI_LEFT;

    /* Joystick LEFT */
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);
    EXTI_LEFT.EXTI_Line = EXTI_Line3;
    EXTI_LEFT.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_LEFT.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_LEFT.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_LEFT);

    /* Joystick RIGHT */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);
    EXTI_RIGHT.EXTI_Line = EXTI_Line4;
    EXTI_RIGHT.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_RIGHT.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_RIGHT.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_RIGHT);
}

// 인터럽트 우선순위
void NVIC_Configure(void) { // stm32f10x.h, misc.c, .h 참고

      NVIC_InitTypeDef NVIC_InitStructure; // for interreupt

      /* Enable TIM2 Global Interrupt */
      NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);
      

      // UART2 Use NVIC_InitUSART
      NVIC_EnableIRQ(USART2_IRQn); // 'NVIC_EnableIRQ' is only required for USART setting
      NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);
         
      /* pressure adc */
      NVIC_EnableIRQ(ADC1_2_IRQn);
      NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; 
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00; 
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_InitStructure);


      // game setting
      NVIC_InitTypeDef NVIC_LEFT;
      NVIC_InitTypeDef NVIC_RIGHT;

      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

      // Joystick LEFT Use NVIC_InitLEFT
      NVIC_EnableIRQ(EXTI3_IRQn);
      NVIC_LEFT.NVIC_IRQChannel = EXTI3_IRQn;
      NVIC_LEFT.NVIC_IRQChannelPreemptionPriority = 0x00;
      NVIC_LEFT.NVIC_IRQChannelSubPriority = 0x01;
      NVIC_LEFT.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_LEFT);
      
      // Joystick RIGHT Use NVIC_InitRIGHT
      NVIC_EnableIRQ(EXTI4_IRQn);
      NVIC_RIGHT.NVIC_IRQChannel = EXTI4_IRQn;
      NVIC_RIGHT.NVIC_IRQChannelPreemptionPriority = 0x00;
      NVIC_RIGHT.NVIC_IRQChannelSubPriority = 0x02;
      NVIC_RIGHT.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&NVIC_RIGHT);

      // fill the arg you want
      //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

      //NVIC_EnableIRQ(ADC1_2_IRQn);
      //NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
      //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 
      //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00; 
      //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      //NVIC_Init(&NVIC_InitStructure);
}

void USART1_2_Init(void) // USART_BaudRate 9600           ?            Putty             ? .
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

    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE); // USART2 RX interrupt     
/////////////////////////////////////////////////////////1///////////////////////////////////////////////////////////////////////
}

void TIM_Configure() {
    RCC_ClocksTypeDef RCC_ClocksStatus; 
    uint16_t prescaler;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_ICInitTypeDef TIM_ICInitStruct;
    
    /* relay */
    RCC_GetClocksFreq(&RCC_ClocksStatus);
    prescaler = RCC_ClocksStatus.SYSCLK_Frequency / 1000000 - 1; //1 tick = 1us (1 tick = 0.165mm resolution)
    TIM_DeInit(TIM3);
    TIM_TimeBaseInitStruct.TIM_Prescaler = prescaler;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
    
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 15; //us
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(TIM3, &TIM_OCInitStruct);
    
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICFilter = 0;
    TIM_PWMIConfig(TIM3, &TIM_ICInitStruct);
    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
    TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
    TIM_CtrlPWMOutputs(TIM3, DISABLE);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    /////////////////////////////////////////////////////
    prescaler = (uint16_t)(SystemCoreClock / 100000) - 1;
  
    TIM_TimeBaseStruct.TIM_Period = 50000 - 1;// 1/2 second period
    TIM_TimeBaseStruct.TIM_Prescaler = prescaler;
    TIM_TimeBaseStruct.TIM_ClockDivision = 0;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Down;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, DISABLE);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // interrupt enable
}

void InitMotor()
{
  uint16_t prescaler;

  prescaler = (uint16_t)(SystemCoreClock / 1000000) - 1;

  TIM_TimeBaseStruct.TIM_Period = 20000 - 1;
  TIM_TimeBaseStruct.TIM_Prescaler = prescaler;
  TIM_TimeBaseStruct.TIM_ClockDivision = 0;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_Pulse = motorPulse;
  TIM_OC3Init(TIM4, &TIM_OCInitStruct);

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStruct);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_Cmd(TIM4, DISABLE);
}

void changeDoor()
{
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_Pulse = motorPulse;

  TIM_OC3Init(TIM4, &TIM_OCInitStruct);
}

int32_t HCSR04GetDistance() { 
    (TIM3)->CNT = 0;
    TIM_Cmd(TIM3, ENABLE);
    while(!TIM_GetFlagStatus(TIM3, TIM_FLAG_Update)); TIM_Cmd(TIM3, DISABLE);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    return (TIM_GetCapture2(TIM3)-TIM_GetCapture1(TIM3))* spd; //*165/1000;
}

const char distmsg[] = "Current distance : ";

void TIM2_IRQHandler(void)//hypersonci cycle manager 1/2 second
{
   
   ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
   ADC_ITConfig(ADC2,ADC_IT_EOC,ENABLE);
   static int count = 0;
   static char number[5];
   if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
   {
      ++count;
      dist = HCSR04GetDistance();
      if (count == 60) {//30s
        count = 0;
        int length = 0;
        uint32_t cur = dist;
        while(cur > 0) {
          ++length;
          cur = cur / 10;
        }
        sprintf(number, "%d", dist);
        for(int i = 0; i < ARRAY_LEN(distmsg); ++i){
           while ((USART2->SR & USART_SR_TC) == 0);
           USART_SendData(USART2, distmsg[i]);
        }
        for(int i = 0; i < length; ++i) {
          while ((USART2->SR & USART_SR_TC) == 0);
          USART_SendData(USART2, number[i]);
        }
        while ((USART2->SR & USART_SR_TC) == 0);
        USART_SendData(USART2, '\r');
        USART_SendData(USART2, '\n');
      }
      if (dist > 30) {////////////////////////////////////모터 움직임 초음파 거리 기준값
        motorPulse = INITIALANGLE;
        changeDoor();
      } else {
        if (0 == lastdist) lastdist = dist;
        if (lastdist != dist) {
          uint32_t diffrenece;
          if (lastdist > dist) {
            diffrenece = (lastdist - dist) * 50;
            if (doorflag) pending -= diffrenece;
            else motorPulse -= diffrenece;
          } else {
            diffrenece = (dist - lastdist) * 50;
            if (doorflag) {
              if (pending + diffrenece > 0) {
                motorPulse += diffrenece - pending;
                if ((motorPulse + diffrenece) <= INITIALANGLE) motorPulse += diffrenece;
                doorflag = 0;
                pending = 0;
              } else pending += diffrenece;
            } else { if ((motorPulse + diffrenece) <= INITIALANGLE) motorPulse += diffrenece; }
          }
          changeDoor();
          lastdist = dist;
        }
      }
      if(dist < 10 ){
        end = 1;
        TIM_stop();
      }
      else if(dist < 20){
         Pause_Flag = 1;
      }
      //printf("%d\n",dist);///////////////////초음파 거리 디버깅용
   }
  Light_value_check();
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void FlushChar(char arr[], int limit) { //Flush input char buffer
  for (int i = 0; i < limit; ++i) {
      arr[i] = '\0';
  }
}

void CheckCommand(char word) { // Check the input string wether it's LED ON or LED OFF
  static char command[BUFFERSIZE]; //Command buffer
  static int comidx = 0; // Command index counter
  switch (word) {
    case ' ': {
      FlushChar(command, comidx); //else flush the buffer
      comidx=0; 
      break;
    }
    case '\r': {break;}// terminal's new line : \r\n
    case '\n': {comidx = 0; break;}
    default: {
      command[comidx++]=word;
      if (strcmp(command, "start") == 0) {
        TIM_start();
        FlushChar(command, comidx);
        comidx = 0;
      }
      else if (strcmp(command, "stop") == 0) {
        TIM_stop();
        end = 1;
        FlushChar(command, comidx);
        comidx = 0;
      }
      else if (comidx == BUFFERSIZE) {//if string is bigger than buffer, flush it
        FlushChar(command, comidx);
        comidx = 0;
      }
      break;
    }
  }
}

void ADC1_2_IRQHandler()
{
  
  if(ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET){
   value_pressure = ADC_GetConversionValue(ADC1);
   if(value_pressure > 900 ){/////////////////////////////////// 압력센서 기준값 안눌렀을 때 기본 약 450-500
     doorflag = 1;
   }
   ADC_ITConfig(ADC1,ADC_IT_EOC,DISABLE);
  }
  ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
  
   if(ADC_GetITStatus(ADC2, ADC_IT_EOC) != RESET){
      value_light = ADC_GetConversionValue(ADC2) - 30000;
      ADC_ITConfig(ADC2,ADC_IT_EOC,DISABLE);
   }
   ADC_ClearITPendingBit(ADC2, ADC_IT_EOC);
}

int limit_light = 30000;////////////////////조도 센서 기준값
void Light_value_check(){
   //printf("%d, %d\n",value_light,value_pressure); //조도센서 압력센서 값 확인용 디버깅용
   if((value_light < limit_light)){
      GPIO_SetBits(GPIOD, GPIO_Pin_11);
   }
   else{
      GPIO_ResetBits(GPIOD, GPIO_Pin_11);
   }

}

void USART2_IRQHandler() { // bluetooth terminal input
    uint16_t word;
    
    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET){
        word = USART_ReceiveData(USART2);
        CheckCommand(word);
       USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    }
}

const char msg_Bluetooth[] = "AT+BTSCAN\r";

void TIM_start() {
   TIM_FLAG = 1;
   TIM_CtrlPWMOutputs(TIM3, ENABLE);
   TIM_Cmd(TIM2, ENABLE);
   TIM_Cmd(TIM4, ENABLE);
}

void TIM_stop() {
   TIM_FLAG = 0;
   TIM_CtrlPWMOutputs(TIM3, DISABLE);
   TIM_Cmd(TIM2, DISABLE);
   TIM_Cmd(TIM4, DISABLE);
}

void init()
{
    SystemInit();
    RCC_Configure();
    GPIO_Configure();
    NVIC_Configure();
    TIM_Configure();
    ADC_Configure();
    USART1_2_Init();
    EXTI_Configure();
    InitMotor();
    for (int i=0; i < ARRAY_LEN(msg_Bluetooth); i++){//ATBTSCAN
        while ((USART2->SR & USART_SR_TC) == 0);
        USART_SendData(USART2, msg_Bluetooth[i]);
    }   
    //LCd + game setting
    LCD_Init();//ok
    Touch_Configuration();//ok
    Touch_Adjust();//ok
    LCD_Clear(WHITE);//ok
    Main_Screen();//ok*/
}


// game setting
// Left Handler
void EXTI3_IRQHandler(void) { // when the button is pressed

   if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        isLeft = 1;
        EXTI_ClearITPendingBit(EXTI_Line3);
        EXTI_ClearFlag(EXTI_Line3);
   }
}

// Right Handler
void EXTI4_IRQHandler(void) { // when the button is pressed

   if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
        isRight = 1;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EXTI_ClearITPendingBit(EXTI_Line4);
        EXTI_ClearFlag(EXTI_Line4);
   }
}



// game source code
typedef struct
{
   int x;
   int y;
   int act;
}DDong;

typedef struct
{
   int x;
}Player;

DDong Dong[WIDTH];
Player player;

void init_Game(void)
{
   int i;

   for (i = 0; i < WIDTH; i++)
      Dong[i].act = 0;

   player.x = MAX_LCD_POSX / 2;
}

void CreateDong(void)
{
   int i;

   for (i = 0; i < WIDTH; i++)
   {
      if (!Dong[i].act)
      {
         Dong[i].x = rand() % MAX_LCD_POSX;
         Dong[i].y = HEIGHT - 1;

         Dong[i].act = 1;

         return;
      }
   }
}

void MoveDong(void)
{
   int i;

   for (i = 0; i < WIDTH; i++)
   {
      if (Dong[i].act)
      {
            if(i&2){
             Dong[i].y -= 10;
            }
            else{
             Dong[i].y -= 15;
            }
      }
   }
}

void DeleteDong(void)
{
   int i;

   for (i = 0; i < WIDTH; i++)
   {
      if (Dong[i].act && Dong[i].y < 30)
      {
         Dong[i].act = 0;
      }
   }
}

int Is_PlayerAlive(void)
{
   int i;

   for (i = 0; i < WIDTH; i++)
   {   
      
      if ((Dong[i].act) && (Dong[i].y < 40) && (abs(Dong[i].x - player.x) <= 20))
      {
         //printf("i : %d, X = %d, Y = %d, player_x = %d, player_y = %d\n",i,Dong[i].x,Dong[i].y,player.x,player.y);
         return 1;
      }
   }

   return 0;
}



void MovePlayer(void)
{
   if (isLeft)
      player.x -= 20;
      isLeft = 0;
   if (isRight)
      player.x += 20;
      isRight = 0;

   if (player.x < 10)
      player.x = 10;
   if (player.x > MAX_LCD_POSX - 10)
      player.x = MAX_LCD_POSX - 10;
}

void PrintMap(void)
{
    
   int i;
   for (i = 0; i < WIDTH; i++)
   {
      if (Dong[i].act)
      {
         //gotoxy(Dong[i].x, HEIGHT - Dong[i].y);
         //printf("D");
                LCD_DrawCircle(Dong[i].x,HEIGHT - Dong[i].y,10);
      }
   }


    // person
    LCD_DrawRectangle(player.x-10,MAX_LCD_POSY-20,player.x+10,MAX_LCD_POSY);
    // 밑에 선
    LCD_DrawLine(0,MAX_LCD_POSY,MAX_LCD_POSX,MAX_LCD_POSY);
}


void Delay(void) {
   int i;

   for (i = 0; i < 2000; i++) {}
}
void Main_Screen(void){
   MyScreen = 0;
   LCD_Clear(WHITE);
   LCD_ShowString(MAX_LCD_POSX/3,MAX_LCD_POSY/2, "GAME Start", BLACK, WHITE);
   LCD_DrawRectangle(MAX_LCD_POSX/3-10 ,MAX_LCD_POSY/2 - 15,MAX_LCD_POSX/3 + 90,MAX_LCD_POSY/2 + 30);
}
void Game_Over(void){ // GameOver 화면
   MyScreen = -1;
   // Big Box
   LCD_ShowString(MAX_LCD_POSX/3 + 10,MAX_LCD_POSY/2, "GAME OVER", BLACK, WHITE);
   LCD_DrawRectangle(MAX_LCD_POSX/3-20 ,MAX_LCD_POSY/2 - 15,MAX_LCD_POSX/3 + 110,MAX_LCD_POSY/2 + 60);
   // Start Box
   LCD_ShowString(MAX_LCD_POSX/3-10,MAX_LCD_POSY/2+30, "Restart", BLACK, WHITE);
   LCD_DrawRectangle(MAX_LCD_POSX/3-15 ,MAX_LCD_POSY/2+20,MAX_LCD_POSX/3+55,MAX_LCD_POSY/2 + 55);
   // Home Box
   LCD_ShowString(MAX_LCD_POSX/3+65 ,MAX_LCD_POSY/2+30, "Home", BLACK, WHITE);
   LCD_DrawRectangle(MAX_LCD_POSX/3+60 ,MAX_LCD_POSY/2+20,MAX_LCD_POSX/3+105,MAX_LCD_POSY/2 + 55);
}

void GAME_PAUSE(void){
   LCD_ShowString(MAX_LCD_POSX/4,MAX_LCD_POSY/2, "Too close Wall", BLACK, WHITE);
   Touch_GetXY(&touch_x, &touch_y, 1);
   Pause_Flag = 0;
}

void Game_start(void){
   if(TIM_FLAG == 0){
      TIM_start();
   }
   MyScreen = 1;
   start = 0;
   init_Game();
   do{
        if(Pause_Flag == 1) GAME_PAUSE();
        srand((int)malloc(NULL)); 
        if(Is_PlayerAlive() || end == 1){
            Game_Over();
            end = 0;
            break;
        }
        CreateDong();
        MoveDong();
        DeleteDong();
        MovePlayer();

        LCD_Clear(WHITE);
        PrintMap();
        
        Delay();
   } while (1);
}
void check_touch(){ // 게임 상태 변경하는 함수  - 주로 게임 재시작할때 사용
   if(MyScreen == 1){ // 게임중
      return ;
   }
   else if(MyScreen == 0){ // 메인화면
      if (touch_x >= MAX_LCD_POSX/3-10 && touch_y >= MAX_LCD_POSY/2 - 30 && touch_x <= MAX_LCD_POSX/3 + 90 &&  touch_y <= MAX_LCD_POSY/2 + 30){
         start = 1;
         return;
      }
   }
   else{ // 게임 Over시 나타나는 창 
      if (touch_x >= MAX_LCD_POSX/3-15 && touch_y >= MAX_LCD_POSY/2+20 && touch_x <= MAX_LCD_POSX/3+55 &&  touch_y <= MAX_LCD_POSY/2 + 55){
         start = 1;
         return;
      }
      else if (touch_x >= MAX_LCD_POSX/3+60 && touch_y >= MAX_LCD_POSY/2+20 && touch_x <= MAX_LCD_POSX/3+105 &&  touch_y <= MAX_LCD_POSY/2 + 55){
         Main_Screen();
         return;
      }
   }
   return;
}

int main() {
   init();
   while(1){
      Touch_GetXY(&touch_x, &touch_y, 1);
      Convert_Pos(touch_x,touch_y,&touch_x,&touch_y);
      check_touch();
      if(start){
         Game_start();
      }
   }
}