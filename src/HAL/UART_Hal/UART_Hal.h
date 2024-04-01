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



void UART_HalInit(UART_ConfigType* ConfigPtr);
void UART_HalTxBufferZeroCopy(UART_Buff_t * Copy_UserBuff  );
void UART_HalRxBufferAsync(UART_Buff_t * Copy_UserBuff );
void UART_HalSendByteAsynch(UART_Channel Channel, u8 Copy_u8Data);




UART_ErrorStatus_t UART_CallBackFunction(UART_Channel Channel, UART_enuMode_t Mode, Cb_t Add_CallBackFunction);
#endif /* UART_HAL_H_ */
