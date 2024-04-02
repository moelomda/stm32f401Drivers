/*==========================================================
 * File: UART.c
 * Author: [Mohamed Ahmed Fouad ]
 ===========================================================*/
#include "UART.h"
#define UART1_BASE_ADDRESS             0x40011000
#define UART2_BASE_ADDRESS             0x40004400
#define UART6_BASE_ADDRESS             0x40011400

#define UART_CHANNELS    3
#define NULL  0
// Bit positions for USART control register (USART_CR1)
#define UART_CR1_OVER8_Pos          15
#define UART_CR1_UE_Pos             13
#define UART_CR1_M_Pos              12
#define UART_CR1_WAKE_Pos           11
#define UART_CR1_PCE_Pos            10
#define UART_CR1_PS_Pos             9
#define UART_CR1_PEIE_Pos           8
#define UART_CR1_TXEIE_Pos          7
#define UART_CR1_TCIE_Pos           6
#define UART_CR1_RXNEIE_Pos         5
#define UART_CR1_IDLEIE_Pos         4
#define UART_CR1_TE_Pos             3
#define UART_CR1_RE_Pos             2
#define UART_CR1_RWU_Pos            1
#define UART_CR1_SBK_Pos            0
#define TXE_MASK                 0x00000080
#define RXNE_MASK                0x00000020
#define TC_MASK                  0x00000040
#define TXE_BIT_POS                 7
#define TC_BIT_POS                  6
#define RXNE_BIT_POS                5
#define BUSY                        1
#define IDLE                        0
#define USART_DIV_MANTISSA_MASK              0x0000FFF0
#define USART_DIV_FRACTION_MASK              0x0000000F
#define SHIFT_FOUR                           (4U)

typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}UART_t;
typedef struct
{
	u8 Transmit_Complete;
	u8 TX_DR_Empty;
	u8 RX_DR_Empty;
}Interrupt_State;

Interrupt_State Interrupt_Cfg;
UART_TxReqBuff_t Tx_Req[3];
UART_RxReqBuff_t Rx_Req[3];
static UART_t * const ChannelArr[UART_CHANNELS]={(UART_t*)UART1_BASE_ADDRESS,
		                                         (UART_t*)UART2_BASE_ADDRESS,
												 (UART_t*)UART6_BASE_ADDRESS};


