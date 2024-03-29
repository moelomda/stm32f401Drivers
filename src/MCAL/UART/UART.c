/*==========================================================
 * File: UART.c
 * Author: [Mohamed Ahmed Fouad ]
 ===========================================================*/
#include "UART.h"
#define UART1_BASE_ADDRESS             0x40011000
#define UART2_BASE_ADDRESS             0x40004400
#define UART6_BASE_ADDRESS             0x40011400
#define UART_CHANNELS    3
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
typedef struct
{
  UART_Channel Channel;
  u16 *data;
  u32 pos ;
  u32 size;
}UART_Buff_t;
typedef struct
{
	UART_Buff_t buff;
    u8 State ;
    Cb_t Cb;
} UART_TxReqBuff_t;

typedef struct
{
	UART_Buff_t buff;
    u8 State ;
    Cb_t Cb;
} UART_RxReqBuff_t;
Interrupt_State Interrupt_Cfg;
UART_TxReqBuff_t Tx_Req;
UART_RxReqBuff_t Rx_Req;
static Cb_t Cb_TxArr[3];
static Cb_t Cb_RxArr[3];
static UART_t * const ChannelArr[UART_CHANNELS]={(UART_t*)UART1_BASE_ADDRESS,
		                                         (UART_t*)UART2_BASE_ADDRESS,
												 (UART_t*)UART6_BASE_ADDRESS};
