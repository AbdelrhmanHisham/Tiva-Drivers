/*
 * PWM.H
 *
 *  Created on: Apr 2, 2020
 *      Author: elkarnk
 */

#ifndef PWM_H_
#define PWM_H_
#include "Includes.h"
void PWMInt(U8 PWMNum, U8 GENERATORNUM, U8 PWMPIN, U8 MODE ,U32 OutInHZ, U8 DUTYCYCLE);
void PWMWrite(U8 PWMNum, U8 GENERATORNUM,U16 X);

#endif /* PWM_H_ */
