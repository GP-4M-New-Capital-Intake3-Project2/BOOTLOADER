/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :SYSTICK_interface.h
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/

#ifndef MCAL_SYSTICK_SYSTICK_INT_H_
#define MCAL_SYSTICK_SYSTICK_INT_H_

#include "SYSTICK_private.h"
#include "../../LIB/STD_TYPES.h"
/*
 * @name		MSTK_vInit
 * @brief 	initialize system timer 
 * @param	void
 * @return	void
*/
void MSTK_vInit(void);


/*
 * @name		MSTK_vDelayms
 * @brief 	halt the processor for a period of time
 * @param	A_u32DelayMilliSec : the time with milli seconds 
 * @return	void
*/
void MSTK_vDelayms(u32 A_u32DelayMilliSec);

/*
 * @name		MSTK_vSetIntervalSingle
 * @brief 	execute function after period of time only once
 * @param	A_u32DelayMilliSec : the time with milli seconds
 * @param   ptr : pointer to function that will be done 
 * @return	void
*/
void MSTK_vSetIntervalSingle(u32 A_u32DelayMilliSec, void (*ptr) (void));


/*
 * @name		MSTK_vSetIntervalSingle
 * @brief 	execute function after period of time repeatedly 
 * @param	A_u32DelayMilliSec : the time with milli seconds
 * @param   ptr : pointer to function that will be done 
 * @return	void
*/
void MSTK_vSetIntervalPeriodic(u32 A_u32DelayMilliSec, void (*ptr) (void));

/*
 * @name		MSTK_vDelayus
 * @brief 	halt the processor for a period of time
 * @param	A_u32DelayMicroSec : the time with micro seconds 
 * @return	void
*/
void MSTK_vDelayus(u32 A_u32DelayMicroSec);

/*
 * @name		MSTK_vSetIntervalSingle
 * @brief 	execute function after period of time only once
 * @param	A_u32DelayMicroSec : the time with micro seconds
 * @param   ptr : pointer to function that will be executed 
 * @return	void
*/
void MSTK_vSetIntervalSingleMicro(u32 A_u32DelayMicroSec, void (*ptr) (void));

/*
 * @name		MSTK_vSetIntervalSingle
 * @brief 	execute function after period of time repeatedly 
 * @param	A_u32DelayMicroSec : the time with micro seconds
 * @param   ptr : pointer to function that will be executed 
 * @return	void
*/
void MSTK_vSetIntervalPeriodicMicro(u32 A_u32DelayMicroSec, void (*ptr) (void));

/*
 * @name		MSTK_u32GetElapsedTime
 * @brief 	get the elapsed time form the register
 * @param	void 
 * @return	L_u32ElapsedTicks : the value of elapsed time
*/
u32 MSTK_u32GetElapsedTime (void);

/*
 * @name		MSTK_u32GetRemainingTime
 * @brief 	get the remaining time form the register subtractor from preloade value
 * @param	void 
 * @return	L_u32RemainingTicks : the value of remaining time
*/
u32 MSTK_u32GetRemainingTime (void);

/*
 * @name		MSTK_vStartTimer
 * @brief 	start the count down of system timer register 
 * @param	A_u32PreloadValue : the number of tick to start the timer
 * @return	void
*/
void MSTK_vStartTimer(u32 A_u32PreloadValue);

/*
 * @name		MSTK_vStopTimer
 * @brief 	stop the count down of the register 
 * @param	void
 * @return	void
*/
void MSTK_vStopTimer(void);

/*
 * @name		MSTK_vSetCallBack
 * @brief 	set the pointer of call back function 
 * @param	copy_ptr : pointer to function that will be executed
 * @return	void
*/
void MSTK_vSetCallBack(void (*copy_ptr)(void));

#endif /* MCAL_SYSTICK_SYSTICK_INT_H_ */
