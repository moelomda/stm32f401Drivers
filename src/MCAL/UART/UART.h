/*==========================================================
 * File: UART.h
 * Description: Header file for UART module configuration and functions.
 * Author: [Mohamed Ahmed Fouad ]
 ===========================================================*/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#define UART_CHANNELS    3

// UART Channel options
#define UART_CHANNEL_1   0
#define UART_CHANNEL_2   1
#define UART_CHANNEL_3   2
// Add more UART channels as needed

// Oversampling options
#define UART_OVERSAMPLING_16  0
#define UART_OVERSAMPLING_8   1

// UART Enable options
#define UART_DISABLE   0
#define UART_ENABLE    1

// Word Length options
#define UART_WORD_LENGTH_8    0
#define UART_WORD_LENGTH_9    1

// Parity Control options
#define UART_PARITY_DISABLE   0
#define UART_PARITY_ENABLE    1

// Transmit Data Register Empty Interrupt options
#define UART_TX_EMPTY_INT_DISABLE   0
#define UART_TX_EMPTY_INT_ENABLE    1

// Transmission Complete Interrupt options
#define UART_TX_COMPLETE_INT_DISABLE   0
#define UART_TX_COMPLETE_INT_ENABLE    1

// Receive Data Register Empty Interrupt options
#define UART_RX_EMPTY_INT_DISABLE   0
#define UART_RX_EMPTY_INT_ENABLE    1

// Transmission Enable options
#define UART_TX_DISABLE   0
#define UART_TX_ENABLE    1

// Reception Enable options
#define UART_RX_DISABLE   0
#define UART_RX_ENABLE    1

#define SYS_CLK     16000000
typedef void(*Cb_t)(void);

typedef enum
{
    UART1 = 0,
    UART2,
    UART6
} UART_Channel;

typedef enum
{
    UART_NullPtr,
    UART_InvalidData,
    UART_InvalidChannel,
    UART_Invalid_Mode,
	UART_BUSY,
	UART_Succ
} UART_ErrorStatus_t;

typedef struct
{
    UART_Channel Channel;
    u8 Oversampling;
    u8 UARTEnable;
    u8 WordLength;
    u8 ParityControl;
    u8 TransDateRegisterEmpty_Int;
    u8 TransComplete_Int;
    u8 ReceiveDateRegisterEmpty_Int;
    u8 TransEnable;
    u8 ReceiveEnable;
    u16 BaudRate;
} UART_ConfigType;

typedef struct
{
    u32 *buff;
    u16 len;
} UART_CfgReceiveBuff_t;

typedef struct
{
    u32 *buff;
    u16 len;
} UART_CfgTransBuff_t;

typedef enum
{
   TxMode,
   RxMode,
} UART_enuMode_t;

/*
    Function Name: 	UART_vidInit

    Description: 	Initialize the UART module with the specified configuration.

    Parameters:
        - ConfigPtr: Pointer to the configuration structure containing UART settings.

    Return: Error status indicating success or failure.
*/
UART_ErrorStatus_t UART_vidInit(const UART_ConfigType* ConfigPtr);

/*
    Function Name: 	UART_SendByteAsynchronous

    Description: 	Send a byte of data asynchronously via UART.

    Parameters:
        - Channel: UART channel to use (UART1, UART2, or UART6).
        - Copy_u8Data: Data byte to be sent.

    Return: Error status indicating success or failure.
*/
UART_ErrorStatus_t UART_SendByteAsynchronous(UART_Channel Channel, u8 Copy_u8Data);

/*
    Function Name: 	UART_ReceiveBuffer

    Description: 	Receive data into a buffer via UART.

    Parameters:
        - ReceiveBuffer: Configuration structure containing channel, data buffer address, and buffer size.

    Return: Error status indicating success or failure.
*/
UART_ErrorStatus_t UART_ReceiveBuffer(const UART_CfgReceiveBuff_t* ReceiveBuffer);

/*
    Function Name: 	UART_SendBufferZeroCopy

    Description: 	Send data from a buffer via UART without copying data.

    Parameters:
        - Copy_sConfigBuffer: Configuration structure containing channel, data buffer address, and buffer size.

    Return: Error status indicating success or failure.
*/
UART_ErrorStatus_t UART_SendBufferZeroCopy(const UART_CfgTransBuff_t* Copy_sConfigBuffer);

/*
    Function Name: 	UART_RegisterCallBackFunction

    Description: 	Register a callback function for UART communication events.

    Parameters:
        - Channel: UART channel to use (UART1, UART2, or UART6).
        - Mode: Communication mode (SEND or RECEIVE).
        - Add_CallBackFunction: Pointer to the callback function to be registered.

    Return: Error status indicating success or failure.
*/
UART_ErrorStatus_t UART_CallBackFunction(UART_Channel Channel, UART_enuMode_t Mode, Cb_t Add_CallBackFunction);

#endif /* UART_H_ */
