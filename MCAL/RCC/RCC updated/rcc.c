/**
  ******************************************************************************
  * @file    rcc.c
  * @brief   Reset and Clock Control (RCC) configuration for STM32F401 microcontroller.
  ******************************************************************************
  * @attention
  *
  * This file provides functions to configure the RCC peripheral, including the
  * initialization of the system clock using the High-Speed Internal (HSI) oscillator
  * and the Phase-Locked Loop (PLL). The configured system clock is used as the main
  * clock source for the microcontroller.
  */
#include "rcc.h"
/*--------------------------------------------------MASKS---------------------------------------------------------*/
#define PLL_MASK      0xF0BC7000
#define SWS_MASK      0xFFFFFFF3
#define SWS_HSI    	  0x00
#define SWS_HSE       0x01
#define SWS_PLL       0x02
#define HSI_RDY       0x02
#define HSE_RDY       0x20000
#define PLL_RDY       0x2000000
#define SW_CLEAR      0xFFFFFFFC
#define HSI_SET       0x00
#define HSE_SET       0x01
#define PLL_SET       0x02
#define PLL_SRC_CLR   0xFFBFFFFF
#define PLL_SRC_HSE   0xFF4FFFFF
#define PLL_M_CLR     0xFFFFFFC0
#define PLL_N_CLR     0xFFFF803F
#define PLL_P_CLR     0xFFFCFFFF

#define RCC_u32BASEADDRESS  0x40023800

typedef struct
{
    volatile u32 CR;             /*!< RCC clock control register */
    volatile u32 PLLCFGR;        /*!< RCC PLL configuration register */
    volatile u32 CFGR;           /*!< RCC clock configuration register */
    volatile u32 CIR;            /*!< RCC clock interrupt register */
    volatile u32 AHB1RSTR;        /*!< RCC AHB1 peripheral reset register */
    volatile u32 AHB2RSTR;        /*!< RCC AHB2 peripheral reset register */
    volatile u32 Reserved[2];     /*!< Reserved space */
    volatile u32 APB1RSTR;        /*!< RCC APB1 peripheral reset register */
    volatile u32 APB2RSTR;        /*!< RCC APB2 peripheral reset register */
    volatile u32 Reserved1[2];    /*!< Reserved space */
    volatile u32 AHB1ENR;         /*!< RCC AHB1 peripheral clock enable register */
    volatile u32 AHB2ENR;         /*!< RCC AHB2 peripheral clock enable register */
    volatile u32 Reserved2[2];    /*!< Reserved space */
    volatile u32 APB1ENR;         /*!< RCC APB1 peripheral clock enable register */
    volatile u32 APB2ENR;         /*!< RCC APB2 peripheral clock enable register */
    volatile u32 AHB1LPENR;      /*!< RCC AHB1 peripheral clock enable in low power mode register */
    volatile u32 AHB2LPENR;      /*!< RCC AHB2 peripheral clock enable in low power mode register */
    volatile u32 Reserved3[2];    /*!< Reserved space */
    volatile u32 APB1LPENR;      /*!< RCC APB1 peripheral clock enable in low power mode register */
    volatile u32 APB2LPENR;      /*!< RCC APB2 peripheral clock enable in low power mode register */
    volatile u32 Reserved4[2];    /*!< Reserved space */
    volatile u32 BDCR;           /*!< RCC Backup domain control register */
    volatile u32 CSR;            /*!< RCC clock control & status register */
    volatile u32 Reserved5[2];    /*!< Reserved space */
    volatile u32 SSCGR;          /*!< RCC spread spectrum clock generation register */
    volatile u32 PLLI2SCFGR;     /*!< RCC PLLI2S configuration register */
    volatile u32 RESERVED6;      /*!< Reserved space */
    volatile u32 DCKCFGR;        /*!< RCC Dedicated Clock Configuration Register */
} Rcc_tstrRegisterType;

