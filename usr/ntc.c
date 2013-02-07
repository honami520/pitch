#include "ntc.h"

/*******************************************
NTC 10K 3960 外加4.7K分压电阻对应的AD值
*******************************************/
static uint16_t ntc_base[201] =
{
    3903, 3892, 3881, 3869, 3857, 3844, 3831, 3817,
    3803, 3787, 3772, 3755, 3738, 3721, 3703, 3684,
    3664, 3643, 3622, 3601, 3578, 3555, 3531, 3506,
    3481, 3454, 3427, 3400, 3371, 3342, 3312, 3282,
    3250, 3218, 3185, 3152, 3118, 3083, 3048, 3012,
    2976, 2939, 2901, 2863, 2825, 2786, 2747, 2707,
    2667, 2627, 2586, 2545, 2504, 2463, 2422, 2380,
    2339, 2298, 2256, 2215, 2174, 2132, 2091, 2051,
    2010, 1970, 1929, 1890, 1850, 1811, 1772, 1734,
    1696, 1659, 1622, 1585, 1549, 1514, 1479, 1444,
    1411, 1377, 1344, 1312, 1281, 1250, 1219, 1189,
    1160, 1131, 1103, 1076, 1049, 1022, 996, 971,
    947, 923, 899, 876, 854, 832, 810, 789,
    769, 749, 730, 711, 693, 675, 657, 640,
    624, 608, 592, 577, 562, 547, 533, 519,
    506, 492, 481, 469, 458, 447, 437, 426,
    416, 406, 396, 387, 377, 368, 359, 350,
    342, 334, 325, 317, 309, 302, 294, 287,
    280, 273, 267, 261, 255, 250, 244, 239,
    233, 228, 223, 218, 213, 208, 204, 199,
    195, 190, 186, 182, 178, 174, 170, 166,
    162, 159, 155, 152, 149, 145, 142, 139,
    136, 134, 131, 128, 125, 123, 120, 117,
    115, 113, 110, 108, 106, 103, 101, 99,
    97, 95, 93, 91, 89, 87, 86, 84, 83
};

extern uint16_t adc_dma_buf[5];
extern int8_t ntc_temp;
extern int8_t ntc_now;
extern uint8_t hot_enable;
extern uint8_t sys_mode;
extern uint8_t hot_output;


void ntc_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    DMA_InitTypeDef  DMA_InitStructure;
    ADC_InitTypeDef  ADC_InitStructure;
    
    //开启DMA1，GPIOA的时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1, ENABLE);
    
    //ADC_IN0
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    //DMA传输配置
    DMA_InitStructure.DMA_BufferSize = 5;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_dma_buf;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1, ENABLE);
        
    /* ADC1 configuration ------------------------------------------------------*/
    ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_OneShot);
    
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channels configuration */
    ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_55_5Cycles);
    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);
    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC1);
    ADC_Cmd(ADC1, ENABLE);
    
    /* Wait the ADCEN falg */
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 

    /* ADC1 regular Software Start Conv */ 
    ADC_StartOfConversion(ADC1);
}

/*****************************************
10ms进入一次
*****************************************/
void adc_convert(void)
{
    static uint32_t ntc_sum = 0;
    static uint16_t i = 0;
    uint8_t j;

    ntc_sum += adc_dma_buf[2];
    i ++;
    
    for(j = 0; j < 5; j ++)
    {
        adc_dma_buf[j] = 0;
    }
    
    ADC_StartOfConversion(ADC1);
    
    if(i == 1000)
    {
        i = 0;

        ntc_sum /= 1000;
        
        if(hot_enable == 1)
        {
            if(ntc_sum > 3950)
            {
                //NTC传感器没安装或者故障

            }
            else
            {
                //根据AD值取得温度值
                ntc_temp = ntc_temp_get(ntc_sum);
                ntc_now = ntc_temp;
                //人工调整温度
                ntc_now += NTC_TEMP_DALTA;
            }
        }
        
        //中间量清空
        ntc_sum = 0;
    }
}


int8_t ntc_temp_get(uint16_t adc)
{
    int8_t temp = 0;
    uint8_t i = 0;
    
    while(i < 201)
    {
        if(adc > ntc_base[i])
        {
            temp = i / 2 - 20;
            break;
        }
        i ++;
    }
    
    
    return temp;
}
