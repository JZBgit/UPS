#include "pwm.h"

/*******************************************************************************
* �� �� ��         : TIM14_CH1_PWM_Init
* ��������		   : TIM14ͨ��1 PWM��ʼ������
* ��    ��         : per:��װ��ֵ
					 psc:��Ƶϵ��
* ��    ��         : ��
*******************************************************************************/
void TIM3_PWM_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM14ʱ��
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3);//�ܽŸ���
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //�������ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;//�ܽ�����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//�ٶ�Ϊ100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ���ṹ��
	
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure); //����Ƚ�ͨ��1��ʼ��
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable); //ʹ��TIMx�� CCR1 �ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM3,ENABLE);//ʹ��Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��
		
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

TIM_Cmd(TIM1, ENABLE);  //��1?��TIM4
  TIM_CtrlPWMOutputs(TIM1, ENABLE);					  
}  


