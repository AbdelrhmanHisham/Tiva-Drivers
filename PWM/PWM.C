/*
 * PWM.C
 *
 *  Created on: Apr 2, 2020
 *      Author: elkarnk
 */
#include "UART.H"
#include "PWM.H"
void PWMInt(U8 PWMNum, U8 GENERATORNUM, U8 PWMPIN, U8 MODE, U32 OutInHZ,
            U8 DUTYCYCLE)
{
    SetBit(RCGCPWM, PWMNum); //enable clock to pwm

    /**********ALTERNATIVE PINS */
    if (PWMNum == PWM0)
    {

        if (PWMPIN == PWMPIN0)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTB) = 0x00000000;
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTB) |= 0x40;   //PB6
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTB) |= 0x0400000;

        }
        else if (PWMPIN == PWMPIN1)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTB) |= 0x80;      //PB7
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTB) |= 0x4000000;

        }
        else if (PWMPIN == PWMPIN2)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTB) |= 0x10;   //PB4
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTB) |= 0x0004000;

        }
        else if (PWMPIN == PWMPIN3)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTB) |= 0x20;   //PB5
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTB) |= 0x00400000;

        }
        else if (PWMPIN == PWMPIN4)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTE) |= 0x10;    //PE4
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTE) |= 0x0040000;

        }
        else if (PWMPIN == PWMPIN5)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTE) |= 0x20;   //PE5
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTE) |= 0x00400000;

        }
        else if (PWMPIN == PWMPIN6)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTD) |= 0x01;        //PD0
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTD) |= 0x00000004;

        }
        else if (PWMPIN == PWMPIN7)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTD) |= 0x02;           //PD1
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTD) |= 0x00000040;

        }

    }
    else if (PWMNum == PWM1)
    {

        if (PWMPIN == PWMPIN0)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTD) |= 0x01;     //PD0
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTD) |= 0x00000005;

        }
        else if (PWMPIN == PWMPIN1)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTD) |= 0x02;     //PD1
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTD) |= 0x00000050;

        }
        else if (PWMPIN == PWMPIN2)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTA) |= 0x40;         ///PA6
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTA) |= 0x05000000;

        }
        else if (PWMPIN == PWMPIN3)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTA) |= 0x80;   ///PA7
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTA) |= 0x50000000;

        }
        else if (PWMPIN == PWMPIN4)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTF) |= 0x01;     //PF0
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTF) |= 0x00000005;

        }
        else if (PWMPIN == PWMPIN5)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTF) |= 0x02;    //PF1
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTF) |= 0x00000050;

        }
        else if (PWMPIN == PWMPIN6)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTF) |= 0x04;       //PF2
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTF) |= 0x00000500;

        }
        else if (PWMPIN == PWMPIN7)
        {
            GETREG(BaseGBIOAdress, GPIOAFSEL, PORTF) |= 0x08;     //PF3
            GETREG(BaseGBIOAdress, GPIOPCTL, PORTF) |= 0x00005000;

        }

    }


    ClearBit(RCC, 20); //NO divisor clock MAIN CLOCK

    //    SetBit(RCC, 20); //enable pwm divisor clock
    //    SetBit(RCC, 17); //deafult clk/64
    //    SetBit(RCC, 18);
    //    SetBit(RCC, 19);

    U16 PWMLOAD = 0;
    U16 PWMCMR = 0;

    if (OutInHZ == 0)
    {
        //nothing to do
    }
    else
    {
        PWMLOAD = 16000000 / OutInHZ;  //MAX = 65535 (245HZ)
        PWMCMR = ((1 - (DUTYCYCLE / 100)) * PWMLOAD);

    }

    if (GENERATORNUM == GEN0)
    {
        if (PWMPIN == PWMPIN1) //PD1
        {
            ClearBit(GETREG(BasePwmAdress,PWM0CTL,PWMNum), 0); //disable counter
            GETREG(BasePwmAdress,PWM0GENB,PWMNum) |= 0X8C;
            GETREG(BasePwmAdress,PWM0LOAD,PWMNum) |= PWMLOAD;
            GETREG(BasePwmAdress,PWM0CMPA,PWMNum) |= PWMCMR;

        }
        else if (PWMPIN == PWMPIN0) //PD0
        {

            ClearBit(GETREG(BasePwmAdress,PWM0CTL,PWMNum), 0); //disable counter
            GETREG(BasePwmAdress,PWM0GENA,PWMNum) |= 0X8C;
            GETREG(BasePwmAdress,PWM0LOAD,PWMNum) |= PWMLOAD;
            GETREG(BasePwmAdress,PWM0CMPA,PWMNum) |= PWMCMR;

        }

        /*******************************************MODE Confg************************************/
        if (MODE == UP_DOWNMODE)
        {
            SetBit(GETREG(BasePwmAdress,PWM0CTL,PWMNum), 1); //COUNT UP/DOWN MODE
        }
        else if (MODE == DOWNMODE)
        {
            ClearBit(GETREG(BasePwmAdress,PWM0CTL,PWMNum), 1); //COUNT DOWN MODE

        }

        /********************************************************************************************/
        SetBit(GETREG(BasePwmAdress,PWM0CTL,PWMNum), 0); //enable counter

    }
    else if (GENERATORNUM == GEN1)
    {
        if (PWMPIN == PWMPIN3)
        {
            ClearBit(GETREG(BasePwmAdress,PWM1CTL,PWMNum), 0); //disable counter
            GETREG(BasePwmAdress,PWM1GENB,PWMNum) |= 0X8C;
            GETREG(BasePwmAdress,PWM1LOAD,PWMNum) |= PWMLOAD;
            GETREG(BasePwmAdress,PWM1CMPA,PWMNum) |= PWMCMR;

        }
        else if (PWMPIN == PWMPIN2)
        {

            ClearBit(GETREG(BasePwmAdress,PWM1CTL,PWMNum), 0); //disable counter
            GETREG(BasePwmAdress,PWM1GENA,PWMNum) |= 0X8C;
            GETREG(BasePwmAdress,PWM1LOAD,PWMNum) |= PWMLOAD;
            GETREG(BasePwmAdress,PWM1CMPA,PWMNum) |= PWMCMR;

        }

        /*******************************************MODE Confg************************************/
        if (MODE == UP_DOWNMODE)
        {
            SetBit(GETREG(BasePwmAdress,PWM1CTL,PWMNum), 1); //COUNT UP/DOWN MODE
        }
        else if (MODE == DOWNMODE)
        {
            ClearBit(GETREG(BasePwmAdress,PWM1CTL,PWMNum), 1); //COUNT DOWN MODE

        }

        /********************************************************************************************/
        SetBit(GETREG(BasePwmAdress,PWM1CTL,PWMNum), 0); //enable counter
    }
    else if (GENERATORNUM == GEN2)
    {
        if (PWMPIN == PWMPIN5)
        {
            ClearBit(GETREG(BasePwmAdress,PWM2CTL,PWMNum), 0); //disable counter
            GETREG(BasePwmAdress,PWM2GENB,PWMNum) |= 0X8C;
            GETREG(BasePwmAdress,PWM2LOAD,PWMNum) |= PWMLOAD;
            GETREG(BasePwmAdress,PWM2CMPA,PWMNum) |= PWMCMR;

        }
        else if (PWMPIN == PWMPIN4)
        {

            ClearBit(GETREG(BasePwmAdress,PWM2CTL,PWMNum), 0); //disable counter
            GETREG(BasePwmAdress,PWM2GENA,PWMNum) |= 0X8C;
            GETREG(BasePwmAdress,PWM2LOAD,PWMNum) |= PWMLOAD;
            GETREG(BasePwmAdress,PWM2CMPA,PWMNum) |= PWMCMR;

        }

        /*******************************************MODE Confg************************************/
        if (MODE == UP_DOWNMODE)
        {
            SetBit(GETREG(BasePwmAdress,PWM2CTL,PWMNum), 1); //COUNT UP/DOWN MODE
        }
        else if (MODE == DOWNMODE)
        {
            ClearBit(GETREG(BasePwmAdress,PWM2CTL,PWMNum), 1); //COUNT DOWN MODE

        }
        /********************************************************************************************/
        SetBit(GETREG(BasePwmAdress,PWM2CTL,PWMNum), 0); //enable counter
    }
    else if (GENERATORNUM == GEN3)
    {
        if (PWMPIN == PWMPIN7)
        {
            ClearBit(GETREG(BasePwmAdress,PWM3CTL,PWMNum), 0); //disable counter
            GETREG(BasePwmAdress,PWM3GENB,PWMNum) |= 0X8C;
            GETREG(BasePwmAdress,PWM3LOAD,PWMNum) |= PWMLOAD;
            GETREG(BasePwmAdress,PWM3CMPA,PWMNum) |= PWMCMR;

        }
        else if (PWMPIN == PWMPIN6)
        {

            ClearBit(GETREG(BasePwmAdress,PWM3CTL,PWMNum), 0); //disable counter
            GETREG(BasePwmAdress,PWM3GENA,PWMNum) |= 0X8C;
            GETREG(BasePwmAdress,PWM3LOAD,PWMNum) |= PWMLOAD;
            GETREG(BasePwmAdress,PWM3CMPA,PWMNum) |= PWMCMR;

        }

        /*******************************************MODE Confg************************************/
        if (MODE == UP_DOWNMODE)
        {
            SetBit(GETREG(BasePwmAdress,PWM3CTL,PWMNum), 1); //COUNT UP/DOWN MODE
        }
        else if (MODE == DOWNMODE)
        {
            ClearBit(GETREG(BasePwmAdress,PWM3CTL,PWMNum), 1); //COUNT DOWN MODE

        }

        /********************************************************************************************/
        SetBit(GETREG(BasePwmAdress,PWM3CTL,PWMNum), 0);  //enable counter
    }

    SetBit(GETREG(BasePwmAdress,PWMENABLE,PWMNum), PWMPIN); //ENABLE PIN

}

void PWMWrite(U8 PWMNum, U8 GENERATORNUM,U16 X) //max 15999
{

    if (X==0)X=1;
    U16 temp = 16000000/1000;

        if (GENERATORNUM == GEN0){
            GETREG(BasePwmAdress,PWM0CMPA,PWMNum) = temp - X;

        }else if (GENERATORNUM == GEN1) {
            GETREG(BasePwmAdress,PWM1CMPA,PWMNum) = temp - X;

        }else if (GENERATORNUM == GEN2) {
            GETREG(BasePwmAdress,PWM2CMPA,PWMNum) = temp - X;

        }else if (GENERATORNUM == GEN3) {
            GETREG(BasePwmAdress,PWM3CMPA,PWMNum) = temp - X;

        }



}
