
#include "servo.h"

/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
void TIM_PWM_Init(u16 arr,u16 psc)  
{    
    GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  
 
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8 | GPIO_Pin_9; 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOB,&GPIO_InitStructure);   
       
    TIM_TimeBaseStructure.TIM_Period = arr; //   50HZ  
    TIM_TimeBaseStructure.TIM_Prescaler =psc;  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
      
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);    
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);    
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  

    TIM_ARRPreloadConfig(TIM4, ENABLE); 
    TIM_CtrlPWMOutputs(TIM4,ENABLE);   
    TIM_Cmd(TIM4, ENABLE);  
}  

/*******************************************************************************
* Function Name  :
* Description    :
*******************************************************************************/
void SERVO(u16 angle)
{
	u8 cnt;
	u16 buff;
	buff=249+(u16)((angle*50)/9);
  TIM_PWM_Init(9999,143);
	//TIM_SetCompare3(TIM4,buff);
	//TIM_SetCompare4(TIM4,buff);
	for(cnt=0;cnt<20;cnt++)
	{
			TIM_SetCompare3(TIM4,buff);
			TIM_SetCompare4(TIM4,buff);
		  Delay_ms(20);	
	}
}

