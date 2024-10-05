#include "system.h"
#include "SysTick.h"
#include "pwm.h"
#include "oled.h"
#include "time.h"
#include "stdlib.h"
#include "adc.h"
#include "shuju.h"
//#include "usart.h"	
#include "led.h"

#include "math.h"


//#define PI 3.1415926
unsigned int x=0,p=0,z,y;
unsigned int adc_now = 0;  	//ADC采样当前值
int adc_zero = 2048;  // 抬高电平
float adc_average,v_true;		//用于承接累加值，求有效值	
int adc_difference;   //计算差值，作为累加变量
int adc_count = 0;    //采样计数
float adc_sum=0;
int flag = 0;
int DAC_sum=0;
float out_acp_avg=0;
int show_flag = 0;
float error;
float kp=180.0;
/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

int main()
{		

//	float data;
	float v_value;
  unsigned char send_buff[20];

	SysTick_Init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	delay_ms(2000);
	Adc_Init();          //初始化ADC
	OLED_Init(); //OLED初始化	
//	LED_Init();
	//USART1_Init(9600);

	
 	TIM1_PWM_Init();	//频率100kHz，产生SPWM
	TIM3_PWM_Init(500-1,42-1); //频率4Kh，产生PWM
	TIM4_Init(20-1,84-1);  //定时20us	，更新SPWM的比较值和ADC采样

	//TIM_SetCompare1(TIM1,840);//预设SPWM占空比
	//TIM_SetCompare1(TIM3,400);  //预设PWM占空比
	//sprintf(send_buff,"%f",a);
	//OLED_ShowString(0,20,send_buff,16);	
//	OLED_ShowString(0,0,"make by:J&J&T",16);		
//	OLED_Refresh_Gram();  //刷新GRAM数组	
	OLED_ShowString(0,0,"Uo:",16);	
	OLED_ShowString(104,0,"Vac",16);	
	TIM_SetCompare1(TIM3,180);
	while(1)
	{
		/*
			if(flag == 1)
			{
				adc_now = Get_ADC_Value(ADC_Channel_5,1);
				flag = 0;
				if(adc_now>2048)
				adc_now = adc_now - 2048;
				else
				adc_now = 2048 - adc_now;
				data = adc_now*0.00080566;
				adc_sum = data*data + adc_sum;
				adc_count++;
			}
			if(adc_count >= 20000)
			{
				adc_count = 0;
				v_value = sqrt(adc_sum/20000);
				sprintf(send_buff,"%f",v_value);
				OLED_ShowString(0,20,send_buff,16);	
				OLED_Refresh_Gram();  //刷新GRAM数组	
				adc_sum = 0;
				
			}
		*/
		
		
		adc_now = Get_Adc(5); //当前
		out_acp_avg = (out_acp_avg*199 + adc_now)/200;
		
		v_true = (out_acp_avg*0.00975) + 0.27;
		error=30.1-v_true;
		
	  if(p==180)
		{
		kp = kp+error*0.055;
		if(kp>450)
			kp=450;
		if(kp<50)
			kp=50;
//		TIM_SetCompare1(TIM3,(int)kp);
		}
		show_flag++;
		
//		//flag =0;
//		v_true=11.99535*v_value+0.7386;
		if(show_flag > 200)
		{
			show_flag = 0;
		sprintf(send_buff,"%.3f",v_true - 0.1);		
		OLED_ShowString(40,0,send_buff,16);	
		
//		sprintf(send_buff,"%d   %.3f",adc_now,v_value);
//		OLED_ShowString(0,20,send_buff,16);	
//		sprintf(send_buff,"%d",kp);
//		OLED_ShowString(80,40,send_buff,16);				
		OLED_Refresh_Gram();  //刷新GRAM数组		
		}
		delay_ms(1);
				
		
			
	}
}


/*******************************************************************************
* 函 数 名         : TIM4_IRQHandler
* 函数功能		   : TIM4中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update))
	{
//		flag=1;
//		led2=!led2;//DS1翻转
		x=x++;
		if(x>1007)
			x=0;
		TIM_SetCompare1(TIM1,spwm[x]);
	/*	
			x=x++;
		if(x>500)
			x=0;
		y=(int)(504*sin(x*PI/250)+840)/*9;
		TIM_SetCompare1(TIM1,y);	//修改比较值，输出sin的SPWM		
*/
		if((p<180)&&(x==999))//290加负载，180初值
			TIM_SetCompare1(TIM3,p++);  //缓慢增大PWM占空比		
		
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);		

}

