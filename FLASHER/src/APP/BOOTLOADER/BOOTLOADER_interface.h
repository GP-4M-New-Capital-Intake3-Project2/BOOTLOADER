/*
 * BOOTLOADER_interface.h
 *
 *  Created on: ???/???/????
 *      Author: ABDELRHMAN ELSHIKH
 */

#ifndef APP_BOOTLOADER_BOOTLOADER_INTERFACE_H_
#define APP_BOOTLOADER_BOOTLOADER_INTERFACE_H_

typedef enum{
	BOOTLOADER_t,
	SECTOR_1_t,
	SECTOR_2_t,
	SECTOR_3_t,
	SECTOR_4_t,
	SYS_INFO_t
}FLASH_t;

//Active App
#define NO_APP 0xFF
#define APP_1 0
#define APP_2 1

//pointer to fun
typedef void (*APP_Call) (void) ;

void APP_vBootloaderInit(void);
void APP_vBootloaderWrite(void);
static void APP_vBootloaderJump(void);
static void APP_vBootloaderGetActiveBank(void);
static u8 APP_u32BootloaderRecordvalidation(u8 * Copy_u8DataBuffer, u8 BufferSize);



#endif /* APP_BOOTLOADER_BOOTLOADER_INTERFACE_H_ */
