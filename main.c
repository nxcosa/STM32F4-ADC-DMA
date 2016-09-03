#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"


//ALIENTEK 探索者STM32F407开发板 实验18
//ADC模数转换实验-库函数版本  
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

__IO uint16_t ADC1ConvertedValue[64][6];
__IO uint32_t ADC1ConvertedVoltage[6];
int main(void)
{ 
	u8 i,j;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();
	Adc_Init();         //初始化ADC
		
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



