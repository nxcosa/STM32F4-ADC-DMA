#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"


//ALIENTEK ̽����STM32F407������ ʵ��18
//ADCģ��ת��ʵ��-�⺯���汾  
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

__IO uint16_t ADC1ConvertedValue[64][6];
__IO uint32_t ADC1ConvertedVoltage[6];
int main(void)
{ 
	u8 i,j;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();
	Adc_Init();         //��ʼ��ADC
		
	while(1)
	{ 
		
		for(i = 0;i<6;i++)
		{
		    ADC1ConvertedVoltage[i] = 0;
    }

        for(i=0;i<6;i++)
        {
            for(j=0;j<64;j++)
            {
                ADC1ConvertedVoltage[i] += ADC1ConvertedValue[j][i];
            }            
            ADC1ConvertedVoltage[i] = ADC1ConvertedVoltage[i]/64;
        }

				if(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)!=RESET)
					{
						for(i = 0;i < 6;i++)
						{
							printf("adc%d=%4.2f  ",i,ADC1ConvertedVoltage[i]*3.3/4096);
						}
			
	      	printf("\n");							
					DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);
					}
			
			LED0=!LED0;
			delay_ms(250);	
	}
}



