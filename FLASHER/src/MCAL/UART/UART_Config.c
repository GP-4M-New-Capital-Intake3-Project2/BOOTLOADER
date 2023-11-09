/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :UART_config.c
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/

#include "UART_Interface.h"

MUART_Config_t My_UART = {
	.UART_ID = UART1,
	.WordLength = UART_8bits, .TransFlow= UART_TxRx, .StopBits = UART_1StopBit,
	.SampleBitMethod = UART_1SampleMethod, .ParitySelect = UART_EvenParity,
	.ParityControl = UART_ParityDisabled, .OverSample = UART_OverSample_8
	,.BaudRate = 9600U
};

