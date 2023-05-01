#include "misc.h"
#include "core_cm3.h"
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include <stm32f10x_tim.h>
#include <stm32f10x_adc.h>

#define INITIALANGLE 1700
double const spd = (double)340 / 10000 / 2;
uint32_t dist;  //distance measured
uint32_t motorPulse = INITIALANGLE;
uint32_t lastdist = 0;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
TIM_OCInitTypeDef TIM_OCInitStruct;

void RCC_Configure() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
    // TIM2 : Hypersomic distance measure cycle. TIM3 : Hypersonic PWM. TIM4 : Motor PWM.
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
}

void GPIO_Configure() {
    GPIO_InitTypeDef GPIO_InitStructure; 
    /* ÃÊÀ½ÆÄ */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//trigger PB0
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//echo PA6
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void NVIC_Configure()
{
  NVIC_InitTypeDef NVIC_InitStructure; // for interreupt

  /* Enable TIM2 Global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
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
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
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
    TIM_Cmd(TIM2, ENABLE);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // interrupt enable
}

void InitMotor()
{
  uint16_t prescaler;
  
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

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
  TIM_Cmd(TIM4, ENABLE);
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

void TIM2_IRQHandler(void)//hypersonci cycle manager
{
   if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
   {
      dist = HCSR04GetDistance();
      if (dist > 25) {
        motorPulse = INITIALANGLE;
        changeDoor();
      } else {
        if (0 == lastdist) lastdist = dist;
        if (lastdist != dist) {
          uint32_t diffrenece;
          if (lastdist > dist) {
            diffrenece = (lastdist - dist) * 50;
            motorPulse -= diffrenece;
            //foor limit to be added
          } else {
            diffrenece = (dist - lastdist) * 50;
            if ((motorPulse + diffrenece) <= INITIALANGLE) motorPulse += diffrenece;
          }
          changeDoor();
          lastdist = dist;
        }
      }
      printf("%d\n",dist);
   }
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void init()
{
    SystemInit();
    RCC_Configure();
    GPIO_Configure();
    NVIC_Configure();
    TIM_Configure();
    InitMotor();
}

int main() {
    
    init();
    while(1){
    }
    return 0;
}