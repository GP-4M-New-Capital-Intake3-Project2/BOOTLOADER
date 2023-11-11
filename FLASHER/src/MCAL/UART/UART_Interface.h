/*
 * NAME :UART_Interface.h
 *
 * Created on: Aug 23, 2023
 *
 * Author: Mo'men Ahmed
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

#include "UART_prv.h"
#include "../../LIB/STD_TYPES.h"

#define UART1_BASE_ADDRESS    0x40011000
#define UART2_BASE_ADDRESS    0x40004400
#define UART6_BASE_ADDRESS    0x40011400

#define UART1   ((volatile UART_MemMap_t*)(UART1_BASE_ADDRESS))
#define UART2   ((volatile UART_MemMap_t*)(UART2_BASE_ADDRESS))
#define UART6   ((volatile UART_MemMap_t*)(UART6_BASE_ADDRESS))

typedef enum{
	UART_OverSample_16 , UART_OverSample_8
}MUART_OverSample_t;

typedef enum{
	UART_8bits, UART_9bits
}MUART_WordLegth_t;

typedef enum{
	UART_ParityDisabled, UART_ParityEnabled
}MUART_ParityCtrl_t;

typedef enum{
	UART_EvenParity, UART_OddParity
}MUART_ParitySelection_t;

typedef enum{
	UART_RxTxDisabled,
	UART_RxOnly,
	UART_TxOnly,
	UART_TxRx
}MUART_TransmissionFlow_t;

typedef enum{
	UART_1StopBit, UART_0_5StopBit,
	UART_2StopBits, UART_1_5StopBits
}MUART_StopBits_t;

typedef enum{
	UART_PEIEDisabled, UART_PEIEEnabled
}MUART_ParityErrorIntEn_t;

typedef enum{
	UART_TXEIEDisabled, UART_TXEIEEnabled
}MUART_TxEmptyIntEn_t;

typedef enum{
	UART_TCIEDisabled, UART_TCIEEnabled
}MUART_TransComplIntEn_t;

typedef enum{
	UART_RXEIEDisabled, UART_RXEIEEnabled
}MUART_RxEmptyIntEn_t;

typedef struct{
	MUART_ParityErrorIntEn_t PEIE;
	MUART_TxEmptyIntEn_t     TXEIE;
	MUART_RxEmptyIntEn_t     RXNEIE;
	MUART_TransComplIntEn_t  TCIE;
}MUART_InterruptEnables_t;

typedef enum{
	UART_3SamplesMethod , UART_1SampleMethod
}MUART_SampleBitMethod_t;

typedef struct{
	UART_MemMap_t *			   UART_ID;
	u32                        BaudRate;
	MUART_OverSample_t         OverSample;
	MUART_WordLegth_t          WordLength;
	MUART_ParityCtrl_t         ParityControl;
	MUART_ParitySelection_t    ParitySelect;
	MUART_TransmissionFlow_t   TransFlow;
	MUART_StopBits_t           StopBits;
	MUART_InterruptEnables_t   IntEnableStruct;
	MUART_SampleBitMethod_t    SampleBitMethod;
}MUART_Config_t;

void MUART_vInit(MUART_Config_t* My_UART);
void MUART_vEnable(MUART_Config_t* My_UART);
void MUART_vDisable(MUART_Config_t* My_UART);

<<<<<<< HEAD
/*
 * @name		MUART_vTransmitByteSynch
 * @brief 	send byte by uart 
 * @param	My_UART : pointer of MUART_Config_t struct 
 * @param	A_u8Byte : byte data to be sent
 * @return	void
*/
=======
>>>>>>> parent of f1c74fc (Document source code)
void MUART_vTransmitByteSynch(MUART_Config_t* My_UART , u8 A_u8Byte);
u8 MUART_vTransmitByteAsynch(MUART_Config_t* My_UART , u8 A_u8Byte);
void MUART_vTransmitString(MUART_Config_t* My_UART , u8* A_ptru8string);

u8 MUART_u8ReceiveByteSynchNonBlocking(MUART_Config_t* My_UART);
void MUART_vReceiveStringSynchNonBlocking(MUART_Config_t* My_UART ,u8 A_u8str[] ,u32 A_u32Size );
u8 MUART_u8ReceiveByteSynchBlocking(MUART_Config_t* My_UART );

void MUART_RxIntSetStatus(MUART_Config_t* My_UART, u8 A_u8Status);
void MUART_voidClearFlags(UART_MemMap_t *USARTx);

u8 MUART_u8ReadDataRegister(MUART_Config_t* My_UART);

//THIS FUNCTION IS DONE FOR BOOTLOADER
u8 MUART_u8ReceiveByteAsych_(MUART_Config_t* My_UART, u8* A_pu8Ptr);

void MUART1_vSetCallBack(void (*ptr) (void) );
void MUART2_vSetCallBack(void (*ptr) (void) );
void MUART6_vSetCallBack(void (*ptr) (void) );




#endif /* MCAL_UART_UART_INTERFACE_H_ */
