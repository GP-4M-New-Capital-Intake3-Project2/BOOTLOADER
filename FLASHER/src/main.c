#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/RCC/RCC_int.h"
#include "MCAL/SYSTICK/SYSTICK_int.h"
#include "MCAL/FMI/FMI_Interface.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/UART/UART_Interface.h"
#include "APP/HEXPARSER/HEXPARSER_int.h"
#include "APP/BOOTLOADER/BOOTLOADER_interface.h"
#include "APP/BOOTLOADER/BOOTLOADER_private.h"

extern MUART_Config_t My_UART;


 //1-FIRST CONFIGURE TX AND RX BITS AS ALTERNATIVE FUNCTIONS
	MGPIO_Config_t Tx_Pin ={
			.Port_ID = GPIO_Port_A, .Pin_ID= GPIO_Pin9, .output_type = Push_pull,
			.output_speed = Low, .mode = Alternative_func, .Alt_func = AF7
	};

	MGPIO_Config_t Rx_Pin ={
			.Port_ID = GPIO_Port_A, .Pin_ID= GPIO_Pin10, .output_type = Push_pull,
			.output_speed = Low, .mode = Alternative_func, .Alt_func = AF7
	};



int main() {
	MRCC_vInit();
	MRCC_vEnableClock(RCC_AHB1, RCC_GPIO_A);
	MRCC_vEnableClock(RCC_APB2, RCC_USART1);
	MSTK_vInit();
	MGPIO_vInit(&Tx_Pin);
	MGPIO_vInit(&Rx_Pin);

	MUART_vInit(&My_UART);
	MUART_vEnable(&My_UART);

	APP_vBootloaderInit();
	APP_vBootloaderWrite();

	while(1){
		asm("NOP");
	}
}
