/*
 * I2C.H
 *
 *  Created on: Apr 6, 2020
 *      Author: elkarnk
 */

#ifndef I2C_H_
#define I2C_H_

#include "Includes.h"

void I2CBegin(U8 MODE, U8 I2CNUM, U32 I2CCLK);
U8 I2CMASTERSendData(U8 I2CNUM, U8 Data, U8 Slaveaddress);
U8 I2CMASTERReciveData(U8 I2CNUM, U8 Slaveaddress);

U8 I2CSLAVESendData(U8 I2CNUM, U8 Data, U8 Slaveaddress);
U8 I2CSLAVEReciveData(U8 I2CNUM);
void Printflages(U8 I2CNUMTX, U8 I2CNUMTRX, U8 UARTNUM);
void I2CEnableInterrupt(U8 I2CNUM);

void I2CSetSlaveAdress(U8 Adress, U8 I2CNUM);

#endif /* I2C_H_ */
