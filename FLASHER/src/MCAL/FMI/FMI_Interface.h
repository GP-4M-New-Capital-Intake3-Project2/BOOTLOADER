/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :FMI_interface.h
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/


#ifndef MCAL_FMI_FMI_INTERFACE_H_
#define MCAL_FMI_FMI_INTERFACE_H_

typedef enum{
	FMI_SEC0 , FMI_SEC1 , FMI_SEC2,
	FMI_SEC3,  FMI_SEC4,  FMI_SEC5
}FMI_SectorNum_t;

typedef enum{
	FMI_Byte, FMI_HalfWord,
	FMI_Word, FMI_DoubleWord
}FMI_PSIZE_t;

typedef struct{
	u32          StartAddress;
	u8*          Data;
	u8          DataSize;
	FMI_PSIZE_t  PSize;
}FMI_WriteOperationData;

/*
 * @name		MFMI_vEraseAppArea
 * @brief 	erase flash from specific sector number  
 * @param	A_u8StartingSector : the number of sector to start erasing
 * @return	void
*/
void MFMI_vEraseAppArea(FMI_SectorNum_t A_u8StartingSector);
/*
 * @name		MFMI_vEraseSector
 * @brief 	erase specific sector from flash  
 * @param	A_u8SectorNum : the number of sector to erase
 * @return	void
*/
void MFMI_vEraseSector(FMI_SectorNum_t A_u8SectorNum);
/*
 * @name		MFMI_vFlashWrite
 * @brief 	write data on the flash memory.  
 * @param	WriteStruct : pointer to struct FMI_WriteOperationData
 * @return	void
*/
void MFMI_vFlashWrite(FMI_WriteOperationData* WriteStruct);


#endif /* MCAL_FMI_FMI_INTERFACE_H_ */
