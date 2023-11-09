/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :HEXPARSER_interface.h
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/


#ifndef APP_HEXPARSER_HEXPARSER_INT_H_
#define APP_HEXPARSER_HEXPARSER_INT_H_


/*
 * @name		HEXPARSER_su8AsciiToHex
 * @brief 	Convert the recoed format form Ascii code to Hexadisimal 
 * @param	A_u8Ascii: chatacter as ascii,
 * @return	L_u8ReturnHex : Hexadisimal Byte
*/
u8 HEXPARSER_su8AsciiToHex(u8 A_u8Ascii);

/*
 * @name		HEXPARESR_vParseRecordAndFlashIt
 * @brief 	Convert data record form Ascii code to Hexadisimal, and wirte it on flash 
 * @param	A_pu8Record: data recoed as ascii
 * @return	void
*/
void HEXPARESR_vParseRecordAndFlashIt(u8* A_pu8Record);


#endif /* APP_HEXPARSER_HEXPARSER_INT_H_ */
