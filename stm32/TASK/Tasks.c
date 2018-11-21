
#include "Tasks.h"

static u8 GET_T[4]={0};
static u8 GET_H[4]={0};
static u8 GET_L[4]={0};
static u8 GET_G[4]={0};
/*******************************************************************************
* Function Name  : TASK
* Description    : check system 
*******************************************************************************/

OS_TCB TASK_INIT_TCB;
CPU_STK TASK_INIT_STK[INIT_STK_SIZE];

void TASK_INIT(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	
	
	OSTaskCreate((OS_TCB * )&Task_GetTEMP_TCB,		
		 (CPU_CHAR	* )"temp task", 		
						 (OS_TASK_PTR )Task_GetTEMP, 			
						 (void		* )0,					
						 (OS_PRIO	  )Task_GetTEMP_PRIO,     
						 (CPU_STK   * )&Task_GetTEMP_STK[0],	
						 (CPU_STK_SIZE)Task_GetTEMP_SIZE/10,	
						 (CPU_STK_SIZE)Task_GetTEMP_SIZE,		
						 (OS_MSG_QTY  )0,					
						 (OS_TICK	  )0,					
						 (void   	* )0,					
						 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
						 (OS_ERR 	* )&err);	
						 
	OSTaskCreate((OS_TCB * )&Task_GetLX_TCB,		
		 (CPU_CHAR	* )"LX task", 		
						 (OS_TASK_PTR )Task_GetLX, 			
						 (void		* )0,					
						 (OS_PRIO	  )Task_GetLX_PRIO,     
						 (CPU_STK   * )&Task_GetLX_STK[0],	
						 (CPU_STK_SIZE)Task_GetLX_SIZE/10,	
						 (CPU_STK_SIZE)Task_GetLX_SIZE,		
						 (OS_MSG_QTY  )0,					
						 (OS_TICK	  )0,					
						 (void   	* )0,					
						 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
						 (OS_ERR 	* )&err);							 
						 
							 
	OSTaskCreate((OS_TCB * )&Task_LED_TCB,		
			 (CPU_CHAR	* )"led0 task", 		
							 (OS_TASK_PTR )Task_LED, 			
							 (void		* )0,					
							 (OS_PRIO	  )LED0_TASK_PRIO,     
							 (CPU_STK   * )&Task_LED_STK[0],	
							 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
							 (CPU_STK_SIZE)LED0_STK_SIZE,		
							 (OS_MSG_QTY  )0,					
							 (OS_TICK	  )0,					
							 (void   	* )0,					
							 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
							 (OS_ERR 	* )&err);								 
				OS_TaskSuspend((OS_TCB*)&TASK_INIT_TCB,&err);		//挂起开始任务			 
				OS_CRITICAL_EXIT();	
}


/*******************************************************************************
* Function Name  : TASK
* Description    : 
*******************************************************************************/
OS_TCB 		Task_GetTEMP_TCB;
CPU_STK 	Task_GetTEMP_STK[LED0_STK_SIZE];

void Task_GetTEMP(void *p_arg)
{
		OS_ERR err;
		p_arg = p_arg;
		GET_T[1]=3;
		while(1)
		{
				if((GET_T[0]>GET_T[1])&&(GET_T[2]>GET_T[3]))
				{
						OSTaskCreate((OS_TCB * )&Task_SI_TEMP_TCB,		
												(CPU_CHAR	* )"si7021 task", 		
											 (OS_TASK_PTR )Task_SI_TEMP, 			
											 (void		* )0,					
											 (OS_PRIO	  )Task_SI_TEMP_PRIO,     
											 (CPU_STK   * )&Task_SI_TEMP_STK[0],	
											 (CPU_STK_SIZE)Task_SI_TEMP_SIZE/10,	
											 (CPU_STK_SIZE)Task_SI_TEMP_SIZE,		
											 (OS_MSG_QTY  )0,					
											 (OS_TICK	  )0,					
											 (void   	* )0,					
											 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
											 (OS_ERR 	* )&err);							
				}	
				else if((GET_T[0]==GET_T[1])&&(GET_T[2]==GET_T[3]))
				{
					    OSTaskDel(&Task_SI_TEMP_TCB,&err);
							if(OS_ERR_NONE == err)
							{
									printf("Del Task_SI_TEMP success!!\n");
							}
					    OSTaskDel(&Task_GetDHT_TCB,&err);
							if(OS_ERR_NONE == err)
							{
									printf("Del Task_GetDHT success!!\n");
							}
				}				
				else
				{
							OSTaskCreate((OS_TCB * )&Task_18B20_TCB,		
									 (CPU_CHAR	* )"Task_18B20_task", 		
													 (OS_TASK_PTR )Task_18B20, 			
													 (void		* )0,					
													 (OS_PRIO	  )Task_18B20_PRIO,     
													 (CPU_STK   * )&Task_18B20_STK[0],	
													 (CPU_STK_SIZE) Task_18B20_SIZE/10,	
													 (CPU_STK_SIZE) Task_18B20_SIZE,		
													 (OS_MSG_QTY  )0,					
													 (OS_TICK	  )0,					
													 (void   	* )0,					
													 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
													 (OS_ERR 	* )&err);	
													 
							OSTaskChangePrio(&Task_GetTEMP_TCB,53,&err);	
							if(OS_ERR_NONE == err)
							{
									printf("POP Task_GetTEMP ok!\n");
							}													 
				}					
		}
}
