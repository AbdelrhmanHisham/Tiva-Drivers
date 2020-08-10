/*
 * UART.H
 *
 *  Created on: Mar 28, 2020
 *      Author: elkarnk
 */



/****
 * Desired baud rate = (sysclock)/((16* clk divisor))
 * default clock is 16 MHZ
 * UART0 : PA0 , PA1 (RX,TX) x
 * UART1 : (PC4,PC5),(PB0,PB1) (RX,TX) x
 * UART2 : PD6 , PD7 (RX,TX)
 * UART3 : PC6 , PC7 (RX,TX)
 * UART4 : PC4 , PC5 (RX,TX) x
 * UART5 : PE4 , PE5 (RX,TX) x
 * UART6 : PD4 , PD5 (RX,TX) x
 * UART7 : PE0 , PE1 (RX,TX) x
 *
 * UART1 : (PC5,PC4),(PF1,PF0)
 */

#ifndef UART_H_
#define UART_H_
#include "Includes.h"
void UARTBEGIN(U8 UARTNUM,U8 PORT, F32 BAUDRATE);
void UARTSendString(U8* c, U8 UARTNUM);
U8* UARTReciveString(U8 UARTNUM);
void UARTSendchar(U8 DATA, U8 UARTNUM);
U8 UARTReciveChar(U8 UARTNUM);
U8 GetUARTValueINTTERUPT(U8 UARTNUM);
void UARTSendInteger(U8 UARTNUM ,U32 NUM);
U32 power(U32 num , U8 p);
U8* str(U32 num);
#endif /* UART_H_ */
