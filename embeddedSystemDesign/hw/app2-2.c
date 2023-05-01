/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                       IAR Development Kits
*                                              on the
*
*                                    STM32F429II-SK KICKSTART KIT
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : YS
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <includes.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  APP_TASK_EQ_0_ITERATION_NBR              16u
#define NUM_LEDS 3
/*
*********************************************************************************************************
*                                            TYPES DEFINITIONS
*********************************************************************************************************
*/
typedef enum {
   TASK_500MS,
   TASK_1000MS,
   TASK_2000MS,

   TASK_N=4
}task_e;
typedef enum {
	LED_ON=12,
	LED_OFF,
	LED_BLINK,
	LED_DONOTHING,
	LED_RESET
}led_op;
typedef struct
{
   CPU_CHAR* name;
   OS_TASK_PTR func;
   OS_PRIO prio;
   CPU_STK* pStack;
   OS_TCB* pTcb;
}task_t;

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static  void  AppTaskStart          (void     *p_arg);
static  void  AppTaskCreate         (void);
static  void  AppObjCreate          (void);

static void AppTask_LED0(void *p_arg);
static void AppTask_LED1(void *p_arg);
static void AppTask_LED2(void *p_arg);
static void AppTask_USART(void *p_arg);

//static void Setup_Gpio(void);
//static void USARTTest(void);
static void LEDOpInit(void);
static int checkStr(char* c, int idx);
static void setOps(int idx, led_op op);
unsigned short setOperation(int command, int numLed, unsigned short blinkTime);
void resumeDelays(int resume, int idx);
/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
/* ----------------- APPLICATION GLOBALS -------------- */
static  OS_TCB   AppTaskStartTCB;
static  CPU_STK  AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static  OS_TCB       Task_LED_TCB[3];
static  OS_TCB       Task_USART_TCB;

static  CPU_STK  Task_LED0_Stack[APP_CFG_TASK_START_STK_SIZE];
static  CPU_STK  Task_LED1_Stack[APP_CFG_TASK_START_STK_SIZE];
static  CPU_STK  Task_LED2_Stack[APP_CFG_TASK_START_STK_SIZE];
static  CPU_STK  Task_USART_Stack[APP_CFG_TASK_START_STK_SIZE];

task_t cyclic_tasks[TASK_N] = {
   {"Task_LED0" , AppTask_LED0,  2, &Task_LED0_Stack[0] , &Task_LED_TCB[0]},
   {"Task_LED1", AppTask_LED1, 2, &Task_LED1_Stack[0], &Task_LED_TCB[1]},
   {"Task_LED2", AppTask_LED2, 2, &Task_LED2_Stack[0], &Task_LED_TCB[2]},
   {"Task_USART", AppTask_USART, 3, &Task_USART_Stack[0], &Task_USART_TCB},
};

int receivePrinted = 0;
led_op led_ops[NUM_LEDS];
unsigned short blink[NUM_LEDS];

