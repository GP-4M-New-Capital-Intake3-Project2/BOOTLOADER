/*
 * BOOTLOADER_program.c
 *
 *  Created on: ???/???/????
 *      Author: ABDELRHMAN ELSHIKH
 */


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "BOOTLOADER_interface.h"
#include "BOOTLOADER_private.h"
#include "../../MCAL/SYSTICK/SYSTICK_int.h"
#include "../../MCAL/FMI/FMI_Interface.h"
#include "../../MCAL/UART/UART_Interface.h"
#include "../../APP/HEXPARSER/HEXPARSER_int.h"

extern MUART_Config_t My_UART;


FMI_WriteOperationData mydata={	.DataSize = 1,
		.PSize = FMI_Byte

};


APP_Call APP = 0 ; /*void (*APP)(void)*/

FMI_WriteOperationData conf={	.DataSize = 1,
		.PSize = FMI_Byte
};

u8 ActiveBank = NO_APP;


static void APP_vBootloaderGetActiveBank(){
	u8 counter = 0;
	u32 ActiveAppAddress = ACTIVE_APP_ADDRESS;
	while(((*((volatile u32 *)(ActiveAppAddress))) & 0xFF) == 0){
		ActiveBank = counter % 2;
		ActiveAppAddress++;
		counter++;
	}
	//reset flash sector 5
	if(ActiveAppAddress == ACTIVE_APP_END_ADDRESS){
		MFMI_vEraseSector(5);
		conf.Data = 0x0;
		for(u8 cout = 0 ; cout <= ActiveBank ; cout++){
			conf.StartAddress = ACTIVE_APP_ADDRESS+cout;
			MFMI_vFlashWrite(&conf);
		}
	}
}

static void APP_vBootloaderJump(void){
	APP_vBootloaderGetActiveBank();

	if(ActiveBank == APP_1){
		SCB_VTOR = APP_1_ADDRESS;
		/*Set Address to call with Reset Handeler_ISR [startup code of Application]*/
		APP = *(APP_Call*)(APP_1_ADDRESS+STARTUP_CODE_OFFSET); //startup code for APP
	}
	else if(ActiveBank == APP_2){
		SCB_VTOR = APP_2_ADDRESS;
		/*Set Address to call with Reset Handeler_ISR [startup code of Application]*/
		APP = *(APP_Call*)(APP_2_ADDRESS+STARTUP_CODE_OFFSET); //startup code for APP
	}
	if(APP != 0){
		APP(); //jump Reset handler [startup code]
	}
}
void APP_vBootloaderInit(){
	APP_vBootloaderGetActiveBank();
	/*
	 * if there is no code
	 *	  erase sectors 1,2,3,4
	 *	  start write at sector one
	 *    wait to code
	 *
	 * */
	if(ActiveBank == NO_APP){
		conf.StartAddress = APP_1_ADDRESS;
		for(int sec = SECTOR_1_t; sec <= SECTOR_4_t; sec++ ){
			MFMI_vEraseSector(sec);
		}
	}
	/*
	 * if there is an app
	 * clear another app block
	 * start write at first of another block
	 * */
	else if(ActiveBank == APP_1){
		conf.StartAddress = APP_2_ADDRESS;
		MFMI_vEraseSector(SECTOR_3_t);
		MFMI_vEraseSector(SECTOR_4_t);
		MSTK_vSetIntervalSingle(15000, APP_vBootloaderJump);
	}
	else if(ActiveBank == APP_2){
		conf.StartAddress = APP_1_ADDRESS;
		MFMI_vEraseSector(SECTOR_1_t);
		MFMI_vEraseSector(SECTOR_2_t);
		MSTK_vSetIntervalSingle(15000, APP_vBootloaderJump);
	}
}


void APP_vBootloaderWrite(){

	u8 Local_u8itrator=0;
	u8 Locla_u8Buffer[50]={} ;
	//	flag to detect new hex code
	u8 RX_Flag = 1;
	//wait for UART RX Flag
	Locla_u8Buffer[Local_u8itrator] = MUART_u8ReceiveByteSynchBlocking(&My_UART);
	//if received data do not jump to app wait hex code
	MSTK_vStopTimer();
	MUART_vTransmitByteSynch(&My_UART, 'k');
	Local_u8itrator++;
	while(RX_Flag){
		while(Locla_u8Buffer[Local_u8itrator-1] != '\n'){
			MSTK_vSetIntervalSingle(8000, APP_vBootloaderJump);
			Locla_u8Buffer[Local_u8itrator] = MUART_u8ReceiveByteSynchBlocking(&My_UART);
			MSTK_vStopTimer();
			MUART_vTransmitByteSynch(&My_UART, 'k');
			Local_u8itrator++;
		}
		if((Locla_u8Buffer[0] == 'E') && (Locla_u8Buffer[1]== 'N') && (Locla_u8Buffer[2] == 'D')){
			u32 ActiveAppAddress = ACTIVE_APP_ADDRESS;
			while(((*((volatile u32 *)(ActiveAppAddress))) & 0xFF) == 0){
				ActiveAppAddress++;
			}
			conf.StartAddress = ActiveAppAddress;
			conf.Data = 0x0;
			MFMI_vFlashWrite(&conf);
			APP_vBootloaderJump();
			RX_Flag =0;
		}
		else{

			HEXPARESR_vParseRecordAndFlashIt(Locla_u8Buffer);
			MUART_vTransmitByteSynch(&My_UART, 'k');
		}
		Local_u8itrator = 0;
	}
}
