#include "adc.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ADC ��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
#define ADC1_DR_ADDRESS    ((uint32_t)0x4001204C)
extern __IO u16 mar[6];
extern __IO uint16_t ADC1ConvertedValue[64][6];

//��ʼ��ADC
void  Adc_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����

	DMA_DeInit(DMA2_Stream0);
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE) {} //�ȴ�DMA������
	/* ���� DMA Stream */
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  //ͨ��ѡ��
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;//DMA�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC1ConvertedValue;//DMA �洢��0��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//�洢��������ģʽ
	DMA_InitStructure.DMA_BufferSize = 384;//���ݴ�����
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݳ���:32λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�洢�����ݳ���:32λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�е����ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);//��ʼ��DMA Stream
	DMA_Cmd(DMA2_Stream0,ENABLE);

	//�ȳ�ʼ��ADC1ͨ��5 IO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ
	ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
	ADC_InitStructure.ADC_NbrOfConversion = 6;
	ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��


	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_144Cycles );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_144Cycles );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_144Cycles );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_144Cycles );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_144Cycles );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_144Cycles );

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);//����ADת����

	ADC_SoftwareStartConv(ADC1);
}