/* ------------ FLOATING POINT TEST TASK -------------- */
/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int main(void)
{
    OS_ERR  err;

    /* Basic Init */
    RCC_DeInit();
//    SystemCoreClockUpdate();
    //Setup_Gpio();

    /* BSP Init */
    //BSP_IntDisAll();  /* Disable all interrupts.                              */
    LEDOpInit();
    CPU_Init();                                                 /* Initialize the uC/CPU Services                       */
    Mem_Init();                                                 /* Initialize Memory Management Module                  */
    Math_Init();                                                /* Initialize Mathematical Module                       */
    /* OS Init */
    OSInit(&err);                                               /* Init uC/OS-III.                                      */

    OSTaskCreate((OS_TCB       *)&AppTaskStartTCB,              /* Create the start task                                */
                 (CPU_CHAR     *)"App Task Start",
                 (OS_TASK_PTR   )AppTaskStart,
                 (void         *)0u,
                 (OS_PRIO       )APP_CFG_TASK_START_PRIO,
                 (CPU_STK      *)&AppTaskStartStk[0u],
                 (CPU_STK_SIZE  )AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE / 10u],
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY    )0u,
                 (OS_TICK       )0u,
                 (void         *)0u,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

   OSStart(&err);   /* Start multitasking (i.e. give control to uC/OS-III). */

   (void)&err;

   return (0u);
}
/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/
static  void  AppTaskStart (void *p_arg)
{
    OS_ERR  err;

   (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    BSP_Tick_Init();                                            /* Initialize Tick Services.                            */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

   // BSP_LED_Off(0u);                                            /* Turn Off LEDs after initialization                   */

   APP_TRACE_DBG(("Creating Application Kernel Objects\n\r"));
   AppObjCreate();                                             /* Create Applicaiton kernel objects                    */

   APP_TRACE_DBG(("Creating Application Tasks\n\r"));
   AppTaskCreate();                                            /* Create Application tasks                             */
}

/*
*********************************************************************************************************
*                                          AppTask_LED0
*
* Description : Task used to control LED1. Read command from led_ops and change the status.
*
* Arguments   : p_arg (unused)
*
* Returns     : none
*
* Note: Long period used to measure timing in person
*********************************************************************************************************
*/
static void AppTask_LED0(void *p_arg)
{
    OS_ERR  err;

    unsigned short time_interval_sec = 0u;
    unsigned int time_interval_milisec = 100u;
    short toggle = 0;
    CPU_SR_ALLOC();
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
    	OS_CRITICAL_ENTER();
    		led_op op = led_ops[0];
    	OS_CRITICAL_EXIT();
    	switch (op) {
    	case LED_DONOTHING: {break;}
    	case LED_ON: {BSP_LED_On(1); toggle = 0; break;}
    	case LED_OFF: {BSP_LED_Off(1); toggle = 0; break;}
    	case LED_BLINK: {
    		OS_CRITICAL_ENTER();
    			time_interval_sec = blink[0];
    		OS_CRITICAL_EXIT();
    		time_interval_milisec = 0u;
    		toggle = 1;
    		break;}
    	}
    	if (toggle) {
    		BSP_LED_Toggle(1);
    	}
    	else {
    		time_interval_sec = 0u;
    		time_interval_milisec = 100u;
    	}
        OSTimeDlyHMSM(0u, 0u, time_interval_sec, time_interval_milisec,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
    }
}

/*
*********************************************************************************************************
*                                          AppTask_LED1
*
* Description : Task used to control LED2. Read command from led_ops and change the status.
*
* Arguments   : p_arg (unused)
*
* Returns     : none
*
* Note: Long period used to measure timing in person
*********************************************************************************************************
*/
static void AppTask_LED1(void *p_arg)
{
    OS_ERR  err;
    unsigned short time_interval_sec = 0u;
    unsigned int time_interval_milisec = 100u;
    short toggle = 0;
    CPU_SR_ALLOC();
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
    	OS_CRITICAL_ENTER();
    		led_op op = led_ops[1];
    	OS_CRITICAL_EXIT();
    	switch (op) {
    	case LED_DONOTHING: {break;}
    	case LED_ON: {BSP_LED_On(2); toggle = 0; break;}
    	case LED_OFF: {BSP_LED_Off(2); toggle = 0; break;}
    	case LED_BLINK: {
    		OS_CRITICAL_ENTER();
    			time_interval_sec = blink[1];
    		OS_CRITICAL_EXIT();
    		time_interval_milisec = 0u;
    		toggle = 1;
    		break;}
    	}
    	if (toggle) {
    		BSP_LED_Toggle(2);
    	}
    	else {
    		time_interval_sec = 0u;
    		time_interval_milisec = 100u;
    	}
        OSTimeDlyHMSM(0u, 0u, time_interval_sec, time_interval_milisec,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
    }
}

/*
*********************************************************************************************************
*                                          AppTask_LED2
*
* Description : Task used to control LED3. Read command from led_ops and change the status.
*
* Arguments   : p_arg (unused)
*
* Returns     : none
*
* Note: Long period used to measure timing in person
*********************************************************************************************************
*/
static void AppTask_LED2(void *p_arg)
{
    OS_ERR  err;
    unsigned short time_interval_sec = 0u;
    unsigned int time_interval_milisec = 100u;
    short toggle = 0;
    CPU_SR_ALLOC();
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
    	OS_CRITICAL_ENTER();
    		led_op op = led_ops[2];
    	OS_CRITICAL_EXIT();
    	switch (op) {
    	case LED_DONOTHING: {break;}
    	case LED_ON: {BSP_LED_On(3); toggle = 0; break;}
    	case LED_OFF: {BSP_LED_Off(3); toggle = 0; break;}
    	case LED_BLINK: {
    		OS_CRITICAL_ENTER();
    			time_interval_sec = blink[2];
    		OS_CRITICAL_EXIT();
    		time_interval_milisec = 0u;
    		toggle = 1;
    		break;}
    	}
    	if (toggle) {
    		BSP_LED_Toggle(3);
    	}
    	else {
    		time_interval_sec = 0u;
    		time_interval_milisec = 100u;
    	}
        OSTimeDlyHMSM(0u, 0u, time_interval_sec, time_interval_milisec,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
    }
}


/*
*********************************************************************************************************
*                                          AppTask_USART
*
* Description : Task used to get command by USART. Commands : led#on, led#off, led#blink#, reset.
* 			    # after blink means the second period of toggle.
*
* Arguments   : p_arg (unused)
*
* Returns     : none
*
* Note: Long period used to measure timing in person
*********************************************************************************************************
*/
static void AppTask_USART(void *p_arg) {
    int strIdx = 0;
    char str[10];
    CPU_SR_ALLOC();
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
    	while (USART_ReceiveData(Nucleo_COM1) != '\r') {
    		while(USART_GetFlagStatus(Nucleo_COM1, USART_FLAG_RXNE) == RESET){}
    		 uint16_t c = USART_ReceiveData(Nucleo_COM1);
    		 USART_SendData(Nucleo_COM1, c);
    		 str[strIdx] = c;
    		 strIdx = checkStr(str, strIdx);
    		 if (strIdx > 9) {
    			 resumeDelays(setOperation(strIdx, str[3]-'1', str[9]-'0'), str[3]-'1');
    			 strIdx = 0;
    		 }
    		 receivePrinted = 0;
    	}
    	if (!receivePrinted) {
    		receivePrinted = 1;
    		strIdx = 0;
    		send_string("\n\rReceive End\n\r");
    	}
    }
}
/*
*********************************************************************************************************
*                                          AppTaskCreate()
*
* Description : Create application tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
   OS_ERR  err;

   u8_t idx = 0;
   task_t* pTask_Cfg;
   for(idx = 0; idx < TASK_N; idx++)
   {
      pTask_Cfg = &cyclic_tasks[idx];

      OSTaskCreate(
            pTask_Cfg->pTcb,
            pTask_Cfg->name,
            pTask_Cfg->func,
            (void         *)0u,
            pTask_Cfg->prio,
            pTask_Cfg->pStack,
            pTask_Cfg->pStack[APP_CFG_TASK_START_STK_SIZE / 10u],
            APP_CFG_TASK_START_STK_SIZE,
            (OS_MSG_QTY    )0u,
            (OS_TICK       )0u,
            (void         *)0u,
            (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            (OS_ERR       *)&err
      );
   }
}


/*
*********************************************************************************************************
*                                          AppObjCreate()
*
* Description : Create application kernel objects tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  AppObjCreate (void)
{

}

/*
*********************************************************************************************************
*                                          Setup_Gpio()
*
* Description : Configure LED GPIOs directly
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     :
*              LED1 PB0
*              LED2 PB7
*              LED3 PB14
*
*********************************************************************************************************
*/
static void Setup_Gpio(void)
{
   GPIO_InitTypeDef led_init = {0};

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

   led_init.GPIO_Mode   = GPIO_Mode_OUT;
   led_init.GPIO_OType  = GPIO_OType_PP;
   led_init.GPIO_Speed  = GPIO_Speed_2MHz;
   led_init.GPIO_PuPd   = GPIO_PuPd_NOPULL;
   led_init.GPIO_Pin    = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_14;

   GPIO_Init(GPIOB, &led_init);
}

