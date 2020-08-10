/*
 * TIMER.H
 *
 *  Created on: Mar 25, 2020
 *      Author: elkarnk
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "Includes.h"
void PeriodicTimerInt(U8 MODE,U8 TimerNum,U8 Timertype,U32 TimerTarget);
void PeriodicTimerDisable(U8 TimerNum, U8 Timertype);
void PeriodicTimerTaskPolling(U8 TimerNum, U8 Timertype, void (*fun_ptr)(void),U8 PERIOD);
void PeriodicTimerFlagClear(U8 TimerNum, U8 Timertype);
void PwmTimerInt(U8 MODE,U8 TimerNum,U8 Timertype);
#endif /* TIMER_H_ */
