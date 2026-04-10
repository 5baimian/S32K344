/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : S32K3XX
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file main.c
*
*   @addtogroup main_module main module documentation
*   @{
*/

/* Including necessary configuration files. */
#include "Mcal.h"

volatile int exit_code = 0;
/* User includes */

/*添加两个头文件*/
//引脚物理属性的配置
#include "Siul2_Port_Ip.h"
//引脚逻辑电平的配置
#include "Siul2_Dio_Ip.h"

#include "delay.h"
#include "IntCtrl_Ip.h"
#include "Clock_Ip.h"

/*!
  \brief The main function for tHhe project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
    /* Write your code here */

	uint32 Get_Freq = 0;
	Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
	/* 初始化中断控制器 */
//	IntCtrl_Ip_Init(&IntCtrlConfig_0);
	//在clocks里面设置Clock Ip Get Frequency Api为enabe,否则报错
	Get_Freq = Clock_Ip_GetClockFrequency(CORE_CLK);

//	Get_Freq = 160000000U;
	delay_init(Get_Freq / 1000000); //初始化延迟函数需要核心频率,把读取到的频率传入函数。

	//初始化 SIUL2 模块中所有预先配置好的引脚属性
	Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

	//定义LED的端口以及引脚为数组，用于循环操作
	/* 使用指针数组来存储端口地址 */
	Siul2_Dio_Ip_GpioType * led_ports[] = {led1_red_PORT, led2_blue_PORT, led3_green_PORT, led4_yellow_PORT};
	uint8 led_pins[] = {led1_red_PIN, led2_blue_PIN, led3_green_PIN, led4_yellow_PIN};

	#define LED_COUNT 4

	while(1)
	{
		for(uint8 i = 0; i < LED_COUNT; i++)
		    {
		        /* 1. 点亮当前 LED */
		        /* 假设 0 是点亮（低电平点亮） */
		        Siul2_Dio_Ip_WritePin(led_ports[i], led_pins[i], 0);

		        /* 2. 延迟一段时间 */
		        delay_ms(100);

		        /* 3. 熄灭当前 LED */
		        Siul2_Dio_Ip_WritePin(led_ports[i], led_pins[i], 1);
		    }
	}

    for(;;)
    {
        if(exit_code != 0)
        {
            break;
        }
    }
    return exit_code;
}

/** @} */
