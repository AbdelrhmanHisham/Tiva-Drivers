/*
 * UART.C
 *
 *  Created on: Mar 28, 2020
 *      Author: elkarnk
 */
#include "UART.H"
//#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void UARTBEGIN(U8 UARTNUM, U8 PORT, F32 BAUDRATE)
{
    float SysClk = 16000000.0;
    float clkDiv = (SysClk) / (8.0 * BAUDRATE);

    SetBit(RCGCUART, UARTNUM);  //ENABLE CLOCK TO UART
    SetBit(RCGCGPIO, PORT);  //ENABLE CLOCK TO PORT
    ClearBit(GETREG(BaseUARTAdress,UARTCTL,UARTNUM), 0); //DISABLE UART

    GETREG(BaseUARTAdress,UARTIBRD,UARTNUM) = clkDiv;
    GETREG(BaseUARTAdress,UARTFBRD,UARTNUM) = (((clkDiv - UARTIBRD) * 64.0)
            + 0.5);

    GETREG(BaseUARTAdress,UARTCC,UARTNUM) = 0X0;  //UART CLOCK SAME AS SYSTEM

    SetBit(GETREG(BaseUARTAdress,UARTIM,UARTNUM), 4); //sent to controller
    GETREG(BaseUARTAdress,UARTIFLS,UARTNUM) = 0x20; //value in fifo

    GETREG(BaseUARTAdress,UARTLCRH,UARTNUM) = 0X60; // 1 STOP BIT - NOPARITY - NO INTERRUPT -NO FIFO - 8BIT DATA SIZE
    GETREG(BaseUARTAdress,UARTCTL,UARTNUM) = 0X331; //ENABLE UART
    if ((UARTNUM == UART0) | (UARTNUM == UART1B) | (UARTNUM == UART7))
    {

//        GETREG(BaseGBIOAdress,GPIODEN,PORT) = 0X03; //A0 A1 INPUT
        SetBit(GETREG(BaseGBIOAdress,GPIODEN,PORT), 0);
        SetBit(GETREG(BaseGBIOAdress,GPIODEN,PORT), 1);
//        GETREG(BaseGBIOAdress,GPIOAFSEL,PORT) = 0X03; //AO A1 ALTERNATE FUNCTION
        SetBit(GETREG(BaseGBIOAdress,GPIOAFSEL,PORT), 0);
        SetBit(GETREG(BaseGBIOAdress,GPIOAFSEL,PORT), 1);
//        GETREG(BaseGBIOAdress,GPIOPCTL,PORT) = 0X11; //AO A1 UART
        SetBit(GETREG(BaseGBIOAdress,GPIOPCTL,PORT), 0);
        SetBit(GETREG(BaseGBIOAdress,GPIOPCTL,PORT), 4);
        int x = 0;
        for (x = 0; x < 1000; x++)
            ;
    }
    else if ((UARTNUM == UART1C) | (UARTNUM == UART4) | (UARTNUM == UART5)
            | (UARTNUM == UART6))
    {

//        GETREG(BaseGBIOAdress,GPIODEN,PORT) = 0X30; //A0 A1 INPUT
        SetBit(GETREG(BaseGBIOAdress,GPIODEN,PORT), 4);
        SetBit(GETREG(BaseGBIOAdress,GPIODEN,PORT), 5);
//        GETREG(BaseGBIOAdress,GPIOAFSEL,PORT) = 0X30; //AO A1 ALTERNATE FUNCTION
        SetBit(GETREG(BaseGBIOAdress,GPIOAFSEL,PORT), 4);
        SetBit(GETREG(BaseGBIOAdress,GPIOAFSEL,PORT), 5);
//        GETREG(BaseGBIOAdress,GPIOPCTL,PORT) = 0X110000; //AO A1 UART
        SetBit(GETREG(BaseGBIOAdress,GPIOPCTL,PORT), 16);
        SetBit(GETREG(BaseGBIOAdress,GPIOPCTL,PORT), 20);

        int x = 0;
        for (x = 0; x < 1000; x++)
            ;

    }
    else if ((UARTNUM == UART2) | (UARTNUM == UART3))
    {
//        GETREG(BaseGBIOAdress,GPIODEN,PORT) = 0XC0; //A0 A1 INPUT
        SetBit(GETREG(BaseGBIOAdress,GPIODEN,PORT), 6);
        SetBit(GETREG(BaseGBIOAdress,GPIODEN,PORT), 7);
//        GETREG(BaseGBIOAdress,GPIOAFSEL,PORT) = 0XC0; //AO A1 ALTERNATE FUNCTION
        SetBit(GETREG(BaseGBIOAdress,GPIOAFSEL,PORT), 6);
        SetBit(GETREG(BaseGBIOAdress,GPIOAFSEL,PORT), 7);
//        GETREG(BaseGBIOAdress,GPIOPCTL,PORT) = 0X11000000; //AO A1 UART
        SetBit(GETREG(BaseGBIOAdress,GPIOPCTL,PORT), 24);
        SetBit(GETREG(BaseGBIOAdress,GPIOPCTL,PORT), 28);
        int x = 0;
        for (x = 0; x < 1000; x++)
            ;
    }

}

