/*
 * CRC_private.h
 *
 *  Created on: Oct 25, 2023
 *      Author: Abdelrhman Elshikh
 */

#ifndef MCAL_CRC_CRC_PRIVATE_H_
#define MCAL_CRC_CRC_PRIVATE_H_

#define CRC_BASE_ADDRESS 0x40023000

typedef struct{
	u32 CRC_DR_REG;
	u32 CRC_IDR_REG;
	u32 CRC_CR_REG;
}CRC_MemMap_t;



#define CRC_RESET_BIT 0

#define CRC ((volatile CRC_MemMap_t *)CRC_BASE_ADDRESS)




#endif /* MCAL_CRC_CRC_PRIVATE_H_ */
