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
#define  TASK_N 		  5
#define  SOUNDLEVEL 	  3
#define  SOUNDSTEP 		  200
#define  SOUNDSENSEPERIOD 6
#define  TRUE 			  1
#define  FALSE 			  0
/*
*********************************************************************************************************
*                                            TYPES DEFINITIONS
*********************************************************************************************************
*/

typedef enum {
	SOUNDPRIO=3,
	VIBPRIO,
	USARTPRIO,
	LEDPRIO,
	BUTTONPRIO,
}task_n;

typedef enum {
	LEDTASK=0,
	BUTTONTASK,
	USARTTASK,
	SOUNDTASK,
	VIBTASK
}task_p;

typedef enum {
	SOUNDNORMAL,
	SOUNDNOISY,
	SOUNDLOUD,
	SOUNDSILENCE,
	VIBDIS,
	VIBEN,
	NONE
}msgs;

typedef struct
{
   CPU_CHAR* name;
   OS_TASK_PTR func;
   OS_PRIO prio;
   CPU_STK* pStack;
   OS_TCB* pTcb;
}task_t;

typedef struct {
	int idx;
	int count;
}soundComp;

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static  void  AppTaskStart          (void     *p_arg);
static  void  AppTaskCreate         (void);
static  void  AppObjCreate          (void);

static void AppTask_LED(void *p_arg);
static void AppTask_SOUND(void *p_arg);
static void AppTask_BUTTON(void *p_arg);
static void AppTask_USART(void *p_arg);
static void AppTask_VIBMOTOR(void *p_arg);


static void Setup_Gpio(void);
static void ADC_Configure(void);
static void initSoundLevel(void);

static void redOn(void);
static void orangeOn(void);
static void greenOn(void);
static void blueOn(void);
static void sendButtonMessages(msgs* msgToSend, OS_ERR* err);
static uint16_t readADC(void);
static void sendSoundMessages(msgs* msgToSend, OS_ERR* err, CPU_BOOLEAN duplicate);
static msgs getSoundLevel(CPU_INT16U *soundCount);
static void vibPatternLoud(OS_ERR* err);
static void vibPatternNoisy(OS_ERR* err);
/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
/* ----------------- APPLICATION GLOBALS -------------- */
static  OS_TCB   AppTaskStartTCB;
static  CPU_STK  AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static  OS_TCB   Task_TCB[TASK_N];
static  CPU_STK  Task_Stack[TASK_N][APP_CFG_TASK_START_STK_SIZE];

task_t cyclic_tasks[TASK_N] = {
   {"Task_BUTTON", AppTask_BUTTON, BUTTONPRIO, &Task_Stack[BUTTONTASK][0], &Task_TCB[BUTTONTASK]},
   {"Task_LED" , AppTask_LED,  LEDPRIO, &Task_Stack[LEDTASK][0] , &Task_TCB[LEDTASK]},
   {"Task_USART", AppTask_USART, USARTPRIO, &Task_Stack[USARTTASK][0], &Task_TCB[USARTTASK]},
   {"Task_VIBRATOR", AppTask_VIBMOTOR, VIBPRIO, &Task_Stack[VIBTASK][0], &Task_TCB[VIBTASK]},
   {"TASK_SOUND", AppTask_SOUND, SOUNDPRIO, &Task_Stack[SOUNDTASK][0], &Task_TCB[SOUNDTASK]},
};

static CPU_INT16U soundLLoud;
static CPU_INT16U soundLNoisy;
static CPU_INT16U soundLNormal;
static CPU_INT16U soundLSilence;

static OS_Q  buttonQ;

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
    Setup_Gpio();
    ADC_Configure();

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
*                                          AppTask_LED
*
* Description : Task used to control LEDs. Pend message from AppTask_SOUND. It turns on or off according
* 				to the message it received.
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
    OS_MSG_SIZE size;
    CPU_TS ts;
    msgs recieved;

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
		recieved = *(msgs*)OSTaskQPend((OS_TICK)0u,
				(OS_OPT)OS_OPT_PEND_BLOCKING,
				(OS_MSG_SIZE *)&size,
				(CPU_TS *)&ts,
				(OS_ERR *)&err
				);
    	if (err == OS_ERR_NONE) {
    		switch (recieved) {
    		case SOUNDLOUD:     {redOn(); break;}
    		case SOUNDNOISY:    {orangeOn(); break;}
    		case SOUNDNORMAL:   {greenOn(); break;}
    		case SOUNDSILENCE : {blueOn(); break;}
    		}
		}
    }
}

