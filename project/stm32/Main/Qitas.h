

#ifndef _Qitas_H__
#define _Qitas_H__
#include "stm32f10x.h"



/******************************************************************************
                         store address  
******************************************************************************/
#define	  SN_ADDR  	0x0801E000
#define   ID_ADDR   0x0801E400 
#define   TR_ADDR   0x0801F000 

#define ADC1_Address    ((u32)0x4001244C)
/******************************************************************************
                         Flags 
******************************************************************************/
#define BACK_SUCCESS       0   /*³É¹¦*/
#define BACK_ERROR         1   /*´íÎó*/
#define BACK_TIMEOUT       2   /*³¬Ê±*/

#define WORK_MODE      	0x11   
#define CHECK_MODE      0x12  
#define ADVER_MODE      0x13   

/*******************************************************************************
GPIO MAP£º
*******************************************************************************/
#define   LED_PORT      	GPIOC 
#define   LED_PIN       	GPIO_Pin_13 

#define   DHT11_PORT      	GPIOA 
#define   DHT11_PIN       	GPIO_Pin_1 

#define   DS18B20_PORT      	GPIOA 
#define   DS18B20_PIN    		 GPIO_Pin_0 

#define		IIC_Port 		GPIOB
#define		SCLK_Pin 		GPIO_Pin_7
#define		SDA_Pin     GPIO_Pin_6

#define		I2C_Port 		GPIOB
#define		I2C_SCLK 		GPIO_Pin_8
#define		I2C_SDA     GPIO_Pin_9
/*******************************************************************************
type def£º
*******************************************************************************/
typedef int64_t  s64;
typedef const int64_t sc64;  /*!< Read Only */
typedef __IO int64_t  vs64;
typedef __I int64_t vsc64;   /*!< Read Only */
typedef uint64_t  u64;
typedef const uint64_t uc64;  /*!< Read Only */
typedef __IO uint64_t  vu64;
typedef __I uint64_t vuc64;  /*!< Read Only */
#endif