static void Helper_Calculate_Baudrate_Scaled(const UART_ConfigType* Config, u16 *mantissa, u8 *fraction);
UART_ErrorStatus_t UART_Init(const UART_ConfigType* ConfigPtr)
{
  u8 Loc_ErrorStatus = UART_Succ;
  u16 Loc_Mantissa ;
  u8  Loc_Fraction;
  if(!ConfigPtr)
  {
	  Loc_ErrorStatus = UART_NullPtr;
  }
  else
  {
	  Helper_Calculate_Baudrate_Scaled(ConfigPtr ,&Loc_Mantissa,&Loc_Fraction);
	  ChannelArr[ConfigPtr->Channel]->CR1  = 0;
	  ChannelArr[ConfigPtr->Channel]->BRR |= ((Loc_Mantissa << 4) | (Loc_Fraction & 0x0F));
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
    if((ChannelArr[Channel] ->SR & TXE_MASK)>>(TXE_BIT_POS))
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
UART_ErrorStatus_t UART_TxBufferZeroCopy(u16 Copy_Buffer , u32 Copy_len , Cb_t Cb )

{
    u8 Loc_ErrorStatus = UART_Succ ;
    if(!Cb)
    {
    	Loc_ErrorStatus = UART_NullPtr;
    }
    else if(Tx_Req.State == BUSY)
	{
    	Loc_ErrorStatus = UART_BUSY;
	}
    else
    {
    	Tx_Req.State = BUSY;
    	*(Rx_Req.buff.data) = Copy_Buffer ;
    	Tx_Req.buff.size = Copy_len;
    	Tx_Req.buff.pos = 0;
    	Tx_Req.Cb = Cb;
    	ChannelArr[Tx_Req.buff.Channel]->DR =Tx_Req.buff.data[0];
    	Tx_Req.buff.pos++;
    	ChannelArr[Tx_Req.buff.Channel]->CR1 |= Interrupt_Cfg.Transmit_Complete;
    }
    return Loc_ErrorStatus;
}
UART_ErrorStatus_t UART_RxBufferAsync(u16 Copy_Buffer , u32 Copy_len , Cb_t Cb )
{
	 u8 Loc_ErrorStatus = UART_Succ ;
	    if(!Cb)
	    {
	    	Loc_ErrorStatus = UART_NullPtr;
	    }
	    else if(Tx_Req.State == BUSY)
		{
	    	Loc_ErrorStatus = UART_BUSY;
		}
	    else
	    {
	    	Rx_Req.State = BUSY;
	    	*(Rx_Req.buff.data) = Copy_Buffer ;
	    	Rx_Req.buff.size = Copy_len;
	    	Rx_Req.buff.pos = 0;
	    	Rx_Req.Cb = Cb;
	    	ChannelArr[Rx_Req.buff.Channel]->CR1 |= Interrupt_Cfg.RX_DR_Empty;
         }
	return Loc_ErrorStatus ;
}
UART_ErrorStatus_t UART_CallBackFunction(UART_Channel Channel, UART_enuMode_t Mode, Cb_t Add_CallBackFunction)
{
   u8 Loc_ErrorStatus =UART_Succ;
   if(!Add_CallBackFunction)
   {
      if(Mode == TxMode)
      {
    	  Cb_TxArr[Channel] = Add_CallBackFunction;
      }
      else if (Mode == RxMode)
      {
    	  Cb_RxArr[Channel] = Add_CallBackFunction;
      }
      else
      {
    	  Loc_ErrorStatus= UART_Invalid_Mode;
      }
   }
   else
   {
	   Loc_ErrorStatus= UART_NullPtr;
   }
   return Loc_ErrorStatus;
}
static void Helper_Calculate_Baudrate_Scaled(const UART_ConfigType* Config , u16 *mantissa, u8 *fraction)
{
	u64 scaled_usartdiv;
	u16 temp_fraction;
	scaled_usartdiv = ((u64)SYS_CLK * 1000) / (Config->BaudRate * (8 * (2 - Config->Oversampling)));

	temp_fraction = (scaled_usartdiv % 1000) * (8 * (2 - Config->Oversampling));
	temp_fraction /= 1000;

	if (temp_fraction > 15) {
	    *mantissa += (temp_fraction >> 4);
	    temp_fraction &= 0x0F;
	}

	*mantissa = scaled_usartdiv / 1000;
	*fraction = temp_fraction;
}
void USART1_IRQHandler(void)
{
		if((ChannelArr[0] ->SR & TC_MASK)>>(TC_BIT_POS))
		{
	      if(Tx_Req.buff.pos < Tx_Req.buff.size)
	      {
	    	  ChannelArr[0] ->SR &= ~(1<<TC_BIT_POS);
	    	  ChannelArr[0]->DR =Tx_Req.buff.data[Tx_Req.buff.pos];
	    	  Tx_Req.buff.pos++;
	      }
	      else
	      {
	    	  Tx_Req.State = IDLE ;
	    	  if(Tx_Req.Cb)
	    	  {
	    		  Tx_Req.Cb();
	    	  }
	    	  ChannelArr[0] ->SR &= ~(1<<TC_BIT_POS);
	      }
		}
		if((ChannelArr[0] ->SR & RXNE_MASK)>>(RXNE_BIT_POS ))
		{
			if(Rx_Req.buff.pos < Rx_Req.buff.size)
			      {
			          Rx_Req.buff.data[Rx_Req.buff.pos]= ChannelArr[0]->DR ;
			    	  Rx_Req.buff.pos++;
			      }
			      else
			      {

			    	  ChannelArr[0] ->SR &= ~(1<<RXNE_BIT_POS);
			    	  Rx_Req.State = IDLE ;
			    	  if(Rx_Req.Cb)
			    	  {
			    		  Rx_Req.Cb();
			    	  }
			      }
}
	}

void USART2_IRQHandler(void)
{
	if((ChannelArr[1] ->SR & TC_MASK)>>(TC_BIT_POS))
	{
      if(Tx_Req.buff.pos < Tx_Req.buff.size)
      {
    	  ChannelArr[1] ->SR &= ~(1<<TC_BIT_POS);
    	  ChannelArr[1]->DR =Tx_Req.buff.data[Tx_Req.buff.pos];
    	  Tx_Req.buff.pos++;
      }
      else
      {
    	  Tx_Req.State = IDLE ;
    	  if(Tx_Req.Cb)
    	  {
    		  Tx_Req.Cb();
    	  }
    	  ChannelArr[1] ->SR &= ~(1<<TC_BIT_POS);
      }
	}
	if((ChannelArr[1] ->SR & RXNE_MASK)>>(RXNE_BIT_POS ))
	{
		if(Rx_Req.buff.pos < Rx_Req.buff.size)
		      {
		          Rx_Req.buff.data[Rx_Req.buff.pos]= ChannelArr[1]->DR ;
		    	  Rx_Req.buff.pos++;
		      }
		      else
		      {
		    	  ChannelArr[1] ->SR &= ~(1<<RXNE_BIT_POS);
		    	  Rx_Req.State = IDLE ;
		    	  if(Rx_Req.Cb)
		    	  {
		    		  Rx_Req.Cb();
		    	  }
		      }
	}
}
void USART6_IRQHandler(void)
{
	if((ChannelArr[2] ->SR & TC_MASK)>>(TC_BIT_POS))
	{
      if(Tx_Req.buff.pos < Tx_Req.buff.size)
      {
    	  ChannelArr[2] ->SR &= ~(1<<TC_BIT_POS);
    	  ChannelArr[2]->DR =Tx_Req.buff.data[Tx_Req.buff.pos];
    	  Tx_Req.buff.pos++;
      }
      else
      {
    	  Tx_Req.State = IDLE ;
    	  if(Tx_Req.Cb)
    	  {
    		  Tx_Req.Cb();
    	  }
    	  ChannelArr[2] ->SR &= ~(1<<TC_BIT_POS);
      }
	}
	if((ChannelArr[2] ->SR & RXNE_MASK)>>(RXNE_BIT_POS ))
	{
		if(Rx_Req.buff.pos < Rx_Req.buff.size)
		      {
		          Rx_Req.buff.data[Rx_Req.buff.pos]= ChannelArr[3]->DR ;
		    	  Rx_Req.buff.pos++;
		      }
		      else
		      {
		    	  ChannelArr[2] ->SR &= ~(1<<RXNE_BIT_POS);
		    	  Rx_Req.State = IDLE ;
		    	  if(Rx_Req.Cb)
		    	  {
		    		  Rx_Req.Cb();
		    	  }
		      }
	}
}