/* Make the structure point at the base address of RCC */
#define RCC    ((Rcc_tstrRegisterType* )(RCC_u32BASEADDRESS))

 Rcc_ErrorStatus_t Rcc_SetClkOnOff(u32 Copy_u32ClkName, u8 Copy_u8ClkState)
 {
	 u8 loc_u8ErrorStatus = Rcc_enuSucceded ;

      u32 loc_TempVar ;
	 switch (Copy_u8ClkState)
	 {
	 case CLK_ON :
        RCC->CR |=Copy_u32ClkName ;
        break ;
	 case CLK_OFF:
		 loc_TempVar = RCC->CFGR ;
         loc_TempVar &= ~(SWS_MASK)  ;
         if((Copy_u32ClkName == SYSCLK_HSI && loc_TempVar == SWS_HSI) || (Copy_u32ClkName == SYSCLK_HSE && loc_TempVar == SWS_HSE)
        		 || (Copy_u32ClkName == SYSCLK_PLL && loc_TempVar == SWS_PLL)  )
         {
        	 loc_u8ErrorStatus = Rcc_enuCantCloseClk ;
         }
         else
         {
        	 RCC->CR &=~(Copy_u32ClkName) ;
         }
	 }
       return loc_u8ErrorStatus ;
 }

 Rcc_ErrorStatus_t Rcc_SetSysClk(u32 Copy_u32ClkName)
 {
	     u8 loc_u8ErrorStatus = Rcc_enuSucceded;
	     u32 loc_u32Timeout = 0;
	     u32 loc_u32temp = RCC->CR;
	     u32 loc_u32Rdyflagraised = 0;
	     u32  Loc_u32Rdyflag = 0 ;
         u32 Loc_u8ClkSet = 0 ;

         if (Copy_u32ClkName == SYSCLK_HSI)
         {
        	 Loc_u32Rdyflag = HSI_RDY ;
        	 Loc_u8ClkSet  = HSI_SET ;
         }
         else if (Copy_u32ClkName == SYSCLK_HSE)
		 {
        	 Loc_u32Rdyflag = HSE_RDY ;
        	 Loc_u8ClkSet  = HSE_SET ;
		 }

         else if (Copy_u32ClkName == SYSCLK_PLL)
		 {
        	 Loc_u32Rdyflag = PLL_RDY ;
        	 Loc_u8ClkSet  = PLL_SET ;
		 }

         else
         {
           loc_u8ErrorStatus = Rcc_enuInvalidClkName ;
         }
         while (loc_u32Rdyflagraised != 1 && loc_u32Timeout < 1000)
        	         {
        	             loc_u32Timeout++;
        	             loc_u32temp = RCC->CR;
        	             loc_u32temp &= Loc_u32Rdyflag ;
        	             if (loc_u32temp == Loc_u32Rdyflag)
        	             {
        	                 loc_u32Rdyflagraised = 1;
        	             }
        	             else if (loc_u32Timeout == 1000)
        	             {
        	                 loc_u8ErrorStatus = Rcc_enuCLkNotReady;  // Set error status
        	             }
        	         }

        	         if (loc_u8ErrorStatus != Rcc_enuCLkNotReady)
        	         {

        	             loc_u32temp = RCC->CFGR;
        	             loc_u32temp &= SW_CLEAR;
        	             loc_u32temp |= Loc_u8ClkSet;

        	             RCC->CFGR = loc_u32temp;
        	         }

	     return loc_u8ErrorStatus;
 }
 Rcc_ErrorStatus_t Rcc_SetPeripheralOnOff(u32 Copy_u32Name , u8 Copy_u8State )
 {
	 u8 loc_u8ErrorStatus = Rcc_enuSucceded;

	 u16 loc_u16ConditionAhp1 = (Copy_u32Name == DMA1 || Copy_u32Name == DMA2 || Copy_u32Name == DMA1 || Copy_u32Name == GPIO_A ||
			 Copy_u32Name == GPIO_B  || Copy_u32Name == GPIO_C || Copy_u32Name == GPIO_D || Copy_u32Name == GPIO_E ||
			 Copy_u32Name == GPIO_H);
	 u8 loc_u16ConditionAhp2 = (Copy_u32Name == USB_OTG);

	 u16 loc_u16ConditionAbp1 = (Copy_u32Name == PW_INTF || Copy_u32Name == I2C_1 || Copy_u32Name == I2C_2 || Copy_u32Name == I2C_3 ||
			 Copy_u32Name == USART2  || Copy_u32Name == SPI_2 || Copy_u32Name == SPI_3 || Copy_u32Name == WINDOW_WD ||
			 Copy_u32Name == TIM2 || Copy_u32Name == TIM3 || Copy_u32Name == TIM4 || Copy_u32Name == TIM5 );

	 u16 loc_u16ConditionAbp2 = (Copy_u32Name == TIM9 || Copy_u32Name == TIM10 || Copy_u32Name == TIM11 || Copy_u32Name == SPI_1 ||
			 Copy_u32Name == SPI_4  || Copy_u32Name == SYS_CFGCTRL || Copy_u32Name ==  ADC1 || Copy_u32Name == USART1 ||
			 Copy_u32Name == USART6 || Copy_u32Name == TIM1 );

      switch (Copy_u8State)
      {
      case CLK_ON :
    	  if(loc_u16ConditionAhp1)
    	  {
              RCC->AHB1ENR |= Copy_u32Name ;
    	  }
    	  else if (loc_u16ConditionAhp2)
    	  {
    		  RCC->AHB2ENR |= Copy_u32Name ;
    	  }
    	  else if (loc_u16ConditionAbp1)
    	  {
    		  RCC->APB1ENR |= Copy_u32Name ;
    	  }
    	  else if (loc_u16ConditionAbp2)
		  {
    		  RCC->APB2ENR |= Copy_u32Name ;
		  }
    	  else
    	  {
    		  loc_u8ErrorStatus = Rcc_enuInvalidperName;
    	  }
           break ;
      case CLK_OFF :
         	  if(loc_u16ConditionAhp1)
         	  {
                  RCC->AHB1ENR &=~Copy_u32Name ;
         	  }
         	  else if (loc_u16ConditionAhp2)
         	  {
         		  RCC->AHB2ENR &=~Copy_u32Name ;
         	  }
         	  else if (loc_u16ConditionAbp1)
         	  {
         		  RCC->APB1ENR &=~Copy_u32Name ;
         	  }
         	  else if (loc_u16ConditionAbp2)
     		  {
         		  RCC->APB2ENR &=~ Copy_u32Name ;
     		  }
         	  else
         	  {
         		  loc_u8ErrorStatus = Rcc_enuInvalidperName;
         	  }
                break ;
      }
      return loc_u8ErrorStatus ;
 }

 Rcc_ErrorStatus_t Rcc_SetPreScaler(u32 Copy_u32Name , u32 Copy_u8Value)
 {
	u8 loc_u8ErrorStatus =  Rcc_enuSucceded;
	u32 loc_u32Temp = RCC->CFGR ;
	loc_u32Temp &= Copy_u32Name ;
	loc_u32Temp |= Copy_u8Value ;
	RCC->CFGR =  loc_u32Temp ;
    return loc_u8ErrorStatus;
 }
 Rcc_ErrorStatus_t Rcc_SetPLLCfg   (u32 copy_u32ClkSrc  , u32 CopyMValue , u32 CopyNValue , u32 CopyPValue)
 {
	 u8 loc_u8ErrorStatus = Rcc_enuSucceded;
     u32 loc_u32Temp = RCC-> CR;
     loc_u32Temp &= SYSCLK_PLL;
     u32 loc_clksrc = 0 ;
     if (loc_u32Temp == SYSCLK_PLL)
     {
    	 loc_u8ErrorStatus = Rcc_enuCantCfgPllOn ;
     }
     else if (copy_u32ClkSrc == SYSCLK_HSE)
     {
	 loc_clksrc = PLL_SRC_HSE ;
     }
     else if (copy_u32ClkSrc == SYSCLK_HSI)
     {
    	 loc_clksrc = PLL_SRC_CLR ;
     }
     else
     {
    	 loc_u8ErrorStatus =  Rcc_enuInvalidClkName;
     }
       loc_u32Temp = RCC-> PLLCFGR ;
       loc_u32Temp &= PLL_SRC_CLR ;
       loc_u32Temp |=loc_clksrc;
       loc_u32Temp &= PLL_M_CLR ;
       loc_u32Temp |=CopyMValue;
       loc_u32Temp &= PLL_N_CLR ;
       loc_u32Temp |=CopyNValue;
       loc_u32Temp &= PLL_P_CLR ;
       loc_u32Temp |=CopyPValue;
       RCC-> PLLCFGR =loc_u32Temp ;
      return loc_u8ErrorStatus ;
}
