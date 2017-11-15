/******************************************
�ļ�����: adc.c
��	  ��: byy
��    ��:
˵    ��: ʵʱʱ������
�޸ļ�¼: 2011-08-18,��������
******************************************/
#include "adc.h"
 
		   


/**********************************************************************
* ��    �ƣ�Adc_Init()
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
***********************************************************************/
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_ADC1 , ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   				// 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			// PB1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	ADC_DeInit(ADC1);  									//������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;		//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת���������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;				//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);					//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	ADC_Cmd(ADC1, ENABLE);								//ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC1);							//����ָ����ADC1��У׼�Ĵ���	 
	while(ADC_GetResetCalibrationStatus(ADC1));			//��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�
	ADC_StartCalibration(ADC1);							//��ʼָ��ADC1��У׼״̬
	while(ADC_GetCalibrationStatus(ADC1));				//��ȡָ��ADC1��У׼����,����״̬��ȴ�
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				//ʹ��ָ����ADC1������ת����������	
}




//���ADCֵ
//ch:ͨ��ֵ 0~3
WORD Get_Adc(BYTE ch)
{
  	// ����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );		  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);			//ʹ��ָ����ADC1������ת����������		 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));	//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);			//�������һ��ADC1�������ת�����
}
