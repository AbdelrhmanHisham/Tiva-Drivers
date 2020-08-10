/*
 * I2C.C
 *
 *  Created on: Apr 6, 2020
 *      Author: elkarnk
 */
#include "I2C.H"
#include "UART.H"

void I2CBegin(U8 MODE, U8 I2CNUM, U32 I2CCLK)
{

    //I2CCLK in bits per second
    U32 SysClk = 16000000;
    SetBit(RCGCI2C, I2CNUM);  //enable i2c clock module
    U8 TPR = (SysClk / (20 * I2CCLK)) - 1;  //get period value
    ClearBit(GETREG(BaseI2CAdress,I2CMTPR,I2CNUM), 7); //disable high speed mode 3.3 mps
    GETREG(BaseI2CAdress,I2CMTPR,I2CNUM) = 7; //set period value
    SetBit(GETREG(BaseI2CAdress,I2CMCR,I2CNUM), MODE);  //Setmode


    if (MODE == SLAVE)
    {
        SetBit(GETREG(BaseI2CAdress,I2CSCSR,I2CNUM), 0); //SLAVE OPERATION  enable
        SetBit(GETREG(BaseI2CAdress,I2CSIMR,I2CNUM), 0); //sent interrupt to controller
    }



    /*****************CONFG PINS**/
    if (I2CNUM == I2C0)
    {
        //****************SCL***************/
        SetBit(GETREG(BaseGBIOAdress, GPIOAFSEL, PORTB), 2);   //PB2
        GETREG(BaseGBIOAdress, GPIOPCTL, PORTB) |= (0x3 << 8);
        /*****************SDA***************/
        SetBit(GETREG(BaseGBIOAdress, GPIOAFSEL, PORTB), 3);   //PB3
        GETREG(BaseGBIOAdress, GPIOPCTL, PORTB) |= (0x3 << 12);

    }
    else if (I2CNUM == I2C1)
    {
        //****************SCL***************/
        SetBit(GETREG(BaseGBIOAdress, GPIOAFSEL, PORTA), 6);   //PA6
        GETREG(BaseGBIOAdress, GPIOPCTL, PORTA) |= (0x3 << 24);
        /*****************SDA***************/
        SetBit(GETREG(BaseGBIOAdress, GPIOAFSEL, PORTA), 7);   //PA7
        GETREG(BaseGBIOAdress, GPIOPCTL, PORTA) |= (0x3 << 28);
    }
    else if (I2CNUM == I2C2)
    {
        //****************SCL***************/
        SetBit(GETREG(BaseGBIOAdress, GPIOAFSEL, PORTE), 4);   //PE4
        GETREG(BaseGBIOAdress, GPIOPCTL, PORTE) |= (0x3 << 16);
        /*****************SDA***************/
        SetBit(GETREG(BaseGBIOAdress, GPIOAFSEL, PORTE), 5);   //PE5
        GETREG(BaseGBIOAdress, GPIOPCTL, PORTE) |= (0x3 << 20);

    }
    else if (I2CNUM == I2C3)
    {
        //****************SCL***************/
        SetBit(GETREG(BaseGBIOAdress, GPIOAFSEL, PORTD), 0);   //PD0
        GETREG(BaseGBIOAdress, GPIOPCTL, PORTD) |= (0x3);
        /*****************SDA***************/
        SetBit(GETREG(BaseGBIOAdress, GPIOAFSEL, PORTD), 1);   //PD1
        GETREG(BaseGBIOAdress, GPIOPCTL, PORTD) |= (0x3 << 4);
    }


}

U8 I2CMASTERSendData(U8 I2CNUM, U8 Data, U8 Slaveaddress)
{

    U8 Error = 0;

    ClearBit(GETREG(BaseI2CAdress,I2CMSA,I2CNUM), 0); //enable write data to slave

    GETREG(BaseI2CAdress,I2CMSA,I2CNUM) = (Slaveaddress << 1); //set the desired address

    GETREG(BaseI2CAdress,I2CMDR,I2CNUM) = Data; //set the desired data to send
    GETREG(BaseI2CAdress,I2CMCS,I2CNUM) = 0x7; //enable master to send data - enable start bit -enable stop bit -disable ack
    while (GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUM),0) != 0)
    {
        UARTSendString("\nBUSY \n", UART0);
    }

    if (GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUM),1) == 0)
    {
        Error = 0;
    }
    else if (GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUM),1) == 1)
    {
        Error = 1;
    }

    return Error;
}

