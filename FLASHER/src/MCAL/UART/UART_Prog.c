/*
 * NAME :UART_Prog.c
 *
 * Created on: Aug 23, 2023
 *
 * Author: Mo'men Ahmed
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "UART_Interface.h"
#include "UART_Config.h"
#include "UART_prv.h"

#include "../GPIO/GPIO_int.h"

void (*MUART1_CallBackPtr)(void)=NULL;
void (*MUART2_CallBackPtr)(void)=NULL;
void (*MUART6_CallBackPtr)(void)=NULL;


void MUART_vInit(MUART_Config_t* My_UART)
{
// //1-FIRST CONFIGURE TX AND RX BITS AS ALTERNATIVE FUNCTIONS
//	MGPIO_Config_t Tx_Pin ={
//			.Port_ID = GPIO_Port_A, .Pin_ID= GPIO_Pin9, .output_type = Push_pull,
//			.output_speed = High, .mode = Alternative_func, .Alt_func = AF7
//	};
//
//	MGPIO_Config_t Rx_Pin ={
//			.Port_ID = GPIO_Port_A, .Pin_ID= GPIO_Pin10, .output_type = Push_pull,
//			.output_speed = High, .mode = Alternative_func, .Alt_func = AF7
//	};
//
//	MGPIO_vInit(&Tx_Pin);
//	MGPIO_vInit(&Rx_Pin);

	//2- SET BAUDE RATE BY MACRO
	switch (My_UART -> OverSample)
	{
	case UART_OverSample_8:
		My_UART ->UART_ID->BRR = UART_BRR_SAMPLING8(8000000, (My_UART -> BaudRate));
		break;
	case UART_OverSample_16:
		My_UART ->UART_ID->BRR = UART_BRR_SAMPLING16(8000000, (My_UART -> BaudRate));
		break;
	}

	//3-SET THE REMAINING OPTIONS:
	My_UART ->UART_ID -> CR[0] = ((My_UART->OverSample<<UART_OVER8_BIT)    |
			          (My_UART->WordLength<< UART_M_BIT)       |
					  (My_UART->ParityControl << UART_PCE_BIT) |
					  (My_UART->ParitySelect << UART_PS_BIT)   |
					  (My_UART->IntEnableStruct.TXEIE << UART_TXEIE_BIT) | (My_UART->IntEnableStruct.TCIE << UART_TCIE_BIT)|
					  (My_UART->IntEnableStruct.PEIE << UART_PEIE_BIT)	| (My_UART->IntEnableStruct.RXNEIE << UART_RXNEIE_BIT)|
					  (My_UART->TransFlow <<  UART_RE_BIT));

	My_UART ->UART_ID -> CR[1] |= (My_UART->StopBits << UART_STOP0_BIT) ;

	My_UART ->UART_ID -> CR[2] |= (My_UART->SampleBitMethod << UART_ONEBIT_BIT);

	MUART_voidClearFlags(My_UART ->UART_ID);
	MUART_vEnable(My_UART ->UART_ID);
}

void MUART_vEnable(MUART_Config_t* My_UART)
{
	SET_BIT(My_UART ->UART_ID -> CR[0] , UART_UE_BIT);
	SET_BIT(My_UART ->UART_ID -> CR[1] , UART_TE_BIT);
}

void MUART_vDisable(MUART_Config_t* My_UART)
{
	CLR_BIT(My_UART ->UART_ID -> CR[0] , UART_UE_BIT);
}

void MUART_vTransmitByteSynch(MUART_Config_t* My_UART , u8 A_u8Byte)
{
	//1-FIRST CHECK THAT TRANSMIT REGISTER IS EMPTY
	while(GET_BIT(My_UART ->UART_ID -> SR , UART_TXE_BIT) == 0){
		asm("NOP");
	}
	//2-PUT THE DATA IN THE SATA REGISTER
    if(A_u8Byte == '\n')
    {
    	My_UART ->UART_ID->DR = 10;
    }
    else{
	(My_UART ->UART_ID->DR) = A_u8Byte;
    }
	//3-WAIT UNTIL TRASNMISSION IS COMPLETE
	while(GET_BIT(My_UART ->UART_ID -> SR , UART_TC_BIT) == 0)
	{
		asm("NOP");
	}
	//4-SEQUENCE TO CLEAR THE TC FLAG
//	u8 Local_u8 = My_UART ->UART_ID -> SR; // READ SR REGISTER
//	My_UART ->UART_ID -> DR = 0;           //WRITE INTO DR
	//OR

	 CLR_BIT(My_UART ->UART_ID -> SR , UART_TC_BIT);
}


u8 MUART_vTransmitByteAsynch(MUART_Config_t* My_UART , u8 A_u8Byte)
{
	if(GET_BIT(My_UART ->UART_ID -> SR , UART_TXE_BIT) == 1)
	{
		My_UART ->UART_ID -> DR = A_u8Byte;
       return UART_SUCCESS;
	}
	else
	{
		return UART_FAIL;
	}
}

void MUART_vTransmitString(MUART_Config_t* My_UART , u8* A_ptru8string)
{
	u8 iterator = 0;
	while(A_ptru8string[iterator] != '\0')
	{
		MUART_vTransmitByteSynch(My_UART ->UART_ID, A_ptru8string[iterator]);
		iterator++;
	}
}

u8 MUART_u8ReceiveByteSynchNonBlocking(MUART_Config_t* My_UART)
{
 u32 timeout = 0;
 u8 ReceivedByte;
	while(GET_BIT(My_UART ->UART_ID -> SR , UART_RXNE_BIT) == 0  || timeout < THRESHOLD_VALUE)
	{
		timeout ++;
	}
	//AFTER THIS LOOP, WHETHER UART RECEIVES A BYTE OR TIMEOUT FINISHES
	if(timeout == THRESHOLD_VALUE)
	{
		ReceivedByte = 255;            //255 IS NOT A VALID ASCII NUMBER
	}
	else
	{
		ReceivedByte = My_UART ->UART_ID -> DR;
	}
	return ReceivedByte;
}

void MUART_vReceiveStringSynchNonBlocking(MUART_Config_t* My_UART ,u8 A_u8str[] ,u32 A_u32Size )
{
	u32 i = 0;
	for (; i<A_u32Size ;i++)
	{
		A_u8str[i] = MUSART_u8ReceiveByteSynchNonBlocking(My_UART ->UART_ID);
		if(A_u8str[i]== 255 )  //TIMEOUT
		{
//			A_u8str[i] = '\0';
			break;
		}
	}

A_u8str[i-1] = '\0';
}

u8 MUART_u8ReceiveByteSynchBlocking(MUART_Config_t* My_UART )
{
	while(GET_BIT(My_UART ->UART_ID -> SR , UART_RXNE_BIT) == 0)
	{
		//DATA HAS NOT BEEN RECEIVED YET
		asm("NOP");
	}

	return My_UART ->UART_ID->DR;
}


void MUART_voidClearFlags(UART_MemMap_t *UARTx)
{
	UARTx -> SR = 0;
}

u8 MUART_u8ReadDataRegister(MUART_Config_t* My_UART)
{
	return My_UART ->UART_ID -> DR;
}

void MUART1_vSetCallBack(void (*ptr) (void) )
{
	ptr = MUART1_CallBackPtr;
}

void MUART2_vSetCallBack(void (*ptr) (void) )
{
	ptr = MUART2_CallBackPtr;
}

void MUART6_vSetCallBack(void (*ptr) (void) )
{
	ptr = MUART6_CallBackPtr;
}

void USART1_IRQHandler(void)
{
	MUART_voidClearFlags(UART1);
	if(MUART1_CallBackPtr != NULL)
	{
		MUART1_CallBackPtr();
	}
}

void USART2_IRQHandler(void)
{
	MUART_voidClearFlags(UART2);
	if(MUART2_CallBackPtr != NULL)
	{
		MUART2_CallBackPtr();
	}
}

void USART6_IRQHandler(void)
{
	MUART_voidClearFlags(UART6);
	if(MUART6_CallBackPtr != NULL)
	{
		MUART6_CallBackPtr();
	}
}

u8 MUART_u8ReceiveByteAsych_(MUART_Config_t* My_UART, u8* A_pu8Ptr)
{
	u8 ReceiveStatus = 0;

	if(GET_BIT(My_UART ->UART_ID -> SR , UART_RXNE_BIT) == 0)
	{
		//DATA HAS NOT BEEN RECEIVED YET
	}
	else
	{
		// UART HAS RECEIVED A BYTE
		ReceiveStatus = 1;
		*A_pu8Ptr = My_UART ->UART_ID -> DR;
	}

   return ReceiveStatus;
}


