
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
	
	OSTaskCreate((OS_TCB 	* )&TASK_INIT_TCB,		//������ƿ�
				 (CPU_CHAR	* )"task init", 		//��������
                 (OS_TASK_PTR)TASK_INIT, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )TASK_INIT_PRIO,     //�������ȼ�
                 (CPU_STK   * )&TASK_INIT_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)INIT_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)INIT_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();
	OSStart(&err);
	
	while(1)
	{
			Convert_DHT11();
		  delay_ms(1119);
	}
}