U8 I2CMASTERReciveData(U8 I2CNUM, U8 Slaveaddress)
{
    U8 Data = 0;

    SetBit(GETREG(BaseI2CAdress,I2CMSA,I2CNUM), 0);   //recive data enable

    return Data;
}

void I2CSetSlaveAdress(U8 Adress, U8 I2CNUM)
{

    GETREG(BaseI2CAdress,I2CSOAR,I2CNUM) = Adress; //set the desired address

}

U8 I2CSLAVESendData(U8 I2CNUM, U8 Data, U8 Slaveaddress)
{
    U8 Error = 0;
    SetBit(GETREG(BaseI2CAdress,I2CSCSR,I2CNUM), 0);   //SLAVE OPERATION enable

    return Error;
}
U8 I2CSLAVEReciveData(U8 I2CNUM)
{
    U8 Data;
    while (GetBit(GETREG(BaseI2CAdress,I2CSCSR,I2CNUM),0) != 0)
    {
        UARTSendString("AHHHHHHHHHHHHHH\n", UART0);
    }
    //check RECIVE flag until becomes low

    Data = GETREG(BaseI2CAdress, I2CSDR, I2CNUM);

    return Data;
}

void Printflages(U8 I2CNUMTX, U8 I2CNUMTRX, U8 UARTNUM)
{

    UARTSendString("\n****************MASTER*************  \n", UARTNUM);

    UARTSendString("\nBUSY         : ", UARTNUM);
    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTX), 0));

    UARTSendString("\nERROR        : ", UARTNUM);
    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTX), 1));

    UARTSendString("\nADRESS ACK   : ", UARTNUM);
    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTX), 2));

    UARTSendString("\nDATA ACK     : ", UARTNUM);
    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTX), 3));

//    UARTSendString("\nARBITRATION  : ", UARTNUM);
//    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTX),4));

//    UARTSendString("\nI2C IDEL     : ", UARTNUM);
//    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTX),5));

    UARTSendString("\nBUS          : ", UARTNUM);
    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTX), 6));

//    UARTSendString("\nCLOCK TIMEOUT: ", UARTNUM);
//    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTX),7));

    UARTSendString("\n\n****************SLAVE*************  \n", UARTNUM);

    UARTSendString("\nRECIVE REQUEST     : ", UARTNUM);
    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTRX), 0));

    UARTSendString("\nTRANSMIT REQUEST   : ", UARTNUM);
    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTRX), 1));

    UARTSendString("\nFIRST BYTE RECIVED : ", UARTNUM);
    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTRX), 2));

//    UARTSendString("\nADRES 2 MATCHED    : ", UARTNUM);
//    UARTSendInteger(UART0, GetBit(GETREG(BaseI2CAdress,I2CMCS,I2CNUMTRX),3));

}

void I2CEnableInterrupt(U8 I2CNUM)
{
    if (I2CNUM == I2C0)
    {
        SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), 8); //I2C0

    }
    else if (I2CNUM == I2C1)
    {
        SetBit(GETREG(BaseINTERUPTAdress,EN1,NOOFFSET), 5); //I2C1

    }
    else if (I2CNUM == I2C2)
    {
        SetBit(GETREG(BaseINTERUPTAdress,EN2,NOOFFSET), 4); //I2C2

    }
    else if (I2CNUM == I2C3)
    {
        SetBit(GETREG(BaseINTERUPTAdress,EN2,NOOFFSET), 5); //I2C3

    }
//    SetBit(GETREG(BaseINTERUPTAdress,EN2,NOOFFSET), 4); //I2C2
//    SetBit(GETREG(BaseINTERUPTAdress,EN2,NOOFFSET), 5); //I2C3
//    SetBit(GETREG(BaseINTERUPTAdress,ENO,NOOFFSET), 8); //I2C0
//    SetBit(GETREG(BaseINTERUPTAdress,EN1,NOOFFSET), 5); //I2C1
}

