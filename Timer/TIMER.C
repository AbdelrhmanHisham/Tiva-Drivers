/*
 * TIMER.C
 *
 *  Created on: Mar 25, 2020
 *      Author: elkarnk
 */
#include "TIMER.H"

void PeriodicTimerInt(U8 MODE, U8 TimerNum, U8 Timertype, U32 TimerTarget)
{

    if (MODE == NORMAL)
    {
//        //16/32Timer
        SetBit(RCGCTIMER, TimerNum); //ENABLE TIMER N
        ClearBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //disableTn
        GETREG(BaseTIMERAdress, GPTMCFG, TimerNum) = 0X00000000;

        if (Timertype == TA)
        {
            GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum) = 0X2;
            ClearBit(GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum), 4); //COUNT DOWN
            GETREG(BaseTIMERAdress, GPTMTAILR, TimerNum) = TimerTarget; //16000000 1SEC RCC
            SetBit(GETREG(BaseTIMERAdress,GPTMIMR,TimerNum),Timertype); //enable interrupt
            SetBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //ENABLE TAEN
        }
        else
        {
//        GPTMTAMR0 = 0X2;
//        ClearBit(GPTMTAMR0,4);
//        GPTMTAILR0 = TimerTarget;

            GETREG(BaseTIMERAdress, GPTMTBMR, TimerNum) = 0X2;
            ClearBit(GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum), 4); //COUNT DOWN
            GETREG(BaseTIMERAdress, GPTMTAILR, TimerNum) = TimerTarget; //16000000 1SEC RCC
            SetBit(GETREG(BaseTIMERAdress,GPTMIMR,TimerNum),Timertype); //enable interrupt
            SetBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //ENABLE TAEN//        }

        }

    }
    else
    {
        //32/64
        if (TimerNum == WTIMER2)
        {
            SetBit(RCGCWTIMER, WIDETIMER2); //ENABLE TIMER 0

        }
        else if (TimerNum == WTIMER3)
        {
            SetBit(RCGCWTIMER, WIDETIMER3); //ENABLE TIMER 0

        }
        else if (TimerNum == WTIMER4)
        {
            SetBit(RCGCWTIMER, WIDETIMER4); //ENABLE TIMER 0

        }
        else if (TimerNum == WTIMER4)
        {
            SetBit(RCGCWTIMER, WIDETIMER4); //ENABLE TIMER 0

        }
        else if (TimerNum == WTIMER5)
        {
            SetBit(RCGCWTIMER, WIDETIMER5); //EN
        }
        else if (TimerNum == WTIMER1)
        {
            SetBit(RCGCWTIMER, WIDETIMER1); //EN
        }
        else
        {
            SetBit(RCGCWTIMER, WIDETIMER0); //EN
        }
        ClearBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //disableTn
        GETREG(BaseTIMERAdress, GPTMCFG, TimerNum) = 0X00000000;

        if (Timertype == TA)
        {
            GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum) = 0X2;
            ClearBit(GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum), 4); //COUNT DOWN
            GETREG(BaseTIMERAdress, GPTMTAILR, TimerNum) = TimerTarget; //16000000 1SEC RCC
            SetBit(GETREG(BaseTIMERAdress,GPTMIMR,TimerNum),Timertype); //enable interrupt
            SetBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //ENABLE TAEN
        }
        else
        {
            GETREG(BaseTIMERAdress, GPTMTBMR, TimerNum) = 0X2;
            ClearBit(GETREG(BaseTIMERAdress, GPTMTBMR, TimerNum), 4); //COUNT DOWN
            GETREG(BaseTIMERAdress, GPTMTBILR, TimerNum) = TimerTarget; //16000000 1SEC RCC
            SetBit(GETREG(BaseTIMERAdress,GPTMIMR,TimerNum),Timertype); //enable interrupt
            SetBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //ENABLE TAEN

        }
    }

}

void PeriodicTimerDisable(U8 TimerNum, U8 Timertype)
{

    ClearBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //ENABLE TAEN
}
void PeriodicTimerTaskPolling(U8 TimerNum, U8 Timertype, void (*fun_ptr)(void),
                       U8 PERIOD)
{

    static U8 flag =0;
    if (GetBit(GETREG(BaseTIMERAdress,GPTMRIS,TimerNum),Timertype) == 1)
    {
        flag++;
        SetBit(GETREG(BaseTIMERAdress,GPTMICR,TimerNum), Timertype); //ENABLE TAEN
    }

    if (flag == PERIOD)
    {
        (*fun_ptr)();
        PERIOD = 0;
        flag=0;
    }

}


