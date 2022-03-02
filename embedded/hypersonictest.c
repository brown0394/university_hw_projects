#include <misc.h>
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>
//#include "lcd.h"
//#include "touch.h"

/* RCC */
#define RCC_APB2ENR ((volatile unsigned *)0x40021018)
#define RCC_APB2ENR_IOPBEN 0x08
#define RCC_APB2ENR_IOPCEN 0x10
#define RCC_APB2ENR_IOPDEN 0x20
// RCC B,C,D en => 0x38

/* GPIO port config */
#define GPIO_D_CRL ((volatile unsigned *)0x40011400)

/* GPIO BSRR */
#define GPIO_D_BSRR ((volatile unsigned *)0x40011410)

void resetDoor(void);
void openDoor(void);
void closeDoor(void);
void delay(void);

void APB2ClockEnable()
{
  // RCC
  //*(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // trigger timer
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // hypersonic activation cycle timer
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // interrupt
}

void GpioConfig()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitTypeDef GPIO_InitButton;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //trigger pin
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // speed
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // mode
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  //echo pin
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // mode
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void EXTI_Configure(void) // stm32f10x_gpio.c, .h Âü°í
{
    //EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitTypeDef EXTI_ECHO;

    /* echo interrupt */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9);
    EXTI_ECHO.EXTI_Line = EXTI_Line9;
    EXTI_ECHO.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_ECHO.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_ECHO.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_BUTTON);

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
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void init()
{
  NVIC_Configure();
  APB2ClockEnable();
  GpioConfig();
}



uint32_t count = 0;

void TIM2_IRQHandler(void)//hypersoncie trigger
{
   if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
   {
      TIM_Cmd(TIM2, DISABLE); //do not start countdown rightaway
      TIM_Cmd(TIM4, ENABLE);  //start timer for next trigger 
      GPIO_ResetBits(GPIOE, GPIO_Pin_8); //stop shooting
   }
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void TIM4_IRQHandler(void)//hypersonic trigger
{
   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
   {
      TIM_Cmd(TIM4, DISABLE);
      TIM_Cmd(TIM2, ENABLE);  //start trigger timer
      GPIO_SetBits(GPIOE, GPIO_Pin_8);  //shoot hypersonic
   }
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
uint16_t prescale = 0;

void setTimer()//1MHz => 1us; 1,000,000
{
 
  TIM_TimeBaseStructure.TIM_Period = 1;
  TIM_TimeBaseStructure.TIM_Prescaler = 72;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, DISABLE); // dont start this timer yet
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // interrupt enable
  
  
  prescale = (uint16_t)(SystemCoreClock / 100000) - 1;
  
  TIM_TimeBaseStructure.TIM_Period = 25000 - 1;// 1/4 second period
  TIM_TimeBaseStructure.TIM_Prescaler = prescale;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_Cmd(TIM4, ENABLE);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); // interrupt enable
  
  
}


int main()
{
  init();

  //LCD_Init();
  //LCD_Clear(WHITE);

  //Touch_Configuration();
  //Touch_Adjust();

  //setLED();
  setMotor();

  //LCD_ShowString(20, 30, "WED_TEAM05", BLACK, WHITE);
  //LCD_ShowString(20, 70, "OFF", RED, WHITE);
  //LCD_ShowString(80, 120, "BUT", RED, WHITE);
  //LCD_DrawRectangle(60, 100, 120, 160);

  while (1)
  {
    
    openDoor();
    for(int i = 0; i < 100000; ++i){}
    closeDoor();
    /*
    Touch_GetXY(&x, &y, 1);
    Convert_Pos(x, y, &x, &y);
    if (x <= 120 && x >= 60 && y >= 100 && y <= 160)
    {
      if (value == 0)
      {
        LCD_ShowString(20, 70, "OFF", WHITE, WHITE);
        LCD_ShowString(20, 70, "ON", RED, WHITE);
        value = 1;
      }
      else
      {
        value = 0;
        secondFl = 0;
        LCD_ShowString(20, 70, "ON", WHITE, WHITE);
        LCD_ShowString(20, 70, "OFF", RED, WHITE);
        LedOff(1);
        LedOff(2);
        closeDoor();
      }
    }*/
  }
}