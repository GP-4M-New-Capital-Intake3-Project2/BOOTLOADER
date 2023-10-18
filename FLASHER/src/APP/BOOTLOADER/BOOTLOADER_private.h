/*
 * BOOTLOADER_private.h
 *
 *  Created on: ???/???/????
 *      Author: ABDELRHMAN ELSHIKH
 */

#ifndef APP_BOOTLOADER_BOOTLOADER_PRIVATE_H_
#define APP_BOOTLOADER_BOOTLOADER_PRIVATE_H_

//Vector table address
#define SCB_VTOR  *((volatile u32*) (0xE000ED00 + 0x08))
//Startup code offset
#define STARTUP_CODE_OFFSET 0x4



/*
 * set sector 0 for bootloader code
 * set sector 1,2 APP one
 * set sector 3,4 APP two
 * set sector 5 to Bootloader information
 *
 */

//Defining running APP block
#define RUNNING_APP_BLOCK_NUMBER_ADDRESS 0x08020000
/*
 * options
 * NO_APP
 * APP_1
 * APP_2
 *
 */

#define ACTIVE_APP_ADDRESS 0x08020000
#define ACTIVE_APP_END_ADDRESS 0x08023FFFD
#define RUNNING_APP_BLOCK_NUMBER *((volatile u32 *)ACTIVE_APP_ADDRESS)

//address of sector 1 _ APP one
#define APP_1_ADDRESS 0x8004000
//address of sector 2 _ APP two
#define APP_2_ADDRESS 0x800C000



//



#endif /* APP_BOOTLOADER_BOOTLOADER_PRIVATE_H_ */
