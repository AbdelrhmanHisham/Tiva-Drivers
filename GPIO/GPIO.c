#include "GPIO.h"
void GPIOInt(U8 PORT, U8 PIN)
{
    if (PORT == 32)
    {
        SetBit(RCGCGPIO, 4);

    }
    else if (PORT == 33)
    {
        SetBit(RCGCGPIO, 5);
    }
    else
    {
        SetBit(RCGCGPIO, PORT);
    }

    /**********************PROTECTED PINS
     GETREG(BaseGBIOAdress,GPIOLOCK,PORT) = 0x4C4F434B;
     //    SetBit(GETREG(BaseGBIOAdress,GPIOCR,PORT), PIN);
     //    GETREG(BaseGBIOAdress,GPIOPCTL,PORT) = 0x00000000;
     ********ADC & ALTERNATIVEPINS
     //    ClearBit(GETREG(BaseGBIOAdress,GPIOAFSEL,PORT), PIN);
     //    ClearBit(GETREG(BaseGBIOAdress,GPIOAMSEL,PORT), PIN);
     * */
    if ((PORT == PORTD) & (PIN == PIN7) | (PORT == PORTF) & (PIN == PIN0))
    {
        GETREG(BaseGBIOAdress,GPIOLOCK,PORT) = 0x4C4F434B;
        SetBit(GETREG(BaseGBIOAdress,GPIOCR,PORT), PIN);
        GETREG(BaseGBIOAdress,GPIOPCTL,PORT) = 0x00000000;
    }

    SetBit(GETREG(BaseGBIOAdress,GPIODEN,PORT), PIN);

}
void PinMode(U8 PORT, U8 PIN, U8 STATE)
{

    GPIOInt(PORT, PIN);
    if ((STATE == OUTPUT) | (STATE == TX))
    {
        SetBit(GETREG(BaseGBIOAdress,GPIODIR,PORT), PIN);
    }
    else if ((STATE == INPUT) | (STATE == RX))
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIODIR,PORT), PIN);
    }
    else if (STATE == INPUT_PULLUP)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIODIR,PORT), PIN);
        SetBit(GETREG(BaseGBIOAdress,GPIOPUR,PORT), PIN);
    }
    else if (STATE == INPUT_PULLDOWN)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIODIR,PORT), PIN);
        SetBit(GETREG(BaseGBIOAdress,GPIOPDR,PORT), PIN);
    }
    else if (STATE == INPUT_OPENDRAIN | (STATE == SDA))
    {
//        ClearBit(GETREG(BaseGBIOAdress,GPIODIR,PORT), PIN);
        SetBit(GETREG(BaseGBIOAdress,GPIOODR,PORT), PIN);
    }
    else if (STATE == INTERUPT_OPENDRAIN)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIODIR,PORT), PIN);
        SetBit(GETREG(BaseGBIOAdress,GPIOODR,PORT), PIN);
        SetBit(GETREG(BaseGBIOAdress,GPIOIM,PORT), PIN); // enable interrupt sent to controller

    }
    else if (STATE == INTERUPT_PULLDOWN)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIODIR,PORT), PIN);
        SetBit(GETREG(BaseGBIOAdress,GPIOPDR,PORT), PIN);
        SetBit(GETREG(BaseGBIOAdress,GPIOIM,PORT), PIN); // enable interrupt sent to controller

    }
    else if (STATE == INTERUPT_PULLUP)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIODIR,PORT), PIN);
        SetBit(GETREG(BaseGBIOAdress,GPIOPUR,PORT), PIN);
        SetBit(GETREG(BaseGBIOAdress,GPIOIM,PORT), PIN); // enable interrupt sent to controller

    }
    else if (STATE == ANALOG_INPUT)
    {

        SetBit(GETREG(BaseGBIOAdress,GPIOAFSEL,PORT), PIN); //ENABLE ALTERNATE FUNCTION
        ClearBit(GETREG(BaseGBIOAdress,GPIODEN,PORT), PIN); //DISABLE DIGITAL ENABLE
        SetBit(GETREG(BaseGBIOAdress,GPIOAMSEL,PORT), PIN); //ENABLE ANALOG FUNCTION

    }

}

