/*
 * ADC.H
 *
 *  Created on: Mar 29, 2020
 *      Author: elkarnk
 */

#ifndef ADC_H_
#define ADC_H_
#include "Includes.h"
void ADCBEGIN (U8 ADCNUM, U8 ADC_PIN,U8 SampleSquential);
U16 GETADCVALUE(U8 ADCNUM,U8 SampleSquential);
void ClearAdcInterruptFlag(U8 ADCNUM,U8 SampleSquential);


#endif /* ADC_H_ */
