
#include "USART.h"

#define   USART_BUFF_SIZE 128

typedef struct USART_BUF {
	u16    cnt;
	u8     Buff[USART_BUFF_SIZE];
} USART_BUF;


/*******************************************************************************
* Function Name  : USART_INIT
* Description    : 
*******************************************************************************/
void USART1_INIT()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;//一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
    //USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); 
    USART_Cmd(USART1, ENABLE); //使能串口 
	NVIC_USART1();
}

void USART3_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);//使能GPIOA,G时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART2时钟
    /*串口GPIO端口配置*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    

    USART_InitStructure.USART_BaudRate = 115200;//一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
    USART_ClearFlag(USART3,USART_FLAG_TC);
    
    USART_Cmd(USART3, ENABLE); //使能串口 
}
/*******************************************************************************
* Function Name  : USART_IRQHandler
* Description    : 
*******************************************************************************/
void NVIC_USART1(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;     
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void NVIC_USART3(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;     
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : USART_IRQHandler
* Description    : 
*******************************************************************************/
USART_BUF  USART1_Buff = {0};
USART_BUF  USART3_Buff = {0};
void USART1_IRQHandler(void)
{
    unsigned char code;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {     
        code=USART_ReceiveData(USART1);
        USART1_Buff.Buff[USART1_Buff.cnt % USART_BUFF_SIZE] = code;
        USART1_Buff.cnt += USART1_Buff.cnt;
    }
}
void USART3_IRQHandler(void)
{
    unsigned char code;
    if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET)
    {     
        code=USART_ReceiveData(USART3);
        USART3_Buff.Buff[USART3_Buff.cnt % USART_BUFF_SIZE] = code;
        USART3_Buff.cnt += USART3_Buff.cnt;
    }
}
/*******************************************************************************
* Function Name  : USART_CHAR
* Description    : 
*******************************************************************************/
u8 Write_Usart1_C(u8 ch)
{
    USART_SendData(USART1, (unsigned char) ch);
    while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);    
    return (ch);
}
u8 Write_Usart3_C(u8 ch)
{
    USART_SendData(USART3, (unsigned char) ch);
    while( USART_GetFlagStatus(USART3,USART_FLAG_TC)!= SET);    
    return (ch);
}
/*******************************************************************************
* Function Name  : USART_STR
* Description    : 
*******************************************************************************/
void Write_Usart1_S(u8 *p)
{
    u16 i;
    for (i = 0; i < USART_BUFF_SIZE; i = i +1 )
	   {
        if (*(p+i) == 0) 
			  {
            Write_Usart1_C('\0');
            break;
        }
        Write_Usart1_C(*(p+i));  
    }
}

void Write_Usart3_S(u8 *p)
{
    u16 i;
    for (i = 0; i < USART_BUFF_SIZE; i = i +1 ){
        if (*(p+i) == 0)
				{
            Write_Usart3_C('\0');
            break;
        }
        Write_Usart3_C(*(p+i));
    }
}
/*******************************************************************************
* Function Name  : USART_STR
* Description    : 
*******************************************************************************/
void Write_Usart1(u8 *p,u16 cnt)
{
    u16 i;
    for (i = 0; i < cnt; i++ )
	  {
        Write_Usart1_C(*(p+i));  
    }
		//Write_Usart1_C('\0');
}

void Write_Usart3(u8 *p,u16 cnt)
{
    u16 i;
    for (i = 0; i < cnt; i++ )
		{
        Write_Usart3_C(*(p+i));
    }
		Write_Usart3_C('\n');
}
