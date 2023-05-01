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

uint16_t value = 0, x, y;
//int color[12] = {WHITE, CYAN, BLUE, RED, MAGENTA, LGRAY, GREEN, YELLOW, BROWN, BRRED, GRAY};

void APB2ClockEnable()
{
  // RCC
  *(RCC_APB2ENR) |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // interrupt
}

void LedGpioConfig()
{
  // LED1 - PD2 output
  *GPIO_D_CRL &= ~0xf00; // reset
  *GPIO_D_CRL |= 0x300;  // output mode
  // LED2 - PD3
  *GPIO_D_CRL &= ~0xf000; // reset
  *GPIO_D_CRL |= 0x3000;  // output mode
  // LED3 - PD4
  *GPIO_D_CRL &= ~0xf0000; // reset
  *GPIO_D_CRL |= 0x30000;  // output mode
  // LED4 - PD7
  *GPIO_D_CRL &= ~0xf0000000; // reset
  *GPIO_D_CRL |= 0x30000000;  // output mode
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

void init()
{
  NVIC_Configure();
  APB2ClockEnable();
  LedGpioConfig();
}

// #region led on and off functions
void LedOn(unsigned char i)
{
  switch (i)
  {
  case 1:
    *GPIO_D_BSRR |= (0x1 << 2);
    break;
  case 2:
    *GPIO_D_BSRR |= (0x1 << 3);
    break;
  case 3:
    *GPIO_D_BSRR |= (0x1 << 4);
    break;
  case 4:
    *GPIO_D_BSRR |= (0x1 << 7);
    break;
  default:
    break;
  }
}

void LedOff(unsigned char i)
{
  switch (i)
  {
  case 1:
    *GPIO_D_BSRR |= ((0x1 << 16) << 2);
    break;
  case 2:
    *GPIO_D_BSRR |= ((0x1 << 16) << 3);
    break;
  case 3:
    *GPIO_D_BSRR |= ((0x1 << 16) << 4);
    break;
  case 4:
    *GPIO_D_BSRR |= ((0x1 << 16) << 7);
    break;
  default:
    break;
  }
}
// #endregion

int flag = 0;
int secondFl = 0;
uint32_t count = 0;

void TIM2_IRQHandler(void)
{
  if (value == 1)
  {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
      flag ^= 1;

      if (flag == 1)
      {
        resetDoor();
        LedOn(2);
        secondFl++;
      }
      else
      {
        closeDoor();
        LedOff(2);
      }

      if (secondFl >= 5 && secondFl < 10)
      {
        openDoor();
        LedOn(1);
      }
      else if (secondFl == 10)
      {
        closeDoor();
        LedOff(1);
        secondFl = 0;
      }
    }
  }
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
uint16_t prescale = 0;

void setLED()
{
  prescale = (uint16_t)(SystemCoreClock / 100000) - 1;

  TIM_TimeBaseStructure.TIM_Period = 50000 - 1;
  TIM_TimeBaseStructure.TIM_Prescaler = prescale;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // interrupt enable
}

void setMotor()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  prescale = (uint16_t)(SystemCoreClock / 1000000) - 1;

  TIM_TimeBaseStructure.TIM_Period = 20000 - 1;
  TIM_TimeBaseStructure.TIM_Prescaler = prescale;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 700;
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_Cmd(TIM4, ENABLE);
}

// #region motor open, close, reset
void openDoor()
{
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 2300;

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
}

void closeDoor()
{
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 700;

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
}

void resetDoor()
{
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1500;

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
}

void changeDoor(uint16_t pulse)
{
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = pulse;

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
}

// #endregion

int main()
{
  init();

  //LCD_Init();
  //LCD_Clear(WHITE);

  //Touch_Configuration();
  //Touch_Adjust();
  uint16_t pulse = 700;

  //setLED();
  setMotor();

  //LCD_ShowString(20, 30, "WED_TEAM05", BLACK, WHITE);
  //LCD_ShowString(20, 70, "OFF", RED, WHITE);
  //LCD_ShowString(80, 120, "BUT", RED, WHITE);
  //LCD_DrawRectangle(60, 100, 120, 160);

  while (1)
  {
    scanf("%d", &pulse);
    changeDoor(pulse);
    
    //openDoor();
    //for(int i = 0; i < 100000; ++i){}
    //closeDoor();
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