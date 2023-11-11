/*
 * CRC_interface.h
 *
 *  Created on: Oct 25, 2023
 *      Author: Abdelrhman Elshikh
 */

#ifndef MCAL_CRC_CRC_INTERFACE_H_
#define MCAL_CRC_CRC_INTERFACE_H_


typedef struct{
	u32 * Data;
	u8 DataSize;
}WordArray_t;

void CRC_init();
void CRC_vReset();
<<<<<<< HEAD
/*
 * @name		CRC_vCrcHWCalculator
 * @brief 	Calculate CRC code base on 32 bit word
 * @param	Copy_u8Data : data record,
 * @param	DataSize : data size
 * @return	Local_CRCResulr : 32 bit CRC code
*/
=======
>>>>>>> parent of f1c74fc (Document source code)
u32 CRC_vCrcHWCalculator(u8 * Copy_u8Data , u32 DataSize);

#endif /* MCAL_CRC_CRC_INTERFACE_H_ */