/************************************************/
static void USARTTest(void) {
    while(USART_GetFlagStatus(Nucleo_COM1, USART_FLAG_TXE) == RESET){}
	USART_SendData(Nucleo_COM1, (uint8_t) '*');
	send_string("\n\rhello world \n\r");
}

static void LEDOpInit(void) {
	for (int i = 0; i < NUM_LEDS; ++i) {
		led_ops[i] = LED_DONOTHING;
		blink[i] = 0u;
	}
}

static void setOps(int idx, led_op op) {
	OS_CRITICAL_ENTER();
		led_ops[idx] = op;
	OS_CRITICAL_EXIT();
}

/*
*********************************************************************************************************
*                                          checkStr()
*
* Description : Check whether input sequence is correct.
*
* Argument(s) : char array c, index of c int idx.
*
* Return(s)   : If sequence is correct idx+1. If not correct 0. If sequence complete command#.
*
* Caller(s)   : AppTask_USART()
*
* Note(s)     :
*
*********************************************************************************************************
*/

static int checkStr(char* c, int idx) {
	switch (idx) {
	case 0: { if (c[idx] == 'l' || c[idx] == 'r')return idx+1; break;}
	case 1: { if (c[idx] == 'e') return idx+1; break;}
	case 2: {
		if (c[idx] == 'd' && c[0] == 'l')
			return idx+1;
		else if (c[idx] == 's' && c[0] == 'r')
			return idx+1;
		break;
	}
	case 3: {
		if ((c[idx] >'0' && c[idx] < '4') && c[idx-1] == 'd')
			return idx+1;
		else if (c[idx] == 'e' && c[idx-1] == 's')
			return idx+1;
		break;
	}
	case 4: {
		if (c[idx] == 't' && c[idx-1] == 'e')
			return LED_RESET;
		else if ((c[idx] == 'o' || c[idx] == 'b')  && (c[idx-1] >'0' && c[idx-1] < '4'))
			return idx+1;
		break;
	}
	case 5: {
		if (c[idx] == 'n' && c[idx-1] == 'o')
			return LED_ON;
		else if (c[idx] == 'f' && c[idx-1] == 'o')
			return idx+1;
		else if (c[idx] == 'l' && c[idx-1] == 'b')
			return idx+1;
		break;
	}
	case 6: {
		if (c[idx] == 'f' && c[idx-1] == 'f')
			return LED_OFF;
		else if (c[idx] == 'i' && c[idx-1] == 'l')
			return idx+1;
		break;
	}
	case 7: { if (c[idx] == 'n' && c[idx-1] == 'i')	return idx+1;	break;}
	case 8: { if (c[idx] == 'k' && c[idx-1] == 'n')	return idx+1;	break;}
	case 9: { if ((c[idx] >'0' && c[idx] <= '9') && c[idx-1] == 'k')	return LED_BLINK;	break;}
	}
	return 0;
}