UART_ErrorStatus_t UART_Init(const UART_ConfigType* ConfigPtr)
{
  u8 Loc_ErrorStatus = UART_Succ;
  u32 Loc_Over8;
  u32 Loc_TempMantissa;
  u32 Loc_TempFraction;
  u32 Loc_UsartDiv;
  u32 Loc_TempReg;

  if(!ConfigPtr)
  {
	  Loc_ErrorStatus = UART_NullPtr;
  }
  else
  {
	  Loc_Over8 = (ConfigPtr->Oversampling)/(UART_OVERSAMPLING_8);
	  Loc_UsartDiv = (((u64)SYS_CLK*1000)/((8*(2-Loc_Over8))*ConfigPtr->BaudRate)) ;
	  Loc_TempMantissa = Loc_UsartDiv/1000 ;
	  Loc_TempFraction = (Loc_UsartDiv % 1000 )*(8*(2-Loc_Over8));
	  if (Loc_TempFraction % 1000 >= 500)
	  	{
		  Loc_TempFraction = (Loc_TempFraction / 1000) + 1;
	  	}
	  	else
	  	{
	  		Loc_TempFraction = Loc_TempFraction / 1000;
	  	}
	  	if (Loc_TempFraction >= 0x10)
	  	{
	  		Loc_TempMantissa += Loc_TempFraction & 0xF0;
	  	}
	  	Loc_TempReg = (Loc_TempMantissa << 4)|(Loc_TempFraction & 0x0F );

	  ChannelArr[ConfigPtr->Channel]->CR1  = 0;
	  ChannelArr[ConfigPtr->Channel]->BRR = Loc_TempReg;
	  ChannelArr[ConfigPtr->Channel]->CR1 |= (ConfigPtr->Oversampling)<<UART_CR1_OVER8_Pos;
	  ChannelArr[ConfigPtr->Channel]->CR1 |= (ConfigPtr->WordLength)<<UART_CR1_M_Pos;
	  ChannelArr[ConfigPtr->Channel]->CR1 |= (ConfigPtr->ParityControl)<<UART_CR1_PCE_Pos;
	  ChannelArr[ConfigPtr->Channel]->CR1 |= (ConfigPtr->TransEnable)<<UART_CR1_TE_Pos;
	  ChannelArr[ConfigPtr->Channel]->CR1 |= (ConfigPtr->ReceiveEnable)<<UART_CR1_RE_Pos;
	  Interrupt_Cfg.Transmit_Complete      = (ConfigPtr->TransComplete_Int)<<UART_CR1_TCIE_Pos;
	  Interrupt_Cfg.TX_DR_Empty            = (ConfigPtr->TransDateRegisterEmpty_Int)<<UART_CR1_TXEIE_Pos;
	  Interrupt_Cfg.RX_DR_Empty            = (ConfigPtr->ReceiveDateRegisterEmpty_Int)<<UART_CR1_RXNEIE_Pos;
	  ChannelArr[ConfigPtr->Channel]->CR1 |= (ConfigPtr->UARTEnable)<<UART_CR1_UE_Pos;
	  ChannelArr[ConfigPtr->Channel]->SR   = 0 ;
  }
  return Loc_ErrorStatus ;
}
UART_ErrorStatus_t UART_SendByteAsynch(UART_Channel Channel, u8 Copy_Data)
{
	UART_ErrorStatus_t Loc_ErrorStauts = UART_Succ ;

    if(!(ChannelArr[Channel] ->SR & TXE_MASK))
    {
    	Loc_ErrorStauts = UART_BUSY ;
    }
    else
    {
    	ChannelArr[Channel]->DR = Copy_Data ;
    	ChannelArr[Channel]->CR1 |= Interrupt_Cfg.Transmit_Complete ;
    }
    return Loc_ErrorStauts ;
}
UART_ErrorStatus_t UART_TxBufferZeroCopy(UART_Buff_t * Copy_UserBuff )
{
    UART_ErrorStatus_t Loc_ErrorStatus = UART_Succ;
    if (!Copy_UserBuff) {
        Loc_ErrorStatus = UART_NullPtr;
    } else if (Tx_Req[Copy_UserBuff->Channel].State== BUSY) {
        Loc_ErrorStatus = UART_BUSY;
    } else {
    	Tx_Req[Copy_UserBuff->Channel].State= BUSY ;
        Tx_Req[Copy_UserBuff->Channel].buff.data = Copy_UserBuff->data ;
        Tx_Req[Copy_UserBuff->Channel].buff.size = Copy_UserBuff->size;
        Tx_Req[Copy_UserBuff->Channel].buff.pos = 0;
        ChannelArr[Copy_UserBuff->Channel]->DR = Tx_Req[Copy_UserBuff->Channel].buff.data[0];
        Tx_Req[Copy_UserBuff->Channel].buff.pos++;
        ChannelArr[Copy_UserBuff->Channel]->CR1 |= Interrupt_Cfg.Transmit_Complete;
    }
    return Loc_ErrorStatus;
}

