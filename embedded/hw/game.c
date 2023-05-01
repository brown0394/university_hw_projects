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
#include "lcd.h"
#include "touch.h"


#define WIDTH 10
#define HEIGHT 304

#define MAX_LCD_POSX 240
#define MAX_LCD_POSY 304
// right key 눌려져있는지 확인
int isRight = 0;
// left key 눌려져있는지 확인
int isLeft = 0;
// clock 설정

void RCC_Configure(void) // stm32f10x_rcc.c, .h 참고, 아래에 주석이 묶여있는 기능끼리 합쳐서 함수에 매개변수 전달 하시오!!
{
/////////////////////// TODO: Enable the APB2 peripheral clock using the function 'RCC_APB2PeriphClockCmd'///////////////////////
   
   /* JoyStick Up/Down port clock enable, LED port clock enable */
   
   /* UART 1 TX/RX port clock enable, USART1 clock enable */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /* Alternate Function IO clock enable */
   //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // UASRT CLOCK
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Joystick clock
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

// 핀 설정 


void GPIO_Configure(void) // stm32f10x_gpio.c, .h 참고
{
    GPIO_InitTypeDef GPIO_InitJoystick;
    

/////////////////////// TODO: Initialize the GPIO pins using the structure 'GPIO_InitTypeDef' and the function 'GPIO_Init'///////
   
    /* JoyStick LEFT pin setting, Input */
    GPIO_InitJoystick.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitJoystick.GPIO_Mode = GPIO_Mode_IPD ; // mode       GPIO_Mode_IPD #2
    GPIO_Init(GPIOC, &GPIO_InitJoystick);

    /* JoyStick RIGHT pin setting, Input */
    GPIO_InitJoystick.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitJoystick.GPIO_Mode = GPIO_Mode_IPD ; // mode       GPIO_Mode_IPD #2
    GPIO_Init(GPIOC, &GPIO_InitJoystick);

}

// EXIT 설정

void EXTI_Configure(void) // stm32f10x_gpio.c, .h 참고
{
    //EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitTypeDef EXTI_RIGHT;
    EXTI_InitTypeDef EXTI_LEFT;
////// TODO: Select the GPIO pin (Joystick, button) used as EXTI Line using function 'GPIO_EXTILineConfig'///////////////////////
   // TODO: Initialize the EXTI using the structure 'EXTI_InitTypeDef' and the function 'EXTI_Init'
   
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

    NVIC_InitTypeDef NVIC_LEFT;
    NVIC_InitTypeDef NVIC_RIGHT;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    // Joystick LEFT Use NVIC_InitLEFT
    NVIC_EnableIRQ(EXTI3_IRQn);
    NVIC_LEFT.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_LEFT.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_LEFT.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_LEFT.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_LEFT);
    
    // Joystick RIGHT Use NVIC_InitRIGHT
    NVIC_EnableIRQ(EXTI4_IRQn);
    NVIC_RIGHT.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_RIGHT.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_RIGHT.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_RIGHT.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_RIGHT);
}


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
int start = 0;
uint16_t touch_x = 0, touch_y = 0;
int MyScreen = 0; // 0 = Main_Screen, 1 = Gaming_Screen -1 = Game_Over_Screen

// GAME OVER시 Cancle 눌리면 나타나는 초기화면
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

void Game_start(void){
   MyScreen = 1;
   start = 0;
   init_Game();
   do
   {
      srand((int)malloc(NULL)); 
      if(Is_PlayerAlive()){
         Game_Over();
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
// LCD 관련 설정은 LCD_Init에 구현되어 있으므로 여기서 할 필요 없음
   SystemInit();
   RCC_Configure();
   GPIO_Configure();
   EXTI_Configure();
   NVIC_Configure();
   // ------------------------------------
   LCD_Init();
   Touch_Configuration();
   Touch_Adjust();
   LCD_Clear(WHITE);
   Main_Screen();
   while(1){
      Touch_GetXY(&touch_x, &touch_y, 1);
      Convert_Pos(touch_x,touch_y,&touch_x,&touch_y);
      check_touch();
      if(start){
         Game_start();
      }
   }
}