void PeriodicTimerFlagClear(U8 TimerNum, U8 Timertype){

    SetBit(GETREG(BaseTIMERAdress,GPTMICR,TimerNum), Timertype); //ENABLE TAEN
}



void PwmTimerInt(U8 MODE,U8 TimerNum,U8 Timertype){

    if (MODE == NORMAL)
    {
        //16/32Timer
        SetBit(RCGCTIMER, TimerNum); //ENABLE TIMER N
        ClearBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //disableTn
        GETREG(BaseTIMERAdress, GPTMCFG, TimerNum) = 0X00000004;

        if (Timertype == TA)
        {
            GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum) = 0XA; //enable pwm periodic and edge count mode
//            ClearBit(GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum), 4); //COUNT DOWN
//            GETREG(BaseTIMERAdress, GPTMTAILR, TimerNum) = TimerTarget; //16000000 1SEC RCC
//            SetBit(GETREG(BaseTIMERAdress,GPTMIMR,TimerNum),Timertype); //enable interrupt
            ClearBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), 6); //Disable inverted
            SetBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //ENABLE TAEN
        }
        else
        {
//        GPTMTAMR0 = 0X2;
//        ClearBit(GPTMTAMR0,4);
//        GPTMTAILR0 = TimerTarget;

            GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum) = 0XA; //enable pwm periodic and edge count mode
//            ClearBit(GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum), 4); //COUNT DOWN
//            GETREG(BaseTIMERAdress, GPTMTAILR, TimerNum) = TimerTarget; //16000000 1SEC RCC
//            SetBit(GETREG(BaseTIMERAdress,GPTMIMR,TimerNum),Timertype); //enable interrupt
            ClearBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), 14); //Disable inverted
            SetBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //ENABLE TAEN//        }

        }

    }
    else
    {
        //32/64
        if (TimerNum == WTIMER2)
        {
            SetBit(RCGCWTIMER, WIDETIMER2); //ENABLE TIMER 0

        }
        else if (TimerNum == WTIMER3)
        {
            SetBit(RCGCWTIMER, WIDETIMER3); //ENABLE TIMER 0

        }
        else if (TimerNum == WTIMER4)
        {
            SetBit(RCGCWTIMER, WIDETIMER4); //ENABLE TIMER 0

        }
        else if (TimerNum == WTIMER4)
        {
            SetBit(RCGCWTIMER, WIDETIMER4); //ENABLE TIMER 0

        }
        else if (TimerNum == WTIMER5)
        {
            SetBit(RCGCWTIMER, WIDETIMER5); //EN
        }
        else if (TimerNum == WTIMER1)
        {
            SetBit(RCGCWTIMER, WIDETIMER1); //EN
        }
        else
        {
            SetBit(RCGCWTIMER, WIDETIMER0); //EN
        }
        ClearBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //disableTn
        GETREG(BaseTIMERAdress, GPTMCFG, TimerNum) = 0X00000004;

        if (Timertype == TA)
        {
            GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum) = 0XA; //enable pwm periodic and edge count mode
//            ClearBit(GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum), 4); //COUNT DOWN
//            GETREG(BaseTIMERAdress, GPTMTAILR, TimerNum) = TimerTarget; //16000000 1SEC RCC
//            SetBit(GETREG(BaseTIMERAdress,GPTMIMR,TimerNum),Timertype); //enable interrupt
            ClearBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), 6); //Disable inverted
            SetBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //ENABLE TAEN
        }
        else
        {
            GETREG(BaseTIMERAdress, GPTMTAMR, TimerNum) = 0XA; //enable pwm periodic and edge count mode
//            ClearBit(GETREG(BaseTIMERAdress, GPTMTBMR, TimerNum), 4); //COUNT DOWN
//            GETREG(BaseTIMERAdress, GPTMTBILR, TimerNum) = TimerTarget; //16000000 1SEC RCC
//            SetBit(GETREG(BaseTIMERAdress,GPTMIMR,TimerNum),Timertype); //enable interrupt
            ClearBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), 14); //Disable inverted
            SetBit(GETREG(BaseTIMERAdress, GPTMCTL, TimerNum), Timertype); //ENABLE TAEN

        }
    }


}
