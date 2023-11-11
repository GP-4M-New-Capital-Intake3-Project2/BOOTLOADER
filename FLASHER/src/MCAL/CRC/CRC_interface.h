/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :CRC_interface.h
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/


#ifndef MCAL_CRC_CRC_INTERFACE_H_
#define MCAL_CRC_CRC_INTERFACE_H_


typedef struct{
	u32 * Data;
	u8 DataSize;
}WordArray_t;

/*
 * @name		CRC_vReset
 * @brief 	Reset CRC data register to it initial value 0xFFFFFFFF
 * @param	void
 * @return	void
*/
void CRC_vReset();
/*
 * @name		CRC_vCrcHWCalculator
 * @brief 	Calculate CRC code base on 32 bit word
 * @param	Copy_u8Data : data record,
 * @param	DataSize : data size
 * @return	Local_CRCResulr : 32 bit CRC code
*/
u32 CRC_vCrcHWCalculator(u8 * Copy_u8Data , u32 DataSize);

#endif /* MCAL_CRC_CRC_INTERFACE_H_ */
