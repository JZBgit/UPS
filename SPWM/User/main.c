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
unsigned int adc_now = 0;  	//ADC������ǰֵ
int adc_zero = 2048;  // ̧�ߵ�ƽ
float adc_average,v_true;		//���ڳн��ۼ�ֵ������Чֵ	
int adc_difference;   //�����ֵ����Ϊ�ۼӱ���
int adc_count = 0;    //��������
float adc_sum=0;
int flag = 0;
int DAC_sum=0;
float out_acp_avg=0;
int show_flag = 0;
float error;
float kp=180.0;
/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

int main()
{		

//	float data;
	float v_value;
  unsigned char send_buff[20];

	SysTick_Init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	delay_ms(2000);
	Adc_Init();          //��ʼ��ADC
	OLED_Init(); //OLED��ʼ��	
//	LED_Init();
	//USART1_Init(9600);

	
 	TIM1_PWM_Init();	//Ƶ��100kHz������SPWM
	TIM3_PWM_Init(500-1,42-1); //Ƶ��4Kh������PWM
	TIM4_Init(20-1,84-1);  //��ʱ20us	������SPWM�ıȽ�ֵ��ADC����

	//TIM_SetCompare1(TIM1,840);//Ԥ��SPWMռ�ձ�
	//TIM_SetCompare1(TIM3,400);  //Ԥ��PWMռ�ձ�
	//sprintf(send_buff,"%f",a);
	//OLED_ShowString(0,20,send_buff,16);	
//	OLED_ShowString(0,0,"make by:J&J&T",16);		
//	OLED_Refresh_Gram();  //ˢ��GRAM����	
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
				OLED_Refresh_Gram();  //ˢ��GRAM����	
				adc_sum = 0;
				
			}
		*/
		
		
		adc_now = Get_Adc(5); //��ǰ
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
		OLED_Refresh_Gram();  //ˢ��GRAM����		
		}
		delay_ms(1);
				
		
			
	}
}


/*******************************************************************************
* �� �� ��         : TIM4_IRQHandler
* ��������		   : TIM4�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update))
	{
//		flag=1;
//		led2=!led2;//DS1��ת
		x=x++;
		if(x>1007)
			x=0;
		TIM_SetCompare1(TIM1,spwm[x]);
	/*	
			x=x++;
		if(x>500)
			x=0;
		y=(int)(504*sin(x*PI/250)+840)/*9;
		TIM_SetCompare1(TIM1,y);	//�޸ıȽ�ֵ�����sin��SPWM		
*/
		if((p<180)&&(x==999))//290�Ӹ��أ�180��ֵ
			TIM_SetCompare1(TIM3,p++);  //��������PWMռ�ձ�		
		
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);		

}

