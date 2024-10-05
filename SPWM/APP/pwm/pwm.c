#include "pwm.h"

/*******************************************************************************
* 函 数 名         : TIM14_CH1_PWM_Init
* 函数功能		   : TIM14通道1 PWM初始化函数
* 输    入         : per:重装载值
					 psc:分频系数
* 输    出         : 无
*******************************************************************************/
void TIM3_PWM_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM14时钟
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3);//管脚复用
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //复用输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;//管脚设置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度为100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化结构体
	
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure); //输出比较通道1初始化
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable); //使能TIMx在 CCR1 上的预装载寄存器
	TIM_ARRPreloadConfig(TIM3,ENABLE);//使能预装载寄存器
	
	TIM_Cmd(TIM3,ENABLE); //使能定时器
		
}

void TIM1_PWM_Init(void)
{		 					 
GPIO_InitTypeDef GPIO_InitStructure;   
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
TIM_OCInitTypeDef  TIM_OCInitStructure;     

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  

GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); 

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;   
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
GPIO_Init(GPIOA,&GPIO_InitStructure);             

TIM_TimeBaseStructure.TIM_Prescaler=1-1;  
TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
TIM_TimeBaseStructure.TIM_Period=1680-1;   
TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);

TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 

//TIM_OCInitStructure.TIM_Pulse = CCR1_Val;// channel 1
TIM_OC1Init(TIM1, &TIM_OCInitStructure);  
TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
 
TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;

  TIM_ARRPreloadConfig(TIM1,ENABLE);

TIM_Cmd(TIM1, ENABLE);  //ê1?üTIM4
  TIM_CtrlPWMOutputs(TIM1, ENABLE);					  
}  