void CongifInterupt(U8 PORT, U8 PIN, U8 MODE)
{
    if (PORT == PORTA)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), PORTA); //enable port F trigger the ISR
    }
    else if (PORT == PORTB)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), PORTB); //enable port F trigger the ISR
    }
    else if (PORT == PORTC)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), PORTC); //enable port F trigger the ISR
    }
    else if (PORT == PORTD)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), PORTD); //enable port F trigger the ISR
    }
    else if (PORT == PORTE)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), 4); //enable port F trigger the ISR
    }
    else if (PORT == PORTF)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), 30); //enable port F trigger the ISR
    }
    /*************************************************************/
    if (MODE == DetectBothedges)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIOIS,PORT), PIN); //edge sesitive
        SetBit(GETREG(BaseGBIOAdress,GPIOIBE,PORT), PIN); //disable bi edge
    }
    else if (MODE == RisingEdge)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIOIS,PORT), PIN); //edge sesitive
        ClearBit(GETREG(BaseGBIOAdress,GPIOIBE,PORT), PIN); //disable bi edge
        SetBit(GETREG(BaseGBIOAdress,GPIOIEV,PORT), PIN); // detect falling edge
    }
    else if (MODE == fallingEdge)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIOIS,PORT), PIN); //edge sesitive
        ClearBit(GETREG(BaseGBIOAdress,GPIOIBE,PORT), PIN); //disable bi edge
        ClearBit(GETREG(BaseGBIOAdress,GPIOIEV,PORT), PIN); // detect falling edge
    }
    else if (MODE == levelSensitive)
    {
        SetBit(GETREG(BaseGBIOAdress,GPIOIS,SWITCHPORT), SW1); //edge sesitive
    }
    /*************************************************/
}

void InterruptEnable(U8 PORT, U8 PIN, U8 MODE)
{
    SetBit(GETREG(BaseGBIOAdress,GPIOIM,PORT), PIN); // enable interrupt sent to controller
    if (PORT == PORTA)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), PORTA); //enable port F trigger the ISR
    }
    else if (PORT == PORTB)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), PORTB); //enable port F trigger the ISR
    }
    else if (PORT == PORTC)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), PORTC); //enable port F trigger the ISR
    }
    else if (PORT == PORTD)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), PORTD); //enable port F trigger the ISR
    }
    else if (PORT == PORTE)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), 4); //enable port F trigger the ISR
    }
    else if (PORT == PORTF)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), 30); //enable port F trigger the ISR
    }

}
void InterruptDisable(U8 PORT, U8 PIN, U8 MODE)
{
    if (MODE == InteruptedPin)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIOIM,PORT), PIN); // enable interrupt sent to controller
    }
    else if (MODE == InteruptedPort)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIOIM,PORT), PIN); // enable interrupt sent to controller
        if (PORT == PORTA)
        {
            SetBit(GETREG(BaseINTERUPTAdress,DIS0,NOOFFSET), PORTA); //enable port F trigger the ISR
        }
        else if (PORT == PORTB)
        {
            SetBit(GETREG(BaseINTERUPTAdress,DIS0,NOOFFSET), PORTB); //enable port F trigger the ISR
        }
        else if (PORT == PORTC)
        {
            SetBit(GETREG(BaseINTERUPTAdress,DIS0,NOOFFSET), PORTC); //enable port F trigger the ISR
        }
        else if (PORT == PORTD)
        {
            SetBit(GETREG(BaseINTERUPTAdress,DIS0,NOOFFSET), PORTD); //enable port F trigger the ISR
        }
        else if (PORT == PORTE)
        {
            SetBit(GETREG(BaseINTERUPTAdress,DIS0,NOOFFSET), 4); //enable port F trigger the ISR
        }
        else if (PORT == PORTF)
        {
            SetBit(GETREG(BaseINTERUPTAdress,DIS0,NOOFFSET), 30); //enable port F trigger the ISR
        }
    }

}

void InterruptISRFlagClear(U8 PORT, U8 PIN)
{
    SetBit(GETREG(BaseGBIOAdress,GPIOICR,PORT), PIN); //clear GPIORIS and GPIOMIS
}

void DigitalWrite(U8 PORT, U8 PIN, U8 VOLTAGE)
{
    if (VOLTAGE == HIGH)
    {
        SetBit(GETREG(BaseGBIOAdress,GPIODATA,PORT), PIN);
    }
    else if (VOLTAGE == LOW)
    {
        ClearBit(GETREG(BaseGBIOAdress,GPIODATA,PORT), PIN);
    }
}
void DigitalWritePort(U8 PORT, U32 DATA)
{
    GETREG(BaseGBIOAdress,GPIODATA,PORT) = DATA;
}
U32 DigitalRead(U8 PORT, U8 PIN)
{
    return GetBit(GETREG(BaseGBIOAdress,GPIODATA,PORT), PIN);
}
U32 DigitalReadPort(U8 PORT)
{
    return GETREG(BaseGBIOAdress, GPIODATA, PORT);
}
void ReadPin(U8 PORT, U8 PIN, U32 * READING)
{

    *READING = GetBit(GETREG(BaseGBIOAdress,GPIODATA,PORT), PIN);
}
void ReadPort(U8 PORT, U8 PIN, U32 * READING)
{

    *READING = GETREG(BaseGBIOAdress, GPIODATA, PORT);
}
void DigitalTogle(U8 PORT, U8 PIN)
{

    ToggleBit(GETREG(BaseGBIOAdress,GPIODATA,PORT), PIN);
}

