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
#define   TASK_N 3
/*
*********************************************************************************************************
*                                            TYPES DEFINITIONS
*********************************************************************************************************
*/

typedef enum {
	LEDTASK=0,
	BUTTONTASK,
	USARTTASK
}task_n;

typedef enum {
	BUTTONPRESSED,
	BUTTONRELEASED,
	REDON,
	GREENON,
	BLUEON,
	REDOFF,
	GREENOFF,
	BLUEOFF,
	FAIL,
	GOOD,
	NONE
}msgs;

typedef enum {
	GREEN = 1,
	BLUE,
	RED
}colors;
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

static void AppTask_LED(void *p_arg);
static void AppTask_BUTTON(void *p_arg);
static void AppTask_USART(void *p_arg);

static void LED_switch(int ledNum, int reverse, OS_ERR* err, msgs* msgSend);
static void show_aim(OS_ERR* err, msgs* msgSend, int *aim);
static void show_success(OS_ERR* err, msgs* msgSend);
static void show_fail(OS_ERR* err, msgs* msgSend);
static void check_aim(int *ledStat, int *aim, msgs *msgSend, OS_ERR *err);
/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
/* ----------------- APPLICATION GLOBALS -------------- */
static  OS_TCB   AppTaskStartTCB;
static  CPU_STK  AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static  OS_TCB       Task_TCB[TASK_N];

static  CPU_STK  Task_Stack[TASK_N][APP_CFG_TASK_START_STK_SIZE];

task_t cyclic_tasks[TASK_N] = {
   {"Task_LED" , AppTask_LED,  4, &Task_Stack[LEDTASK][0] , &Task_TCB[LEDTASK]},
   {"Task_BUTTON", AppTask_BUTTON, 5, &Task_Stack[BUTTONTASK][0], &Task_TCB[BUTTONTASK]},
   {"Task_USART", AppTask_USART, 3, &Task_Stack[USARTTASK][0], &Task_TCB[USARTTASK]},
};

static OS_Q msgQ;

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

    /* BSP Init */
    //BSP_IntDisAll();  /* Disable all interrupts.                              */
    CPU_Init();                                                 /* Initialize the uC/CPU Services                       */
    Mem_Init();                                                 /* Initialize Memory Management Module                  */
    Math_Init();                                                /* Initialize Mathematical Module                       */
    /* OS Init */
    OSInit(&err);                                               /* Init uC/OS-III.                                      */
    OSQCreate((OS_Q *)&msgQ,
 	(CPU_CHAR *)"My Queue",
 	(OS_MSG_QTY)1,
 	(OS_ERR *)&err);

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
*                                          LED_switch
*
* Description : Function used to control LED. Switch on or off according to the ledNum and reverse. If
* 				reverse it will off the switch. Else it turns on. Then it post appropiate message.
*
* Arguments   : ledNum		is indicator of which led will be controlled.
* 				reverse     is a flag. If its 1 it switch on else it switch off the LED.
* 				err			is a pointer to a variable that will contain an error code returned by this function.
* 				msgSend		is a pointer pointing the message variable to be posted by message queue.
*
* Returns     : none
*
* Callers	  : AppTask_LED, show_aim, show_success, show_fail, check_aim
*
* Note: none
*********************************************************************************************************
*/

static void LED_switch(int ledNum, int reverse, OS_ERR* err, msgs* msgSend) {
	if (reverse) {
		switch(ledNum) {
		case GREEN:{BSP_LED_Off(GREEN); *msgSend = GREENOFF; break; }
		case BLUE:{BSP_LED_Off(BLUE); *msgSend = BLUEOFF; break; }
		case RED:{BSP_LED_Off(RED); *msgSend = REDOFF; break; }
		}
	}
	else{
		switch(ledNum) {
		case GREEN:{BSP_LED_On(GREEN); *msgSend = GREENON; break; }
		case BLUE:{BSP_LED_On(BLUE); *msgSend = BLUEON; break; }
		case RED:{BSP_LED_On(RED); *msgSend = REDON; break; }
		}
	}
	OSQPost((OS_Q *)&msgQ,
			(void *)msgSend,
			(OS_MSG_SIZE)sizeof(void*),
			(OS_OPT)OS_OPT_POST_FIFO,
			(OS_ERR *)err
	);
}

