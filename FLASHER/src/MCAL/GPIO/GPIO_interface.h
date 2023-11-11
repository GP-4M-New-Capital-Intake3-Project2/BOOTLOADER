/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :GPIO_interface.h
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/

#ifndef MCAL_GPIO_GPIO_INT_H_
#define MCAL_GPIO_GPIO_INT_H_


#include "GPIO_private.h"

typedef enum{
	GPIO_Port_A, GPIO_Port_B, GPIO_Port_C
}GPIO_PortNum_t;

typedef enum{
	GPIO_Pin0, GPIO_Pin1, GPIO_Pin2 ,GPIO_Pin3,
	GPIO_Pin4, GPIO_Pin5, GPIO_Pin6 ,GPIO_Pin7,
	GPIO_Pin8, GPIO_Pin9, GPIO_Pin10,GPIO_Pin11,
	GPIO_Pin12,GPIO_Pin13,GPIO_Pin14,GPIO_Pin15
}GPIO_PinNum_t;

typedef struct{
	GPIO_PortNum_t Port_ID;
	GPIO_PinNum_t  Pin_ID;
	GPIO_Mode_t mode;
	GPIO_OutType_t output_type;
	GPIO_OutSpeed_t output_speed;
	GPIO_InputPullType_t input_pull_type;
	GPIO_AlternativeFunctions_t Alt_func;
}MGPIO_Config_t;


/*
 * @name		MGPIO_vInit
 * @brief 	Iniztalize GPIO pin function  
 * @param	Copy_Config_Struct : pointer of MGPIO_Config_t struct
 * @return	void
*/
void MGPIO_vInit(MGPIO_Config_t* copy_Config_Struct);

/*
 * @name		MGPIO_vSetPin
 * @brief 	Write a value on a pin  
 * @param	copy_Port_ID : GPIO port,
 * @param	copy_Pin_ID : GPIO pin number
 * @param	copy_Pin_value : the value to be written (HIGH or LOW)
 * @return	void
*/
void MGPIO_vSetPin(GPIO_PortNum_t copy_Port_ID, GPIO_PinNum_t copy_Pin_ID, GPIO_PinValues_t copy_Pin_value );
/*
 * @name		MGPIO_vSetPinFast
 * @brief 	Write a value on a pin with atomic access 
 * @param	copy_Port_ID : GPIO port,
 * @param	copy_Pin_ID : GPIO pin number
 * @param	copy_Pin_value : the value to be written (HIGH or LOW)
 * @return	void
*/
void MGPIO_vSetPinFast(GPIO_PortNum_t copy_Port_ID, GPIO_PinNum_t copy_Pin_ID,GPIO_PinValues_t copy_Pin_value );

/*
 * @name		MGPIO_vTogPin
 * @brief 	Toggle the value on a pin  
 * @param	copy_Port_ID : GPIO port,
 * @param	copy_Pin_ID : GPIO pin number
 * @return	void
*/
void MGPIO_vTogPin (GPIO_PortNum_t copy_Port_ID, GPIO_PinNum_t copy_Pin_ID);

/*
 * @name		MGPIO_u8GetPin
 * @brief 	read the value from a pin  
 * @param	copy_Port_ID : GPIO port,
 * @param	copy_Pin_ID : GPIO pin number
 * @return	pin_value : pin state
*/
u8 MGPIO_u8GetPin(GPIO_PortNum_t copy_Port_ID, GPIO_PinNum_t copy_Pin_ID );



#endif /* MCAL_GPIO_GPIO_INT_H_ */