/*
*********************************************************************************************************
*                                          setOperation()
*
* Description : Store command read from USART to global variable.
*
* Argument(s) : int command storing command. int numLed shows which led is getting the command.
* 				unsigned short blinkTime is the period of blink.
*
* Return(s)   : resume flag. 0 no resume. 1 specific led resume. 2 all led resume.
*
* Caller(s)   : AppTask_USART()
*
* Note(s)     :
*
*********************************************************************************************************
*/

unsigned short setOperation(int command, int numLed, unsigned short blinkTime) {
	unsigned short resume = 0;
	switch (command) {
	case LED_ON:
	case LED_OFF: {
		setOps(numLed, command);
		send_string("\n\r");
		resume = 1;
		break;
	}
	case LED_RESET: {
		for (int i = 0; i < NUM_LEDS; ++i) {
			setOps(i, LED_OFF);
		}
		send_string("\n\r");
		resume = 2;
		break;
	}
	case LED_BLINK: {
		setOps(numLed, command);
		OS_CRITICAL_ENTER();
		blink[numLed] = blinkTime;
		OS_CRITICAL_EXIT();
		send_string("\n\r");
		break;
	}
	}
	return resume;
}

/*
*********************************************************************************************************
*                                          resumeDelays()
*
* Description : When command is changed from blink. Break the delay.
*
* Argument(s) : int resume for flag. int idx for resuming specific led.
*
* Return(s)   :
*
* Caller(s)   : setOperation()
*
* Note(s)     :
*
*********************************************************************************************************
*/

void resumeDelays(int resume, int idx) {
	if (resume) {
		OS_ERR err;
		if (resume > 1) {
			for (int i = 0; i < NUM_LEDS; ++i) {
				OSTimeDlyResume(&Task_LED_TCB[i], &err);
			}
		} else {
			OSTimeDlyResume(&Task_LED_TCB[idx], &err);
		}
	}
}
