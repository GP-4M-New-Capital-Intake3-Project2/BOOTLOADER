/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :FMI_private.h
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/


#ifndef MCAL_FMI_FMI_PRV_H_
#define MCAL_FMI_FMI_PRV_H_

#define FLASH_NUM_OF_SECTORS 6

#define FMI_BASE_ADDRESS 0x40023C00

#define FMI_KEY1   0x45670123
#define FMI_KEY2   0xCDEF89AB

//FLASH_SR REGISTER BITS
#define FMI_BSY_BIT   16
#define FMI_EOP_BIT   0

//FLASH_CR REGISTER BITS
#define FMI_LOCK_BIT  31
#define FMI_PG_BIT    0
#define FMI_SER_BIT   1
#define FMI_MER_BIT   2
#define FMI_STRT_BIT  16

typedef struct{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 OPTCR;
}FMI_MemMap_t;

#define FMI   ((volatile FMI_MemMap_t*)(FMI_BASE_ADDRESS))


#endif /* MCAL_FMI_FMI_PRV_H_ */
