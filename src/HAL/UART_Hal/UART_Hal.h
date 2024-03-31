/*
 * UART_Hal.h
 *
 *  Created on: ???/???/????
 *      Author: Mohamed Elomda
 */
#include "rcc.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#ifndef UART_HAL_H_
#define UART_HAL_H_



void UART_HalInit(UART_Channel Channel);

void UART_HalSendByteAsynch(UART_Channel Channel, u8 Copy_u8Data);

void UART_HalRxBufferAsync(u16 Copy_Buffer , u32 Copy_len , Cb_t Cb );

void UART_HalTxBufferZeroCopy(u16 Copy_Buffer , u32 Copy_len , Cb_t Cb );

void UART_HalCallBackFunction(UART_Channel Channel, UART_enuMode_t Mode, Cb_t Add_CallBackFunction);
#endif /* UART_HAL_H_ */