UART_ErrorStatus_t UART_RxBufferAsync(UART_Buff_t * Copy_UserBuff )
{
	 u8 Loc_ErrorStatus = UART_Succ ;
	    if(!Copy_UserBuff)
	    {
	    	Loc_ErrorStatus = UART_NullPtr;
	    }
	    else if(Rx_Req[Copy_UserBuff->Channel].State == BUSY)
		{
	    	Loc_ErrorStatus = UART_BUSY;
		}
	    else
	    {
	    	Rx_Req[Copy_UserBuff->Channel].State = BUSY;
	    	Rx_Req[Copy_UserBuff->Channel].buff.data = Copy_UserBuff->data ;
	    	Rx_Req[Copy_UserBuff->Channel].buff.size = Copy_UserBuff->size;
	    	Rx_Req[Copy_UserBuff->Channel].buff.pos = 0;
	    	ChannelArr[Copy_UserBuff->Channel]->CR1 |= Interrupt_Cfg.RX_DR_Empty;
         }
	return Loc_ErrorStatus ;
}
UART_ErrorStatus_t UART_CallBackFunction(UART_Channel Channel, u8 Mode, Cb_t Add_CallBackFunction)
{
	u8 Loc_ErrorStatus =UART_Succ ;
	if(Add_CallBackFunction == NULL )
	{
		Loc_ErrorStatus = UART_NullPtr;
	}
	else
	{
         switch (Mode)
         {
         case TxMode : Tx_Req[Channel].Cb = Add_CallBackFunction ;
            break;
         case RxMode : Rx_Req[Channel].Cb = Add_CallBackFunction ;
        	break;
         }
	}
	return Loc_ErrorStatus;
}
void USART1_IRQHandler(void)
{
	if((ChannelArr[0] ->SR & TC_MASK))
		{
	      if(Tx_Req[0].buff.pos < Tx_Req[0].buff.size)
	      {
	    	  ChannelArr[0] ->SR &= ~(1<<TC_BIT_POS);
	    	  ChannelArr[0]->DR =Tx_Req[0].buff.data[Tx_Req[0].buff.pos];
	    	  Tx_Req[0].buff.pos++;
	      }
	      else{
	    	  Tx_Req[0].State = IDLE ;
	    	  if(Tx_Req[0].Cb)
	    	  {
	    		  Tx_Req[0].Cb();
	    	  }
	    	  ChannelArr[0] ->SR &= ~(1<<TC_BIT_POS);
	      }
		}
		if((ChannelArr[0] ->SR & RXNE_MASK))
		{
			if(Rx_Req[0].buff.pos < Rx_Req[0].buff.size)
			      {
			          Rx_Req[0].buff.data[Rx_Req[0].buff.pos]= ChannelArr[0]->DR ;
	    	  Rx_Req[0].buff.pos++;
			      }
			      else{

			    	  ChannelArr[0] ->SR &= ~(1<<RXNE_BIT_POS);
			    	  Rx_Req[0].State = IDLE ;
			    	  if(Rx_Req[0].Cb){
			    		  Rx_Req[0].Cb();
			    	  }
			      }
}
}
void USART2_IRQHandler(void)
{
	if((ChannelArr[1] ->SR & TC_MASK)){
	      if(Tx_Req[1].buff.pos < Tx_Req[1].buff.size){
	    	  ChannelArr[1] ->SR &= ~(1<<TC_BIT_POS);
	    	  ChannelArr[1]->DR =Tx_Req[1].buff.data[Tx_Req[1].buff.pos];
	    	  Tx_Req[1].buff.pos++;
	      }
	      else {
	    	  Tx_Req[1].State = IDLE ;
	    	  if(Tx_Req[1].Cb) {
	    		  Tx_Req[1].Cb();
	    	  }
	    	  ChannelArr[1] ->SR &= ~(1<<TC_BIT_POS);
	      }
		}
		if((ChannelArr[1] ->SR & RXNE_MASK)){
			if(Rx_Req[1].buff.pos < Rx_Req[1].buff.size) {
			          Rx_Req[1].buff.data[Rx_Req[1].buff.pos]= ChannelArr[1]->DR ;
			    	  Rx_Req[1].buff.pos++;
			      }
			      else{

			    	  ChannelArr[1] ->SR &= ~(1<<RXNE_BIT_POS);
			    	  Rx_Req[1].State = IDLE ;
			    	  if(Rx_Req[1].Cb)
			    	  {
			    		  Rx_Req[1].Cb();
			    	  }
			      }
}
	}
void USART6_IRQHandler(void)
{
	if((ChannelArr[2] ->SR & TC_MASK)){
	      if(Tx_Req[2].buff.pos < Tx_Req[2].buff.size){
	    	  ChannelArr[2] ->SR &= ~(1<<TC_BIT_POS);
	    	  ChannelArr[2]->DR =Tx_Req[2].buff.data[Tx_Req[2].buff.pos];
	    	  Tx_Req[2].buff.pos++;
	      }
	      else{
	    	  Tx_Req[2].State = IDLE ;
	    	  if(Tx_Req[2].Cb){
	    		  Tx_Req[2].Cb();
	    	  }
	    	  ChannelArr[2] ->SR &= ~(1<<TC_BIT_POS);
	      }
		}
		if((ChannelArr[2] ->SR & RXNE_MASK)){
			if(Rx_Req[2].buff.pos < Rx_Req[2].buff.size){
			          Rx_Req[2].buff.data[Rx_Req[2].buff.pos]= ChannelArr[2]->DR ;
			    	  Rx_Req[2].buff.pos++;
			      }
		        else {

			    	  ChannelArr[2] ->SR &= ~(1<<RXNE_BIT_POS);
			    	  Rx_Req[2].State = IDLE ;
			    	  if(Rx_Req[2].Cb) {
			    		  Rx_Req[2].Cb();
			    	  }
	      }
        }
	}