/*
*********************************************************************************************************
*                                          AppTask_BUTTON
*
* Description : Task used to take input from button. If button is pressed it enables or disables the
* 				vibration motor and send its new sate to AppTask_USART.
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
    CPU_BOOLEAN button = Bit_RESET;
    CPU_BOOLEAN last = Bit_RESET;
    msgs msgToSend;
    CPU_BOOLEAN en = TRUE;
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
    	button = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
    	if (button != last) {//taking only one input even when user is keep pressing the button.
        	if (button) {
        		en = !en;
        		if (en) {
        			msgToSend = VIBEN;
        		}
        		else {
        			msgToSend = VIBDIS;
        		}
        		sendButtonMessages(&msgToSend, &err);
        	}
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
* Description : Task used to monitor the status.
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
	msgs lastMessage = NONE;
	msgs recieved;
	while (DEF_TRUE) {                                        /* Task body, always written as an infinite loop.       */
		recieved = *(msgs*)OSTaskQPend(
				(OS_TICK)0u,
				(OS_OPT)OS_OPT_PEND_BLOCKING,
				(OS_MSG_SIZE *)&size,
				(CPU_TS *)&ts,
				(OS_ERR *)&err
				);
		switch(recieved) {
			case VIBEN:{send_string("Vibration Motor Enabled\r\n"); break;}
			case VIBDIS:{send_string("Vibration Motor Disabled\r\n"); break;}
			case SOUNDLOUD:{send_string("Loud Sound Around\r\n"); break;}
			case SOUNDNOISY:{send_string("Noisy around\r\n"); break;}
			case SOUNDNORMAL:{send_string("Normal Around\r\n"); break;}
			case SOUNDSILENCE:{send_string("Silent Around\r\n"); break;}
		}
	}
 }

