
#include "Qitas.h"              
#include "Tasks.h"
#include "USART.h"
#include "delay.h"


void IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;		  		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOC, &GPIO_InitStructure);				
}

void RCC_init(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
		delay_init();  
}

int main()
{  
	OS_ERR err;
	CPU_SR_ALLOC();
	RCC_init();
	IO_Init();
	USART1_INIT();
	OSInit(&err); 
	OS_CRITICAL_ENTER();
	 printf("LED_task\n");
	
	OSTaskCreate((OS_TCB 	* )&TASK_INIT_TCB,		//任务控制块
				 (CPU_CHAR	* )"task init", 		//任务名字
                 (OS_TASK_PTR)TASK_INIT, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )TASK_INIT_PRIO,     //任务优先级
                 (CPU_STK   * )&TASK_INIT_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)INIT_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)INIT_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();
	OSStart(&err);
	
	while(1)
	{
			Convert_DHT11();
		  delay_ms(1119);
	}
}





