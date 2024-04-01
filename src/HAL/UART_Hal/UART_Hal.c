/*
 * UART_Hal.c
 *
 *  Created on: ???/???/????
 *      Author: Mohamed Elomda
 */

#include "UART_Hal.h"
#define UART1_TX  0
#define UART1_RX  1
#define UART2_TX  2
#define UART2_RX  3
#define UART6_TX  4
#define UART6_RX  5
GpioPinCfg_t UART_CH[6]=
{
  [UART1_TX]=
  {
			 .GPIO_Port =  PORT_A,
			 .GPIO_Pin  =  GPIO_PIN_9,
			 .GPIO_Direction =  GPIO_AF_M ,
			 .GPIO_Mode = GPIO_OTYPE_PUSHPULL,
			 .GPIO_Speed = GPIO_SPEED_HIGH ,
			 .GPIO_AF    = GPIO_AFR_AF7
  },
  [UART1_RX]=
  {
		     .GPIO_Port =  PORT_A,
			 .GPIO_Pin  =  GPIO_PIN_10,
			 .GPIO_Direction =  GPIO_AF_M ,
			 .GPIO_Mode =  GPIO_PULL_UP,
			 .GPIO_Speed = GPIO_SPEED_HIGH ,
			 .GPIO_AF    = GPIO_AFR_AF7

  },
  [UART2_TX]=
  {
			 .GPIO_Port =  PORT_A,
			 .GPIO_Pin  =  GPIO_PIN_2,
			 .GPIO_Direction =  GPIO_AF_M ,
			 .GPIO_Mode = GPIO_OTYPE_PUSHPULL,
			 .GPIO_Speed = GPIO_SPEED_HIGH ,
			 .GPIO_AF    = GPIO_AFR_AF7

  },
  [UART2_RX]=
  {
	     .GPIO_Port =  PORT_A,
		 .GPIO_Pin  =  GPIO_PIN_3,
		 .GPIO_Direction =  GPIO_AF_M ,
		 .GPIO_Mode =  GPIO_PULL_UP,
		 .GPIO_Speed = GPIO_SPEED_HIGH ,
		 .GPIO_AF    = GPIO_AFR_AF7

  },
  [UART6_TX]=
  {
			     .GPIO_Port =  PORT_C,
				 .GPIO_Pin  =  GPIO_PIN_6,
				 .GPIO_Direction =  GPIO_AF_M ,
				 .GPIO_Mode = GPIO_OTYPE_PUSHPULL,
				 .GPIO_Speed = GPIO_SPEED_HIGH ,
				 .GPIO_AF    = GPIO_AFR_AF8

  },
  [UART6_RX]=
  {
		     .GPIO_Port =  PORT_C,
			 .GPIO_Pin  =  GPIO_PIN_7,
			 .GPIO_Direction =  GPIO_AF_M ,
			 .GPIO_Mode =  GPIO_PULL_UP,
			 .GPIO_Speed = GPIO_SPEED_HIGH ,
			 .GPIO_AF    = GPIO_AFR_AF8
  }


};
void UART_HalInit(UART_ConfigType* ConfigPtr)
{


  if(ConfigPtr->Channel == UART1)
  {
	 Rcc_SetPeripheralOnOffAhp (GPIO_A , CLK_ON );
	 Rcc_SetPeripheralOnOffAbp(USART1, CLK_ON );
	 GPIO_Init(&UART_CH[UART1_TX]);
     GPIO_Init(&UART_CH[UART1_RX]);
     NVIC_IRQControl(NVIC_USART1_INTERRUPT, IRQ_ENABLE);

  }
  else if (ConfigPtr->Channel== UART2)
  {
	  Rcc_SetPeripheralOnOffAhp(GPIO_A , CLK_ON );
	  Rcc_SetPeripheralOnOffAbp(USART2, CLK_ON );
	  GPIO_Init(&UART_CH[UART2_TX]);
	  GPIO_Init(&UART_CH[UART2_RX]);
	  NVIC_IRQControl(NVIC_USART2_INTERRUPT, IRQ_ENABLE);

  }
  else if (ConfigPtr->Channel == UART6)
  {

	     Rcc_SetPeripheralOnOffAhp(GPIO_C , CLK_ON );
	     Rcc_SetPeripheralOnOffAbp(USART6, CLK_ON );
	     GPIO_Init(&UART_CH[UART6_TX]);
	     GPIO_Init(&UART_CH[UART6_RX]);
	     NVIC_IRQControl(NVIC_USART6_INTERRUPT, IRQ_ENABLE);

  }
  else
  {

  }
  UART_Init(ConfigPtr);
}
void UART_HalSendByteAsynch(UART_Channel Channel, u8 Copy_u8Data)
{
	UART_SendByteAsynch( Channel, Copy_u8Data);
}
void UART_HalRxBufferAsync(UART_Buff_t * Copy_UserBuff )
{
	UART_RxBufferAsync( Copy_UserBuff )	;
}
void UART_HalTxBufferZeroCopy(UART_Buff_t * Copy_UserBuff  )
{
	 UART_TxBufferZeroCopy( Copy_UserBuff );
}
void UART_HalCallBackFunction(UART_Channel Channel, UART_enuMode_t Mode, Cb_t Add_CallBackFunction)
{
	UART_CallBackFunction( Channel,  Mode,  Add_CallBackFunction);
}