/*
*********************************************************************************************************
*                                          show_aim
*
* Description : Function used to show which LEDs should be switched on.
*
* Arguments   : err			is a pointer to a variable that will contain an error code returned by this function.
* 				msgSend		is a pointer pointing the message variable to be posted by message queue.
* 				aim			is a array containing information of which LED should be switched on.
*
* Returns     : none
*
* Callers	  : AppTask_LED
*
* Note: none
*********************************************************************************************************
*/

static void show_aim(OS_ERR* err, msgs* msgSend, int *aim) {
    for (int i = 0; i < 3; ++i) {
    	if (aim[i]) {
    		LED_switch(i+1, 0, err, msgSend);
    	}
    }
	OSTimeDlyHMSM(0u, 0u, 1u, 0u,
                  OS_OPT_TIME_HMSM_STRICT,
                  err);
    for (int i = 0; i < 3; ++i) {
    	if (aim[i]) {
    		LED_switch(i+1, 1, err, msgSend);
    	}
    }
}

/*
*********************************************************************************************************
*                                          show_success
*
* Description : Function used to switch Green LED on to show the answer is correct.
*
* Arguments   : err			is a pointer to a variable that will contain an error code returned by this function.
* 				msgSend		is a pointer pointing the message variable to be posted by message queue.
*
* Returns     : none
*
* Callers	  : check_aim
*
* Note: none
*********************************************************************************************************
*/

static void show_success(OS_ERR* err, msgs* msgSend) {
	LED_switch(GREEN, 0, err, msgSend);
	OSTimeDlyHMSM(0u, 0u, 1u, 0u,
                  OS_OPT_TIME_HMSM_STRICT,
                  err);
	LED_switch(GREEN, 1, err, msgSend);
}

/*
*********************************************************************************************************
*                                          show_fail
*
* Description : Function used to switch Red LED on to show the answer is incorrect.
*
* Arguments   : err			is a pointer to a variable that will contain an error code returned by this function.
* 				msgSend		is a pointer pointing the message variable to be posted by message queue.
*
* Returns     : none
*
* Callers	  : check_aim
*
* Note: none
*********************************************************************************************************
*/

static void show_fail(OS_ERR* err, msgs* msgSend) {
	LED_switch(RED, 0, err, msgSend);
	OSTimeDlyHMSM(0u, 0u, 1u, 0u,
                  OS_OPT_TIME_HMSM_STRICT,
                  err);
	LED_switch(RED, 1, err, msgSend);
}

/*
*********************************************************************************************************
*                                          check_aim
*
* Description : Function used to check whether currently switched on LEDs are same as the aim.
*
* Arguments   : ledStat		is an array containing information of which leds are currently is on.
* 				aim			is an array	containing information of which leds should be switched on.
* 				msgSend		is a pointer pointing the message variable to be posted by message queue.
* 				err			is a pointer to a variable that will contain an error code returned by this function.
*
* Returns     : none
*
* Callers	  : AppTask_LED
*
* Note: none
*********************************************************************************************************
*/

static void check_aim(int *ledStat, int *aim, msgs *msgSend, OS_ERR *err) {
	int result = 1;
	for (int i = 0; i < 3; ++i) {
		if (ledStat[i] != aim[i]) {
			result = 0;
		}
		if (ledStat[i]) {
			LED_switch(i+1, 1, err, msgSend);
		}
		ledStat[i] = 0;
	}
	if (result) {
		show_success(err, msgSend);
		*msgSend = GOOD;
	}
	else {
		show_fail(err, msgSend);
		*msgSend = FAIL;
	}
	OSQPost((OS_Q *)&msgQ,
			(void *)msgSend,
			(OS_MSG_SIZE)sizeof(void*),
			(OS_OPT)OS_OPT_POST_FIFO,
			(OS_ERR *)err
	);
}

/*
*********************************************************************************************************
*                                          AppTask_LED
*
* Description : Task used to control LEDs. Pend message from AppTask_BUTTON. If button is pressed, switches
* 				on and off LEDS. If button is released it checks the answer.
*
* Arguments   : p_arg (unused)
*
* Returns     : none
*
* Note: none
*********************************************************************************************************
*/

