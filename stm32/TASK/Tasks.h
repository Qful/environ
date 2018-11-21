#ifndef _TASKS_H_
#define _TASKS_H_

#include "includes.h"
#include "Qitas.h" 
#include "USART.h"

extern u8 GET_T[4];
extern u8 GET_H[4];
extern u8 GET_L[4];
extern u8 GET_G[4];

/*******************************************************************************
* Function Name  : TASK
* Description    : 
*******************************************************************************/

#define 	TASK_INIT_PRIO					3u
#define 	INIT_STK_SIZE 					512u
extern 		OS_TCB 		TASK_INIT_TCB;
extern 		CPU_STK 	TASK_INIT_STK[INIT_STK_SIZE];
void 	    TASK_INIT(void *p_arg);

/*******************************************************************************
* Function Name  : TASK
* Description    : 
*******************************************************************************/
#define 	Task_GetLX_PRIO					    12u
#define 	Task_GetLX_SIZE 				   128u
extern 		OS_TCB 		Task_GetLX_TCB;
extern 		CPU_STK 	Task_GetLX_STK[Task_GetLX_SIZE];
void 		Task_GetLX(void *p_arg);


/*******************************************************************************
* Function Name  : TASK
* Description    : 
*******************************************************************************/
#define 	Task_GetTEMP_PRIO					   5u
#define 	Task_GetTEMP_SIZE 				  128u
extern 		OS_TCB 		Task_GetTEMP_TCB;
extern 		CPU_STK 	Task_GetTEMP_STK[Task_GetTEMP_SIZE];
void 		Task_GetTEMP(void *p_arg);


#define 	Task_GetDHT_PRIO					   7u
#define 	Task_GetDHT_SIZE 				    128u
extern 		OS_TCB 		Task_GetDHT_TCB;
extern 		CPU_STK 	Task_GetDHT_STK[Task_GetDHT_SIZE];
void 		Task_GetDHT(void *p_arg);


#define 	Task_SI_TEMP_PRIO						   8u
#define 	Task_SI_TEMP_SIZE 				   128u
extern 		OS_TCB 		Task_SI_TEMP_TCB;
extern 		CPU_STK 	Task_SI_TEMP_STK[Task_SI_TEMP_SIZE];
void 		Task_SI_TEMP(void *p_arg);


#define 	Task_18B20_PRIO						   6u
#define 	Task_18B20_SIZE 				   128u
extern 		OS_TCB 		Task_18B20_TCB;
extern 		CPU_STK 	Task_18B20_STK[Task_18B20_SIZE];
void 		Task_18B20(void *p_arg);
/*******************************************************************************
* Function Name  : TASK
* Description    : 
*******************************************************************************/
#define 	Task_SI_HUMI_PRIO						  9u
#define 	Task_SI_HUMI_SIZE 				  128u
extern 		OS_TCB 		Task_SI_HUMI_TCB;
extern 		CPU_STK 	Task_SI_HUMI_STK[Task_SI_HUMI_SIZE];
void 		Task_SI_HUMI(void *p_arg);

/*******************************************************************************
* Function Name  : TASK
* Description    : 
*******************************************************************************/

#define 	LED0_TASK_PRIO					9u
#define 	LED0_STK_SIZE 					128u
extern 		OS_TCB 		Task_LED_TCB;
extern 		CPU_STK 	Task_LED_STK[LED0_STK_SIZE];
void 			Task_LED(void *p_arg);

#endif