/*
*********************************************************************************************************
*                                          AppTask_SOUND
*
* Description : Task used to get value from sound sensor and send messages to other tasks according the
* 				sound level it computed.
*
* Arguments   : p_arg (unused)
*
* Returns     : none
*
* Note: none
*********************************************************************************************************
*/
static void AppTask_SOUND(void *p_arg) {
	OS_ERR err;
	msgs messageToSend;
	msgs lastMsgSent = NONE;
	uint16_t currentVal;
	CPU_INT16U count = 0;
	CPU_INT16U soundCount[SOUNDLEVEL] = {0};
	CPU_BOOLEAN duplicate = FALSE;
	while (DEF_TRUE) {                                        /* Task body, always written as an infinite loop.       */
		currentVal = readADC();
		++count;
		if (count > SOUNDSENSEPERIOD) {//you can change its sensitivity by changing SOUNDSENSERPERIOD value.
			count = 0;
			messageToSend = getSoundLevel(soundCount);
			if (lastMsgSent == messageToSend) {
				duplicate = TRUE;
			}
			else {
				duplicate = FALSE;
				lastMsgSent = messageToSend;
			}
	    	sendSoundMessages(&messageToSend, &err, duplicate);//only VIBMOTOR gets duplicate Msg.
		}
		if (currentVal <= soundLLoud) {//count the occurrence.
			++soundCount[SOUNDLOUD];
		}
		else if (currentVal <= soundLNoisy) {
    		++soundCount[SOUNDNOISY];
    	}
    	else if (currentVal <= soundLNormal) {
    		++soundCount[SOUNDNORMAL];
    	}
    	OSTimeDlyHMSM(0u, 0u, 0u, 100u,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
    }
}

/*
*********************************************************************************************************
*                                          AppTask_VIBRATOR
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

static void AppTask_VIBMOTOR(void *p_arg) {
	CPU_TS ts;
	OS_ERR err;
	OS_MSG_SIZE size;
	msgs recieved;
	msgs messageToSend;
	uint16_t currentVal;
	int en = TRUE;
	int soundLevel = SOUNDSILENCE;
	while (DEF_TRUE) {                                        /* Task body, always written as an infinite loop.       */
		recieved = *(msgs *)OSQPend(
				(OS_Q *)&buttonQ,
				(OS_TICK)0u,
				(OS_OPT)OS_OPT_PEND_NON_BLOCKING,
				(OS_MSG_SIZE *)&size,
				(CPU_TS *)&ts,
				(OS_ERR *)&err
				);
		if (err != OS_ERR_PEND_WOULD_BLOCK) {
			switch (recieved) {
				case VIBEN: {en = TRUE; break;}
				case VIBDIS: {en = FALSE; break;}
			}
		}
		recieved = *(msgs *)OSTaskQPend(
				(OS_TICK)0u,
				(OS_OPT)OS_OPT_PEND_BLOCKING,
				(OS_MSG_SIZE *)&size,
				(CPU_TS *)&ts,
				(OS_ERR *)&err
				);
		if (err != OS_ERR_TIMEOUT) {
			if (en) {
				switch (recieved) {
				case SOUNDLOUD: {vibPatternLoud(&err); break;}
				case SOUNDNOISY: {vibPatternNoisy(&err); break;}
				}
			}
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
   initSoundLevel();
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
            (OS_MSG_QTY    )1u,
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
	OS_ERR err;
	OSQCreate((OS_Q *)&buttonQ,
			(CPU_CHAR *) "buttonQ",
			(OS_MSG_QTY)1,
			(OS_ERR*) &err);
}

/*
*********************************************************************************************************
*                                          redOn()
*
* Description : Turn on red LED(PG0) and turn off other LEDs.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTask_LED()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void redOn(void) {
	GPIO_SetBits(GPIOG, GPIO_Pin_0);
	GPIO_ResetBits(GPIOG, GPIO_Pin_1);
	GPIO_ResetBits(GPIOG, GPIO_Pin_2);
}
/*
*********************************************************************************************************
*                                          orangeOn()
*
* Description : Turn on red(PG0) and green(PG1) LEDs and turn off blue LED.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTask_LED()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void orangeOn(void) {
	GPIO_SetBits(GPIOG, GPIO_Pin_0);
	GPIO_SetBits(GPIOG, GPIO_Pin_1);
	GPIO_ResetBits(GPIOG, GPIO_Pin_2);
}
/*
*********************************************************************************************************
*                                          greenOn()
*
* Description : Turn on green LED(PG1) and turn off other LEDs.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTask_LED()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void greenOn(void) {
	GPIO_ResetBits(GPIOG, GPIO_Pin_0);
	GPIO_SetBits(GPIOG, GPIO_Pin_1);
	GPIO_ResetBits(GPIOG, GPIO_Pin_2);
}
/*
*********************************************************************************************************
*                                          blueOn()
*
* Description : Turn on blue LED(PG2) and turn off other LEDs.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTask_LED()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void blueOn(void) {
	GPIO_ResetBits(GPIOG, GPIO_Pin_0);
	GPIO_ResetBits(GPIOG, GPIO_Pin_1);
	GPIO_SetBits(GPIOG, GPIO_Pin_2);
}
/*
*********************************************************************************************************
*                                          sendButtonMessages()
*
* Description : Post to AppTask_VIBMOTOR and AppTask_USART's task message que with same message.
*
* Argument(s) : msgToSend		pointer to the message to be sent.
* 				err				OS_ERR to get error.
*
* Return(s)   : none
*
* Caller(s)   : AppTask_BUTTON()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void sendButtonMessages(msgs* msgToSend, OS_ERR* err) {
	OSQPost(
		(OS_Q *)&buttonQ,
		(void *)msgToSend,
		(OS_MSG_SIZE)sizeof(msgToSend),
		(OS_OPT)OS_OPT_POST_FIFO,
		(OS_ERR *)err
	);
	OSTaskQPost(
		(OS_TCB *)&Task_TCB[USARTTASK],
		(void *)msgToSend,
		(OS_MSG_SIZE)sizeof(msgToSend),
		(OS_OPT)OS_OPT_POST_FIFO,
		(OS_ERR *)err
	);
}
/*
*********************************************************************************************************
*                                          readADC()
*
* Description : Read analog value from sound sensor. Bigger the value smaller the sound.
*
* Argument(s) : none
*
* Return(s)   : uint16_t	 analog input from sound sensor
*
* Caller(s)   : AppTask_SOUND()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static uint16_t readADC(void) {
	 ADC_RegularChannelConfig(ADC3, ADC_Channel_9,1, ADC_SampleTime_15Cycles);
	 ADC_SoftwareStartConv(ADC3);//Start the conversion
	 while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC));//Processing the conversion
	 return ADC_GetConversionValue(ADC3); //Return the converted data
}
/*
*********************************************************************************************************
*                                          sendSoundMessages()
*
* Description : Post to AppTask_VIBMOTOR, AppTask_USART and AppTask_LED's task message queue with same message.
*
* Argument(s) : msgToSend		pointer to the message to be sent.
* 				err				OS_ERR to get error.
* 				duplicate		indicates whether its message is same as last time.
*
* Return(s)   : none
*
* Caller(s)   : AppTask_SOUND()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void sendSoundMessages(msgs* msgToSend, OS_ERR* err, CPU_BOOLEAN duplicate) {
	OSTaskQPost(
		(OS_TCB *)&Task_TCB[VIBTASK],
		(void *)msgToSend,
		(OS_MSG_SIZE)sizeof(msgToSend),
		(OS_OPT)OS_OPT_POST_FIFO,
		(OS_ERR *)err
	);
	if (!duplicate) {
		OSTaskQPost(
			(OS_TCB *)&Task_TCB[LEDTASK],
			(void *)msgToSend,
			(OS_MSG_SIZE)sizeof(msgToSend),
			(OS_OPT)OS_OPT_POST_FIFO,
			(OS_ERR *)err
		);
		OSTaskQPost(
			(OS_TCB *)&Task_TCB[USARTTASK],
			(void *)msgToSend,
			(OS_MSG_SIZE)sizeof(msgToSend),
			(OS_OPT)OS_OPT_POST_FIFO,
			(OS_ERR *)err
		);
	}
}
/*
*********************************************************************************************************
*                                          getSoundLevel()
*
* Description : Return sound level which has been sensed the most time.
*
* Argument(s) : soundCount		Array of counted value. Containing counts of each sound level occurence.
*
* Return(s)   : msgs	 msgs value indication sound level.
*
* Caller(s)   : AppTask_SOUND()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static msgs getSoundLevel(CPU_INT16U *soundCount) {
	soundComp comp = {SOUNDSILENCE, 0};
	for (int i = SOUNDNORMAL; i < SOUNDLEVEL; ++i) {
		if (comp.count <= soundCount[i]) {
			comp.idx = i;
			comp.count = soundCount[i];
		}
		soundCount[i] = 0;
	}
	return comp.idx;
}
/*
*********************************************************************************************************
*                                          vibPatternLoud()
*
* Description : Vibration pattern for sound level Loud. Vibrate two times.
*
* Argument(s) : OS_ERR*		pointer to err.
*
* Return(s)   : none
*
* Caller(s)   : AppTask_VIBMOTOR()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void vibPatternLoud(OS_ERR* err) {
	GPIO_SetBits(GPIOG, GPIO_Pin_3);
	OSTimeDlyHMSM(0u, 0u, 0u, 500u,
                  OS_OPT_TIME_HMSM_STRICT,
                  err);
	GPIO_ResetBits(GPIOG, GPIO_Pin_3);
	OSTimeDlyHMSM(0u, 0u, 0u, 500u,
                  OS_OPT_TIME_HMSM_STRICT,
                  err);
	GPIO_SetBits(GPIOG, GPIO_Pin_3);
	OSTimeDlyHMSM(0u, 0u, 0u, 500u,
                  OS_OPT_TIME_HMSM_STRICT,
                  err);
	GPIO_ResetBits(GPIOG, GPIO_Pin_3);
	OSTimeDlyHMSM(0u, 0u, 1u, 0u,
                  OS_OPT_TIME_HMSM_STRICT,
                  err);
}
/*
*********************************************************************************************************
*                                          vibPatternNoisy()
*
* Description : Vibration pattern for sound level Noisy. Vibrate one time.
*
* Argument(s) : OS_ERR*		pointer to err.
*
* Return(s)   : none
*
* Caller(s)   : AppTask_VIBMOTOR()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void vibPatternNoisy(OS_ERR* err) {
	GPIO_SetBits(GPIOG, GPIO_Pin_3);
	OSTimeDlyHMSM(0u, 0u, 0u, 500u,
                  OS_OPT_TIME_HMSM_STRICT,
                  err);
	GPIO_ResetBits(GPIOG, GPIO_Pin_3);
	OSTimeDlyHMSM(0u, 0u, 1u, 0u,
                  OS_OPT_TIME_HMSM_STRICT,
                  err);
}
/*
*********************************************************************************************************
*                                          initSoundLevel()
*
* Description : Initialize sound level standard. You can change SOUNDSTEP to modify sound sensitivity.
* 				If the place is noisy when the machine starts, it may can malfunction.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void initSoundLevel(void) {
	soundLSilence = readADC();
	soundLNormal = soundLSilence - SOUNDSTEP;
	soundLNoisy = soundLNormal - SOUNDSTEP;
	soundLLoud = soundLNoisy - SOUNDSTEP;
}

static void Setup_Gpio(void)
{
   GPIO_InitTypeDef IO_init = {0};

   BSP_PeriphEn(BSP_PERIPH_ID_GPIOG);
   RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

   IO_init.GPIO_Mode   = GPIO_Mode_OUT;
   IO_init.GPIO_OType  = GPIO_OType_PP;
   IO_init.GPIO_Speed  = GPIO_Speed_2MHz;
   IO_init.GPIO_PuPd   = GPIO_PuPd_NOPULL;
   IO_init.GPIO_Pin    = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
   //PG0 : RED, PG1 : GREEN, PG2 : BLUE, PG3 : VIB
   GPIO_Init(GPIOG, &IO_init);

   BSP_PeriphEn(BSP_PERIPH_ID_GPIOF);
   BSP_PeriphEn(BSP_PERIPH_ID_ADC3);
   BSP_PeriphEn(BSP_PERIPH_ID_TIM1);
   RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

   GPIO_InitTypeDef sound_init = {0};
   sound_init.GPIO_Pin = GPIO_Pin_3;
   sound_init.GPIO_Speed = GPIO_Speed_2MHz;
   sound_init.GPIO_Mode = GPIO_Mode_AIN;
   sound_init.GPIO_OType  = GPIO_OType_PP;
   sound_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

   GPIO_Init(GPIOF, &sound_init);//pf3
}

static void ADC_Configure(void){

  ADC_InitTypeDef ADC_1;
  ADC_DeInit();
  ADC_1.ADC_Resolution = ADC_Resolution_12b;
  ADC_1.ADC_ScanConvMode = DISABLE;
  ADC_1.ADC_ContinuousConvMode = DISABLE;
  ADC_1.ADC_ExternalTrigConv = DISABLE;
  ADC_1.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_1.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_1.ADC_NbrOfConversion = 1;

  ADC_CommonInitTypeDef ADC_2;
  ADC_2.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_2.ADC_Mode = ADC_Mode_Independent;
  ADC_2.ADC_Prescaler = ADC_Prescaler_Div4;
  ADC_2.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_8Cycles;
  ADC_CommonInit(&ADC_2);

  ADC_Init(ADC3, &ADC_1);
  ADC_ITConfig(ADC3,ADC_IT_EOC,ENABLE);
  ADC_Cmd(ADC3, ENABLE);

}
