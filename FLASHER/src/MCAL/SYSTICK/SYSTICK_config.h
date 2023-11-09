/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :SYSTICk_config.h
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/

#ifndef MCAL_SYSTICK_SYSTICK_CFG_H_
#define MCAL_SYSTICK_SYSTICK_CFG_H_

#include "SYSTICK_private.h"

//systick clock sources: STK_AHB OR STK_AHB_8
#define STK_CLK_SOURCE   STK_AHB_8

//systick options for interrupt enable: STK_INT_EN STK_INT_DIS
#define STK_INT_OPTION   STK_INT_EN


#endif /* MCAL_SYSTICK_SYSTICK_CFG_H_ */
