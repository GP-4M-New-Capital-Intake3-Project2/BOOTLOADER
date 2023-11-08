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
u32 CRC_vCrcHWCalculator(u8 * Copy_u8Data , u32 DataSize);

#endif /* MCAL_CRC_CRC_INTERFACE_H_ */