static void AppTask_LED(void *p_arg)
{
    OS_ERR  err;
    int led = 0;
    OS_MSG_SIZE size;
    CPU_TS ts;
    msgs msgSend;
    msgs curMsg = NONE;
    void *recieved;
    int ledStat[3] = {0, 0, 0};
    int aim[5][3] = {{1, 0, 0}, {1, 1, 0}, {1, 1, 1}, {0, 1, 1}, {0, 0, 1}};
    int aimidx = Math_Rand() % 5;
    show_aim(&err, &msgSend, aim[aimidx]);

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
		recieved = OSQPend((OS_Q *)&msgQ,
				(OS_TICK)1000u,
				(OS_OPT)OS_OPT_PEND_BLOCKING,
				(OS_MSG_SIZE *)&size,
				(CPU_TS *)&ts,
				(OS_ERR *)&err
				);
    	if (err != OS_ERR_TIMEOUT) {
    		curMsg = *(msgs*)recieved;
    	}
		if (curMsg == BUTTONPRESSED) {
			LED_switch(led+1, ledStat[led], &err, &msgSend);
	    	ledStat[led] = !ledStat[led];
	    	led = (led+1) % 3;
		}
		else if(curMsg == BUTTONRELEASED){
			check_aim(ledStat, aim[aimidx], &msgSend, &err);
			curMsg = NONE;
			aimidx = Math_Rand() % 5;
			show_aim(&err, &msgSend, aim[aimidx]);
			led = 0;
		}
    }
}

/*
*********************************************************************************************************
*                                          AppTask_BUTTON
*
* Description : Task used to take input from button. Post broadcast message to AppTask_LED and AppTask_USART
* 				whether the button is pressed or released.
*
* Arguments   : p_arg (unused)
*
* Returns     : none
*
* Note: none
*********************************************************************************************************
*/

static void AppTask_BUTTON(void *p_arg)
{
    OS_ERR  err;
    int button = 0;
    int last = 0;
    msgs msg;
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
    	button = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
    	if (button != last) {
        	if (button) {
        		msg = BUTTONPRESSED;
        	}
        	else {
        		msg = BUTTONRELEASED;
        	}
    		OSQPost((OS_Q *)&msgQ,
    				(void *)&msg,
					(OS_MSG_SIZE)sizeof(void*),
					(OS_OPT)OS_OPT_POST_ALL,
					(OS_ERR *)&err
    		);
    		last = button;
    	}
    	OSTimeDlyHMSM(0u, 0u, 0u, 100u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
    }
}


/*
*********************************************************************************************************
*                                          AppTask_USART
*
* Description : Task used to monitor the status of LEDs and button.
*
* Arguments   : p_arg (unused)
*
* Returns     : none
*
* Note: none
*********************************************************************************************************
*/
static void AppTask_USART(void *p_arg) {
	CPU_TS ts;
	OS_ERR err;
	OS_MSG_SIZE size;
	void* recieved;
	while (DEF_TRUE) {                                        /* Task body, always written as an infinite loop.       */
		recieved = OSQPend((OS_Q *)&msgQ,
				(OS_TICK)0u,
				(OS_OPT)OS_OPT_PEND_BLOCKING,
				(OS_MSG_SIZE *)&size,
				(CPU_TS *)&ts,
				(OS_ERR *)&err
				);
		switch(*(msgs*)recieved) {
		case BUTTONPRESSED:{send_string("Button Pressed\r\n"); break;}
		case BUTTONRELEASED:{send_string("Button Released\r\n"); break;}
		case GREENON:{send_string("Green On\r\n"); break;}
		case GREENOFF:{send_string("Green Off\r\n"); break;}
		case BLUEON:{send_string("Blue On\r\n"); break;}
		case BLUEOFF:{send_string("Blue Off\r\n"); break;}
		case REDON:{send_string("Red On\r\n"); break;}
		case REDOFF:{send_string("Red Off\r\n"); break;}
		case FAIL:{send_string("Wrong Answer\r\n"); break;}
		case GOOD:{send_string("Right Answer\r\n"); break;}
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
