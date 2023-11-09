/************************************************************************
 * Author           :Abdelrhman Elshikh
 * File description :BIT_MATH.h
 * Date             :20/10/2023
 * Target           :STM32F401
 * Version          :v0.1
 ************************************************************************/


#ifndef BIT_CALC_H
#define BIT_CALC_H 

#define SET_BIT(var, bit_no)      ((var) |=  (1 << (bit_no)))

#define CLR_BIT(var, bit_no)      ((var) &= ~(1 << (bit_no)))

#define TOG_BIT(var, bit_no)      ((var) ^=  (1 << (bit_no)))

#define GET_BIT(var, bit_no)     ((((var) >> (bit_no)) & 0x01))

#endif			

