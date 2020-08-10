/*
 * GPIO.h
 *
 *  Created on: Mar 23, 2020
 *      Author: elkarnk
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "Includes.h"


void GPIOInt(U8 PORT , U8 PIN);
void PinMode(U8 PORT , U8 PIN , U8 STATE);
void CongifInterupt(U8 PORT , U8 PIN,U8 MODE);
void InterruptISRFlagClear(U8 PORT , U8 PIN);

void InterruptEnable(U8 PORT , U8 PIN,U8 MODE);
void InterruptDisable(U8 PORT , U8 PIN,U8 MODE);

void DigitalWrite(U8 PORT , U8 PIN,U8 VOLTAGE);
void DigitalWritePort(U8 PORT,U32 DATA);

U32 DigitalRead(U8 PORT , U8 PIN);
U32 DigitalReadPort(U8 PORT);

void ReadPin (U8 PORT , U8 PIN,U32 * READING);
void ReadPort (U8 PORT , U8 PIN,U32 * READING);
void DigitalTogle(U8 PORT , U8 PIN);

#endif /* GPIO_H_ */
