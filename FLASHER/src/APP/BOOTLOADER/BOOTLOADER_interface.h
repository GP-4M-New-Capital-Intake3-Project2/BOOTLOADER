/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :BOOTLOADER_interface.h
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/

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
/*
 * @name		 APP_vBootloaderInit
 * @brief	initialize bootloader function, 
 *				get the active app bank number,
 * 			erase unuseful area,
 * 			set the address of sector that will receive any updates,
 * 			start a timer to jump to the active app if exist.
 * @param	void
 * @return	void
*/
void APP_vBootloaderInit(void);
/*
 * @name		APP_vBootloaderWrite
 * @brief 	Receive data, check it by CRC, write to flash
 * @param	void
 * @return	void
*/
void APP_vBootloaderWrite(void);
/*
 * @name		APP_vBootloaderJump
 * @brief 	get the active app bank number, \n
 * 			change the address of vector table, \n
 * 			start the app.
 * @param	void
 * @return	void
*/
static void APP_vBootloaderJump(void);
/*
 * @name		APP_vBootloaderGetActiveBank
 * @brief 	know the active app bank depending on number of zero bytes on sector 5
 * @param	void
 * @return	void
*/
static void APP_vBootloaderGetActiveBank(void);
/*
 * @name		APP_u32BootloaderRecordvalidation
 * @brief 	know the active app bank depending on number of zero bytes on sector 5
 * @param	Copy_u8DataBuffer: pointer to the data buffer,
 * 			BufferSize: data size
 * @return	ValidationState : the result of comparing the two CRC codes
*/
static u8 APP_u32BootloaderRecordvalidation(u8 * Copy_u8DataBuffer, u8 BufferSize);



#endif /* APP_BOOTLOADER_BOOTLOADER_INTERFACE_H_ */
