/*
 * ADC.C
 *
 *  Created on: Mar 29, 2020
 *      Author: elkarnk
 */
#include "ADC.H"

void ADCBEGIN(U8 ADCNUM, U8 ADC_PIN, U8 SampleSquential)
{

//    SetBit(RCGCADC, ADCNUM); //Enable ADC Clock
    RCGCADC |= (1<<ADCNUM);

    ClearBit(GETREG(BaseADCAdress,ADCACTSS,ADCNUM), SampleSquential); //disable SS
    GETREG(BaseADCAdress,ADCEMUX,ADCNUM) = 0xF000; //start conversion trigger by software default mode

    GETREG(BaseADCAdress,ADCSSMUX3,ADCNUM) = ADC_PIN; // CHOOSE ANALOG INPUT PIN

    SetBit(GETREG(BaseADCAdress,ADCSSCTL3,ADCNUM), 1); //MUST SET BEFOR SINGLE SAMPLE SEQUENCER
    SetBit(GETREG(BaseADCAdress,ADCSSCTL3,ADCNUM), 2); //ENABLE INTERRUPT

    SetBit(GETREG(BaseADCAdress,ADCIM,ADCNUM), SampleSquential); //ENABLE INTERRUPT

    SetBit(GETREG(BaseADCAdress,ADCACTSS,ADCNUM), SampleSquential); //ENABLE SS

    SetBit(GETREG(BaseADCAdress,ADCISC,ADCNUM), SampleSquential); //CLEAR FLAG

    if (ADCNUM == ADC0)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), 17); //ENABLE VECTOR
    }
    else if (ADCNUM == ADC1)
    {
        SetBit(GETREG(BaseINTERUPTAdress,EN1,NOOFFSET), 19); //ENABLE VECTOR

    }

}

U16 GETADCVALUE(U8 ADCNUM, U8 SampleSquential)
{
  U16 reading =0;
  reading =GETREG(BaseADCAdress, ADCSSFIFO3, ADCNUM);
return reading;
}



void ClearAdcInterruptFlag(U8 ADCNUM,U8 SampleSquential){
    SetBit(GETREG(BaseADCAdress,ADCISC,ADCNUM), SampleSquential); //CLEAR FLAG

}
