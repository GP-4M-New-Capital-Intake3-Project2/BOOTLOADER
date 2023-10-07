#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/RCC/RCC_int.h"
#include "MCAL/SYSTICK/SYSTICK_int.h"
#include "MCAL/FMI/FMI_Interface.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/UART/UART_Interface.h"
#include "APP/HEXPARSER/HEXPARSER_int.h"

//u16 d[]={0x12,0x56,0x90,0x34};

FMI_WriteOperationData mydata={	.StartAddress = 0x0800C000,
								.DataSize = 1,
								.PSize = FMI_Byte

};


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


u8 resevide_data='0' ;


typedef void (*APP_Call) (void) ;
APP_Call APP = 0 ; /*void (*APP)(void)*/
void APP_vTest(void)
{

	/*Move Vector Table*/
   #define SCB_VTOR  *((volatile u32*) (0xE000ED00 + 0x08))
	SCB_VTOR = 0x800C000;
	/*Set Address to call with Reset Handeler_ISR [startup code of Application]*/
	APP = *(APP_Call*)0x800C004; //startup code for APP
	APP(); //jump Reset handler [startup code]
}





int main() {
	MRCC_vInit();
	MRCC_vEnableClock(RCC_AHB1, RCC_GPIO_A);
	MRCC_vEnableClock(RCC_APB2, RCC_USART1);
	MSTK_vInit();
	MGPIO_vInit(&Tx_Pin);
	MGPIO_vInit(&Rx_Pin);

	MUART_vInit(&My_UART);
	MUART_vEnable(&My_UART);


	u8 d[50]={} ;
	MSTK_vSetIntervalSingle(16000, APP_vTest);
	while(1){
		u8 itr=0;
		while(d[itr-1] != '\n'){
			d[itr] = MUART_u8ReceiveByteSynchBlocking(&My_UART);
			MSTK_vStopTimer();
			MUART_vTransmitByteSynch(&My_UART, 'k');
			itr++;
		}
		if((d[0] == 'E') && (d[1]== 'N') && (d[2] == 'D')){
			APP_vTest();
		}
		else{
		HEXPARESR_vParseRecordAndFlashIt(d);
		MUART_vTransmitByteSynch(&My_UART, 'k');
		}
	}

}
