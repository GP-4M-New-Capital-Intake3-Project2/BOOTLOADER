/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :CRC_program.c
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "CRC_interface.h"
#include "CRC_private.h"

/*
 * reset the crc data register to initial value
 * */
void CRC_vReset(){
	SET_BIT(CRC -> CRC_CR_REG, CRC_RESET_BIT);
}

/*
 * calculate crc
 * if the data less than N*32 bit complete it with dumy '0's
 * */
u32 CRC_vCrcHWCalculator(u8 * Copy_u8Data , u32 DataSize){
	u32 Local_CRCResulr=0;
	u8 Local_u8Counter=0;
	CRC_vReset();

	for (Local_u8Counter =0; Local_u8Counter <= (DataSize+2); Local_u8Counter+=4){
		if(((DataSize +2 )- Local_u8Counter) >=4 ){
			CRC->CRC_DR_REG = (((Copy_u8Data[Local_u8Counter])<<24) | ((Copy_u8Data[(Local_u8Counter+1)])<<16) |((Copy_u8Data[(Local_u8Counter+2)])<<8) | (Copy_u8Data[(Local_u8Counter+3)]));
		}
		else if((((DataSize +2 )- Local_u8Counter)) == 3){
			CRC->CRC_DR_REG = (((Copy_u8Data[Local_u8Counter])<<24) | ((Copy_u8Data[(Local_u8Counter+1)])<<16) |((Copy_u8Data[(Local_u8Counter+2)])<<8) | '0');
		}
		else if(((DataSize +2 )- Local_u8Counter) == 2){
			CRC->CRC_DR_REG = (((Copy_u8Data[Local_u8Counter])<<24) | ((Copy_u8Data[(Local_u8Counter+1)])<<16) |(('0')<<8) | '0');
		}
		else if(((DataSize +2 )- Local_u8Counter) == 1){
			CRC->CRC_DR_REG = (((Copy_u8Data[Local_u8Counter])<<24) |(('0')<<16) | (('0')<<8) | '0');
		}
	}
	Local_CRCResulr = CRC ->CRC_DR_REG;


	return Local_CRCResulr;
}
