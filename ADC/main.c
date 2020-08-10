#include "GPIO.h"
#include "TIMER.H"
#include "UART.H"
#include "ADC.H"

volatile static U32 adcresult = 0;
void main(void)
{
    PinMode(PORTE, PIN1, INPUT);

    PinMode(LEDPORT, RED, OUTPUT);
    PinMode(LEDPORT, BLUE, OUTPUT);
    PinMode(LEDPORT, GREEN, OUTPUT);
    SetBit(RCGCADC, ADC1);

//    PinMode(PORTA, PIN0, RX);
//    PinMode(PORTA, PIN1, TX);
    UARTBEGIN(UART0, PORTA, 9600);
//ADCBEGIN(ADC0,SS3);

//    SetBit(GETREG(BaseGBIOAdress,GPIOAFSEL,PORTE), PIN1); //ENABLE ALTERNATE FUNCTION
//    ClearBit(GETREG(BaseGBIOAdress,GPIODEN,PORTE), PIN1); //DISABLE DIGITAL ENABLE
//    SetBit(GETREG(BaseGBIOAdress,GPIOAMSEL,PORTE), PIN1); //ENABLE ANALOG FUNCTION

//    UARTSendInteger(UART0, 1);
//    GETREG(BaseTIMERAdress, GPTMTAMR, TIMER0) = 0X2;

//    ClearBit(GETREG(BaseADCAdress,ADCACTSS,ADC1), SS3); //disable SS
//    ClearBit(ADCACTSS, SS3); //disable SS

//    UARTSendInteger(UART0, 2);
//
//    GETREG(BaseADCAdress,ADCEMUX,ADC1) = 0xF000; //start conversion trigger by software default mode
//    UARTSendInteger(UART0, 3);

//    GETREG(BaseADCAdress,ADCSSMUX3,ADC1) = 2; //start conversion trigger by software default mode
//    UARTSendInteger(UART0, 4);

//    SetBit(GETREG(BaseADCAdress,ADCSSCTL3,ADC1), PIN1); //ENABLE ANALOG FUNCTION
//    SetBit(GETREG(BaseADCAdress,ADCSSCTL3,ADC1), PIN2); //ENABLE ANALOG FUNCTION
//
//    SetBit(GETREG(BaseADCAdress,ADCIM,ADC1), SS3); //ENABLE ANALOG FUNCTION
//    SetBit(GETREG(BaseADCAdress,ADCACTSS,ADC1), SS3); //disable SS
//
//    SetBit(GETREG(BaseADCAdress,ADCISC,ADC1), SS3); //CLEAR FLAG
//    SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), 17); //CLEAR SS

    //    SetBit(GETREG(BaseADCAdress,ADCPSSI,ADCNUM), SampleSquential); //enable the conversion for each input cont. conversion

    while (1)
    {
//        if ((adcresult < 1000))
//        {
//            DigitalWrite(LEDPORT, RED, HIGH);
//        }
//        else if ((adcresult > 1000) & (adcresult < 3000))
//        {
//            DigitalWrite(LEDPORT, RED, LOW);
//            DigitalWrite(LEDPORT, GREEN, HIGH);
//        }
//        else if (adcresult > 3000)
//        {
//            DigitalWrite(LEDPORT, GREEN, LOW);
        DigitalWrite(LEDPORT, BLUE, HIGH);
//        }
//        UARTSendInteger(UART0, 5);

    }

}

void adc(void)
{
    DigitalWrite(LEDPORT, RED, HIGH);
    adcresult = GETREG(BaseADCAdress, ADCSSFIFO3, ADC1);
    SetBit(GETREG(BaseADCAdress,ADCISC,ADC1), SS3); //CLEAR FLAG
}
