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

/*
 * to know the active app bank
 * go to sector 5
 * read how many bytes equal zero
 * take the reminder by 2
 * if the sector 5 reach the end
 * save the number in ram
 * erase sector 5
 * write it again
 * */
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

/* fetch the crc from received data
 * calculate crc for useful data
 * compare them
 * */
static u8 APP_u32BootloaderRecordvalidation(u8 * Copy_u8DataBuffer, u8 BufferSize){
	u32 Local_u32CrcCalculated=0;
	u32 Local_u32CrcFetched=0;
	u8 Local_u8ValidationState = 0;
	u8 Local_u8Iterator=0;
	u8 Local_u8ParsedValue=0;
	//fetch CRC form record "buffer -8:crc -1:'\n' -1:' '"
	for(Local_u8Iterator = BufferSize-9; Local_u8Iterator < BufferSize-1; Local_u8Iterator++ ){
		Local_u8ParsedValue = HEXPARSER_su8AsciiToHex(Copy_u8DataBuffer[Local_u8Iterator]);

		Local_u32CrcFetched = (Local_u32CrcFetched <<4)|Local_u8ParsedValue;
	}

	// calculate CRC for data only "buffer -8:crc -1:'\n' -1:' '"
	Local_u32CrcCalculated =  CRC_vCrcHWCalculator(Copy_u8DataBuffer, BufferSize - 11);
	if(Local_u32CrcCalculated == Local_u32CrcFetched){
		Local_u8ValidationState = 1;
	}
	return Local_u8ValidationState;
}

/*
 * get the active app bank number
 * change the address of vector table
 * start the app
 * */
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

/*
 * get the active app bank number
 * erase unuseful area
 * set the address of sector that will receive any updates
 * start a timer to jump to the active app if exist
 * */
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

/*
 * Receive data from uart until '\n'
 * check the data
 * if the crc is correct send 'k' for confirmation
 * if not send 'E' to ask for this record again
 * if the data buffer equal 'END' jump to the new app
 * if you do not able to receive any data for 8 seconds jump on the active app
 * */
void APP_vBootloaderWrite(){

	u8 Local_u8itrator=0;
	u8 Locla_u8Buffer[50]={} ;
	u8 Local_u8RecordValidation = 0;
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
			Local_u8RecordValidation =  APP_u32BootloaderRecordvalidation(Locla_u8Buffer, Local_u8itrator);
			if(Local_u8RecordValidation == 1){
				HEXPARESR_vParseRecordAndFlashIt(Locla_u8Buffer);
				MUART_vTransmitByteSynch(&My_UART, 'k');
			}else{
				MUART_vTransmitByteSynch(&My_UART, 'E');
			}
		}
		Local_u8itrator = 0;
		Local_u8RecordValidation =0;
	}
}