void UARTSendString(U8* DATA, U8 UARTNUM)
{
    U8 i = 0;
    while (*(DATA + i) != '\0')
    {
        while (((GETREG(BaseUARTAdress, UARTFR, UARTNUM)) & 0x20) != 0)
            ; /* wait until Tx buffer not full */
        GETREG(BaseUARTAdress,UARTDR,UARTNUM) = (*(DATA + i)); /* before giving it another byte */
        i++;
    }

}

U8* UARTReciveString(U8 UARTNUM)
{
    U8 i = 0;
    U8 *DATA;
    U8 recive[20]= "12";
    i = 0;
    while (recive[i] != '\0')
    {
        while ((GETREG(BaseUARTAdress, UARTFR, UARTNUM) & 0x10) != 0)
            ; /* wait until the buffer is not empty */
        (recive[i]) = GETREG(BaseUARTAdress, UARTDR, UARTNUM); /* read the received data */
        i++;

    }
    DATA = recive;
    return DATA; /* and return it */
}

void UARTSendchar(U8 DATA, U8 UARTNUM)
{
    while (((GETREG(BaseUARTAdress, UARTFR, UARTNUM)) & 0x20) != 0)
        ; /* wait until Tx buffer not full */
    GETREG(BaseUARTAdress,UARTDR,UARTNUM) = DATA; /* before giving it another byte */
}
U8 UARTReciveChar(U8 UARTNUM)
{
    U8 DATA;
    while ((GETREG(BaseUARTAdress, UARTFR, UARTNUM) & 0x10) != 0)
        ; /* wait until the buffer is not empty */
    DATA = GETREG(BaseUARTAdress, UARTDR, UARTNUM); /* read the received data */

    return DATA; /* and return it */
}

U8 GetUARTValueINTTERUPT(U8 UARTNUM)
{
    SetBit(GETREG(BaseUARTAdress,UARTICR,UARTNUM), 4); //clear flag
    return GETREG(BaseUARTAdress, UARTDR, UARTNUM); //get value
}

void UARTSendInteger(U8 UARTNUM, U32 NUM)
{
    U8* DATA = str(NUM);
    UARTSendString(DATA, UARTNUM);
}

U8* str(U32 num)
{
    U8 counter = 0;
    U8 out[30];
    U32 buffer = num;
    U8 *retuenvalue;
    while (num != 0)
    {
        num = (num / 10);
        counter++;
    }
    U8 i = counter;
    U8 flag = 0;
    while (counter != 0)
    {

        U8 offset = (i - counter);
        U32 holder = (buffer / power(10, (counter - 1)));
        out[offset] = holder + '0';
        buffer = buffer - ((power(10, (counter - 1))) * holder);
//    printf("buffer :%d\n",buffer);
//    printf("counter:%d\n",counter);
//    printf("data :%c\n",*(out+offset));
        counter--;
        flag = 1;
    }
    if (flag == 0)
    {
        out[0] = '0';
        out[1] = '\0';
    }
    else
    {
        out[i] = '\0';
    }
    retuenvalue = out;
    return retuenvalue;
}

U32 power(U32 num, U8 p)
{
    U32 result = 1;
    U8 n = 0;
    while (p != n)
    {
        result = result * num;
        n++;
    }
    return result;
}
