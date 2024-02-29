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
  *
  * @note
  *   - Refer to the STM32F401 reference manual and datasheet for detailed information.
  *
  ******************************************************************************
  */
#include "RCC.h"


 Rcc_ErrorStatus_t Rcc_ClkOnOff(u8 Copy_u8ClkName, u8 Copy_u8ClkState)
 {
    u8 loc_u8ErrorStatus = Rcc_enuSucceded ;
    u32 loc_u32temp ;
     if(Copy_u8ClkName == HSI_CLK)
     {
    	   switch(Copy_u8ClkState)
    	   {
    	     case CLK_ON : RCC->CR |= 0x00000001 ;  break ;
    	     case CLK_OFF:
    	    	loc_u32temp = RCC -> CFGR ;
    	    	loc_u32temp &= 0x0000000C ;
    	    	if(loc_u32temp == 0x00000000)
    	    	{
                      loc_u8ErrorStatus = Rcc_enuCantCloseClk ;
    	    	}
    	    	else
    	    	{
    	    		RCC->CR &= 0xFFFFFFFE ;
    	    	}
                break;
    	     default :
    	        loc_u8ErrorStatus =Rcc_enuInvalidClkState ;
    	    	break ;
           }
     }
     else if (Copy_u8ClkName == HSE_CLK)
     {

				 switch(Copy_u8ClkState)
				 {
				 case CLK_ON :  RCC -> CR |= 0x00010000 ; break ;
				 case CLK_OFF:
				   loc_u32temp = RCC -> CFGR ;
				   loc_u32temp &= 0x0000000C ;
					 if(loc_u32temp == 0x00000004)
					  {
						   loc_u8ErrorStatus = Rcc_enuCantCloseClk ;
					  }
					 else
					  {
						   RCC->CR &= 0xFFFEFFFF;
					  }
					 break ;
				 default :
					 loc_u8ErrorStatus =Rcc_enuInvalidClkState ;
					 break ;
				 }
      }
     else if (Copy_u8ClkName == PLL_CLK)
     {
    	 switch(Copy_u8ClkState)
    	 {
        	   case CLK_ON :  RCC -> CR |= 0x01000000 ; break ;
        	   case CLK_OFF:
        	     loc_u32temp = RCC -> CFGR ;
        	     loc_u32temp &= 0x0000000C ;
        	  if(loc_u32temp == 0x00000008)
        	    {
        	    	 loc_u8ErrorStatus = Rcc_enuCantCloseClk ;
        	    }
        	  else
        	    {
        	    	 RCC->CR &= 0xFEFFFFFF;
        	    }
        	     break ;
        	   default :
        	   loc_u8ErrorStatus = Rcc_enuInvalidClkState ;
        	     break ;
        	    }
         }

     else
     {
            loc_u8ErrorStatus = Rcc_enuInvalidClkName ;
     }
  return loc_u8ErrorStatus ;
 }

 Rcc_ErrorStatus_t Rcc_SetSysClk(u8 Copy_u8ClkName)
 {

	 // Initialize error status to success
	     u8 loc_u8ErrorStatus = Rcc_enuSucceded;

	     // Initialize timeout counter
	     u32 loc_u32Timeout = 0;

	     // Read the current value of the RCC CR register
	     u32 loc_u32temp = RCC->CR;

	     // Flag indicating if the specified clock is ready
	     u32 loc_u32Rdyflag = 0;

	     // Check if the specified clock is HSI
	     if (Copy_u8ClkName == HSI_CLK)
	     {
	         // Loop until the specified clock is ready or timeout occurs
	         while (loc_u32Rdyflag != 1 && loc_u32Timeout < 1000)
	         {
	             // Increment timeout counter
	             loc_u32Timeout++;

	             // Read the value of the RCC CR register
	             loc_u32temp = RCC->CR;

	             // Mask out the HSI RDY flag
	             loc_u32temp &= 0x00000002;

	             // Check if HSI is ready
	             if (loc_u32temp == 0x00000002)
	             {
	                 loc_u32Rdyflag = 1;  // Set ready flag
	             }
	             // Check if timeout occurred
	             else if (loc_u32Timeout == 1000)
	             {
	                 loc_u8ErrorStatus = Rcc_enuCLkNotReady;  // Set error status
	             }
	         }

	         // If clock is ready, proceed to set it as system clock
	         if (loc_u8ErrorStatus != Rcc_enuCLkNotReady)
	         {
	             // Read current configuration and mask out SW bits
	             loc_u32temp = RCC->CFGR;
	             loc_u32temp &= CFGR_SW_MASK;

	             // Update CFGR register to set specified clock as system clock
	             RCC->CFGR = loc_u32temp;
	         }
	     }
	     else if (Copy_u8ClkName == HSE_CLK)
	     {
	            // Loop until the specified clock is ready or timeout occurs
	            while (loc_u32Rdyflag != 1 && loc_u32Timeout < 1000)
	            {
	                // Increment timeout counter
	                loc_u32Timeout++;

	                // Read the value of the RCC CR register
	                loc_u32temp = RCC->CR;

	                // Mask out the HSE RDY flag
	                loc_u32temp &= 0x00020000;

	                // Check if HSE is ready
	                if (loc_u32temp == 0x00020000)
	                {
	                    loc_u32Rdyflag = 1;  // Set ready flag
	                }
	                // Check if timeout occurred
	                else if (loc_u32Timeout == 1000)
	                {
	                    loc_u8ErrorStatus = Rcc_enuCLkNotReady;  // Set error status
	                }
	            }

	            // If clock is ready, proceed to set it as system clock
	            if (loc_u8ErrorStatus != Rcc_enuCLkNotReady)
	            {
	                // Read current configuration and mask out SW bits
	                loc_u32temp = RCC->CFGR;
	                loc_u32temp &= CFGR_SW_MASK;
	                loc_u32temp |= 0x00000001;

	                // Update CFGR register to set specified clock as system clock
	                RCC->CFGR = loc_u32temp;
	            }
	          }
	     else if (Copy_u8ClkName == PLL_CLK)
	     {

	    	         // Loop until the specified clock is ready or timeout occurs
	    	         while (loc_u32Rdyflag != 1 && loc_u32Timeout < 1000)
	    	         {
	    	             // Increment timeout counter
	    	             loc_u32Timeout++;

	    	             // Read the value of the RCC CR register
	    	             loc_u32temp = RCC->CR;

	    	             // Mask out the PLL RDY flag
	    	             loc_u32temp &= 0x02000000;

	    	             // Check if PLL is ready
	    	             if (loc_u32temp == 0x02000000)
	    	             {
	    	                 loc_u32Rdyflag = 1;  // Set ready flag
	    	             }
	    	             // Check if timeout occurred
	    	             else if (loc_u32Timeout == 1000)
	    	             {
	    	                 loc_u8ErrorStatus = Rcc_enuCLkNotReady;  // Set error status
	    	             }
	    	         }

	    	         // If clock is ready, proceed to set it as system clock
	    	         if (loc_u8ErrorStatus != Rcc_enuCLkNotReady)
	    	         {
	    	             // Read current configuration and mask out SW bits
	    	             loc_u32temp = RCC->CFGR;
	    	             loc_u32temp &= CFGR_SW_MASK;
	    	             loc_u32temp |= 0x00000002;

	    	             // Update CFGR register to set specified clock as system clock
	    	             RCC->CFGR = loc_u32temp;

	    	         }


	     }

	     // Return error status
	     return loc_u8ErrorStatus;

 }
 Rcc_ErrorStatus_t Rcc_PeripheralOnOff(u8 Copy_u8Name , u8 Copy_u8State )
 {

	 u8 loc_u8ErrorStatus = Rcc_enuSucceded;
	 u32 loc_u32Temp = 0 ;
     if (Copy_u8State == CLK_OFF  )
     {
        switch (Copy_u8Name)
        {
        case DMA1:
            // Disable DMA1 peripheral
            loc_u32Temp = RCC->AHB1ENR;
            loc_u32Temp &= 0xFFDFFFFF; // Clear corresponding bit for DMA1
            RCC->AHB1ENR = loc_u32Temp;
            break;
        case DMA2:
            // Enable DMA2 peripheral
            loc_u32Temp = RCC->AHB1ENR;
            loc_u32Temp &= 0xFFBFFFFF; // Set corresponding bit for DMA2
            RCC->AHB1ENR = loc_u32Temp;
            break;
        case GPIO_A:
            // Enable GPIOA peripheral
            loc_u32Temp = RCC->AHB1ENR;
            loc_u32Temp &= 0xFFFFFFFE; // Set corresponding bit for GPIOA
            RCC->AHB1ENR = loc_u32Temp;
            break;
        case GPIO_B:
            // Enable GPIOB peripheral
            loc_u32Temp = RCC->AHB1ENR;
            loc_u32Temp &= 0xFFFFFFFD; // Set corresponding bit for GPIOB
            RCC->AHB1ENR = loc_u32Temp;
            break;
        case GPIO_C:
            // Enable GPIOC peripheral
            loc_u32Temp = RCC->AHB1ENR;
            loc_u32Temp &= 0x00000004; // Set corresponding bit for GPIOC
            RCC->AHB1ENR = loc_u32Temp;
            break;
        case GPIO_D:
            // Enable GPIOD peripheral
            loc_u32Temp = RCC->AHB1ENR;
            loc_u32Temp |= 0x00000008; // Set corresponding bit for GPIOD
            RCC->AHB1ENR = loc_u32Temp;
            break;
        case GPIO_E:
            // Enable GPIOE peripheral
            loc_u32Temp = RCC->AHB1ENR;
            loc_u32Temp |= 0x00000010; // Set corresponding bit for GPIOE
            RCC->AHB1ENR = loc_u32Temp;
            break;
        case GPIO_H:
            // Enable GPIOH peripheral
            loc_u32Temp = RCC->AHB1ENR;
            loc_u32Temp |= 0x00000080; // Set corresponding bit for GPIOH
            RCC->AHB1ENR = loc_u32Temp;
            break;
        case USB_OTG :
        	loc_u32Temp = RCC->AHB2ENR;
        	loc_u32Temp |= 0x00000080;
        	RCC->AHB2ENR = loc_u32Temp;
        	break;
        case I2C_1:
            // Enable I2C1 peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp |= 0x00200000; // Set corresponding bit for I2C1
            RCC->APB1ENR = loc_u32Temp;
            break;
        case I2C_2:
            // Enable I2C2 peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp |= 0x00400000; // Set corresponding bit for I2C2
            RCC->APB1ENR = loc_u32Temp;
            break;
        case I2C_3:
            // Enable I2C3 peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp |= 0x00800000; // Set corresponding bit for I2C3
            RCC->APB1ENR = loc_u32Temp;
            break;
        case USART2:
            // Enable USART2 peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp |= 0x00020000; // Set corresponding bit for USART2
            RCC->APB1ENR = loc_u32Temp;
            break;
        case SPI_2:
            // Enable SPI2 peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp |= 0x00004000; // Set corresponding bit for SPI2
            RCC->APB1ENR = loc_u32Temp;
            break;
        case SPI_3:
            // Enable SPI3 peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp |= 0x00008000; // Set corresponding bit for SPI3
            RCC->APB1ENR = loc_u32Temp;
            break;
        case TIM2:
            // Enable TIM2 peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp |= 0x00000001; // Set corresponding bit for TIM2
            RCC->APB1ENR = loc_u32Temp;
            break;
        case TIM3:
            // Enable TIM3 peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp &= 0xFFFFFFFD;; // Set corresponding bit for TIM3
            RCC->APB1ENR = loc_u32Temp;
            break;
        case TIM4:
            // Enable TIM4 peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp &= 0xFFFFFFFB; // Set corresponding bit for TIM4
            RCC->APB1ENR = loc_u32Temp;
            break;
        case TIM5:
            // Enable TIM5 peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp &= 0xFFFFFFF7; // Set corresponding bit for TIM5
            RCC->APB1ENR = loc_u32Temp;
            break;
        case WINDOW_WD:
            // Enable Window Watchdog peripheral
            loc_u32Temp = RCC->APB1ENR;
            loc_u32Temp &= 0xFFFFF7FF; // Set corresponding bit for Window Watchdog
            RCC->APB1ENR = loc_u32Temp;
            break;
        case TIM9:
            // Enable TIM9 peripheral
            loc_u32Temp = RCC->APB2ENR;
            loc_u32Temp &= 0xFFFEFFFF; // Set corresponding bit for TIM9
            RCC->APB2ENR = loc_u32Temp;
            break;

        case TIM10:
            // Enable TIM10 peripheral
            loc_u32Temp = RCC->APB2ENR;
            loc_u32Temp &= 0xFFFDFFFF; // Set corresponding bit for TIM10
            RCC->APB2ENR = loc_u32Temp;
            break;
        case TIM11:
            // Enable TIM11 peripheral
            loc_u32Temp = RCC->APB2ENR;
            loc_u32Temp &= 0xFFFBFFFF; // Set corresponding bit for TIM11
            RCC->APB2ENR = loc_u32Temp;
            break;
        case SYS_CFGCTRL:
            // Enable System Configuration Control peripheral
            loc_u32Temp = RCC->APB2ENR;
            loc_u32Temp &= 0xFFFFBFFF; // Set corresponding bit for System Configuration Control
            RCC->APB2ENR = loc_u32Temp;
            break;
        case SPI_1:
            // Enable SPI1 peripheral
            loc_u32Temp = RCC->APB2ENR;
            loc_u32Temp &= 0xFFFFEFFF; // Set corresponding bit for SPI1
            RCC->APB2ENR = loc_u32Temp;
            break;
        case SPI_4:
            // Enable SPI4 peripheral
            loc_u32Temp = RCC->APB2ENR;
            loc_u32Temp &= 0xFFFFDFFF; // Set corresponding bit for SPI4
            RCC->APB2ENR = loc_u32Temp;
            break;
        case ADC1:
            // Enable ADC1 peripheral
            loc_u32Temp = RCC->APB2ENR;
            loc_u32Temp &= 0xFFFFFEFF; // Set corresponding bit for ADC1
            RCC->APB2ENR = loc_u32Temp;
            break;
        case USART1:
            // Enable USART1 peripheral
            loc_u32Temp = RCC->APB2ENR;
            loc_u32Temp &= 0xFFFFFFEF; // Set corresponding bit for USART1
            RCC->APB2ENR = loc_u32Temp;
            break;
        case USART6:
            // Enable USART6 peripheral
            loc_u32Temp = RCC->APB2ENR;
            loc_u32Temp &= 0xFFFFFFDF; // Set corresponding bit for USART6
            RCC->APB2ENR = loc_u32Temp;
            break;
        case TIM1:
            // Enable TIM1 peripheral
            loc_u32Temp = RCC->APB2ENR;
            loc_u32Temp &= 0xFFFFFFFE; // Set corresponding bit for TIM1
            RCC->APB2ENR = loc_u32Temp;
            break;
        default :
        loc_u8ErrorStatus = Rcc_enuInvalidperName ;
            break;

         }

     }
     else if(Copy_u8State == CLK_ON  )
     {
    	 switch (Copy_u8Name)
    	        {
    	        case DMA1:
    	            // Enable DMA1 peripheral
    	            loc_u32Temp = RCC->AHB1ENR;
    	            loc_u32Temp |= 0x00200000; // Set corresponding bit for DMA1
    	            RCC->AHB1ENR = loc_u32Temp;
    	            break;
    	        case DMA2:
    	            // Enable DMA2 peripheral
    	            loc_u32Temp = RCC->AHB1ENR;
    	            loc_u32Temp |= 0x00400000; // Set corresponding bit for DMA2
    	            RCC->AHB1ENR = loc_u32Temp;
    	            break;
    	        case GPIO_A:
    	            // Enable GPIOA peripheral
    	            loc_u32Temp = RCC->AHB1ENR;
    	            loc_u32Temp |= 0x00000001; // Set corresponding bit for GPIOA
    	            RCC->AHB1ENR = loc_u32Temp;
    	            break;
    	        case GPIO_B:
    	            // Enable GPIOB peripheral
    	            loc_u32Temp = RCC->AHB1ENR;
    	            loc_u32Temp |= 0x00000002; // Set corresponding bit for GPIOB
    	            RCC->AHB1ENR = loc_u32Temp;
    	            break;
    	        case GPIO_C:
    	            // Enable GPIOC peripheral
    	            loc_u32Temp = RCC->AHB1ENR;
    	            loc_u32Temp |= 0x00000004; // Set corresponding bit for GPIOC
    	            RCC->AHB1ENR = loc_u32Temp;
    	            break;
    	        case GPIO_D:
    	            // Enable GPIOD peripheral
    	            loc_u32Temp = RCC->AHB1ENR;
    	            loc_u32Temp |= 0x00000008; // Set corresponding bit for GPIOD
    	            RCC->AHB1ENR = loc_u32Temp;
    	            break;
    	        case GPIO_E:
    	            // Enable GPIOE peripheral
    	            loc_u32Temp = RCC->AHB1ENR;
    	            loc_u32Temp |= 0x00000010; // Set corresponding bit for GPIOE
    	            RCC->AHB1ENR = loc_u32Temp;
    	            break;
    	        case GPIO_H:
    	            // Enable GPIOH peripheral
    	            loc_u32Temp = RCC->AHB1ENR;
    	            loc_u32Temp |= 0x00000080; // Set corresponding bit for GPIOH
    	            RCC->AHB1ENR = loc_u32Temp;
    	            break;
    	        case USB_OTG :
    	        	loc_u32Temp = RCC->AHB2ENR;
    	        	loc_u32Temp |= 0x00000080;
    	        	RCC->AHB2ENR = loc_u32Temp;
    	        	break;
    	        case I2C_1:
    	            // Enable I2C1 peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00200000; // Set corresponding bit for I2C1
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case I2C_2:
    	            // Enable I2C2 peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00400000; // Set corresponding bit for I2C2
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case I2C_3:
    	            // Enable I2C3 peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00800000; // Set corresponding bit for I2C3
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case USART2:
    	            // Enable USART2 peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00020000; // Set corresponding bit for USART2
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case SPI_2:
    	            // Enable SPI2 peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00004000; // Set corresponding bit for SPI2
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case SPI_3:
    	            // Enable SPI3 peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00008000; // Set corresponding bit for SPI3
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case TIM2:
    	            // Enable TIM2 peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00000001; // Set corresponding bit for TIM2
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case TIM3:
    	            // Enable TIM3 peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00000002; // Set corresponding bit for TIM3
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case TIM4:
    	            // Enable TIM4 peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00000004; // Set corresponding bit for TIM4
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case TIM5:
    	            // Enable TIM5 peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00000008; // Set corresponding bit for TIM5
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case WINDOW_WD:
    	            // Enable Window Watchdog peripheral
    	            loc_u32Temp = RCC->APB1ENR;
    	            loc_u32Temp |= 0x00000800; // Set corresponding bit for Window Watchdog
    	            RCC->APB1ENR = loc_u32Temp;
    	            break;
    	        case TIM9:
    	            // Enable TIM9 peripheral
    	            loc_u32Temp = RCC->APB2ENR;
    	            loc_u32Temp |= 0x00010000; // Set corresponding bit for TIM9
    	            RCC->APB2ENR = loc_u32Temp;
    	            break;

    	        case TIM10:
    	            // Enable TIM10 peripheral
    	            loc_u32Temp = RCC->APB2ENR;
    	            loc_u32Temp |= 0x00020000; // Set corresponding bit for TIM10
    	            RCC->APB2ENR = loc_u32Temp;
    	            break;
    	        case TIM11:
    	            // Enable TIM11 peripheral
    	            loc_u32Temp = RCC->APB2ENR;
    	            loc_u32Temp |= 0x00040000; // Set corresponding bit for TIM11
    	            RCC->APB2ENR = loc_u32Temp;
    	            break;
    	        case SYS_CFGCTRL:
    	            // Enable System Configuration Control peripheral
    	            loc_u32Temp = RCC->APB2ENR;
    	            loc_u32Temp |= 0x00004000; // Set corresponding bit for System Configuration Control
    	            RCC->APB2ENR = loc_u32Temp;
    	            break;
    	        case SPI_1:
    	            // Enable SPI1 peripheral
    	            loc_u32Temp = RCC->APB2ENR;
    	            loc_u32Temp |= 0x00001000; // Set corresponding bit for SPI1
    	            RCC->APB2ENR = loc_u32Temp;
    	            break;
    	        case SPI_4:
    	            // Enable SPI4 peripheral
    	            loc_u32Temp = RCC->APB2ENR;
    	            loc_u32Temp |= 0x00002000; // Set corresponding bit for SPI4
    	            RCC->APB2ENR = loc_u32Temp;
    	            break;
    	        case ADC1:
    	            // Enable ADC1 peripheral
    	            loc_u32Temp = RCC->APB2ENR;
    	            loc_u32Temp |= 0x00000100; // Set corresponding bit for ADC1
    	            RCC->APB2ENR = loc_u32Temp;
    	            break;
    	        case USART1:
    	            // Enable USART1 peripheral
    	            loc_u32Temp = RCC->APB2ENR;
    	            loc_u32Temp |= 0x00000010; // Set corresponding bit for USART1
    	            RCC->APB2ENR = loc_u32Temp;
    	            break;
    	        case USART6:
    	            // Enable USART6 peripheral
    	            loc_u32Temp = RCC->APB2ENR;
    	            loc_u32Temp |= 0x00000020; // Set corresponding bit for USART6
    	            RCC->APB2ENR = loc_u32Temp;
    	            break;
    	        case TIM1:
    	            // Enable TIM1 peripheral
    	            loc_u32Temp = RCC->APB2ENR;
    	            loc_u32Temp |= 0x00000001; // Set corresponding bit for TIM1
    	            RCC->APB2ENR = loc_u32Temp;
    	            break;
    	        default :
    	        	loc_u8ErrorStatus = Rcc_enuInvalidperName ;
    	        	break;
    	         }
             }
       else
           {
    	    loc_u8ErrorStatus = Rcc_enuInvalidClkState ;
           }

 return loc_u8ErrorStatus ;
 }

 Rcc_ErrorStatus_t Rcc_SetPreScaler(u8 Copy_u8Name , u8 Copy_u8Value)
 {
	u8 loc_u8ErrorStatus =  Rcc_enuSucceded;
	u32 loc_u32Temp = RCC->CFGR ;
    if (Copy_u8Name ==  MCO1_PRE )
    {
        // Check if the prescaler name is for MCO1
        // Apply mask to clear previous prescaler value for MCO1
        loc_u32Temp &= MCO1_MASK ;
        // Set the new prescaler value for MCO1
        loc_u32Temp |= Copy_u8Value << 24 ;
    }
    else if (Copy_u8Name ==  MCO2_PRE)
    {
        // Check if the prescaler name is for MCO2
        // Apply mask to clear previous prescaler value for MCO2
        loc_u32Temp &= MCO2_MASK ;
        // Set the new prescaler value for MCO2
        loc_u32Temp |= Copy_u8Value << 27 ;
    }
    else if (Copy_u8Name ==  AHP_PRE)
    {
        // Check if the prescaler name is for AHP
        // Apply mask to clear previous prescaler value for AHP
        loc_u32Temp &= AHP_MASK ;
        // Set the new prescaler value for AHP
        loc_u32Temp |= Copy_u8Value << 4 ;
    }
    else if (Copy_u8Name ==  APB1_PRE)
    {
        // Check if the prescaler name is for APB1
        // Apply mask to clear previous prescaler value for APB1
        loc_u32Temp &= APB1_MASK ;
        // Set the new prescaler value for APB1
        loc_u32Temp |= Copy_u8Value << 10 ;
    }
    else if (Copy_u8Name ==  APB2_PRE)
    {
        // Check if the prescaler name is for APB2
        // Apply mask to clear previous prescaler value for APB2
        loc_u32Temp &= APB2_MASK ;
        // Set the new prescaler value for APB2
        loc_u32Temp |= Copy_u8Value << 13 ;
    }
    else if (Copy_u8Name ==  HSE_PRE)
    {
        // Check if the prescaler name is for HSE
        // Apply mask to clear previous prescaler value for HSE
        loc_u32Temp &=  HSE_MASK  ;
        // Set the new prescaler value for HSE
        loc_u32Temp |= Copy_u8Value << 16 ;
    }
    else
    {
        // If the provided prescaler name is invalid, set error status
        loc_u8ErrorStatus = Rcc_ennInvalidpresclrname ;
    }

    RCC->CFGR = loc_u32Temp ;

    return loc_u8ErrorStatus;
 }
 Rcc_ErrorStatus_t Rcc_setPLLCfg   (u8 copy_u8ClkSrc  , u8 Copy_u8Value)
 {
	 u8 loc_u8ErrorStatus = Rcc_enuSucceded;
     u32 Copy_u32Temp = RCC-> CR;
     Copy_u32Temp &= 0x01000000;

     if (Copy_u32Temp == 0x01000000)
     {
    	 loc_u8ErrorStatus = Rcc_enuCantCfgPllOn ;
     }

      Copy_u32Temp = RCC->PLLCFGR ;
     if ( copy_u8ClkSrc ==  HSE_PLLCLK_SRC )
     {
    	 Copy_u32Temp &=PLL_MASK  ;
    	 Copy_u32Temp |=0x1 << 22 ;
    	 switch (Copy_u8Value)
    	 {
    	 case PLLCLK_30 :
    		 Copy_u32Temp |= 0x14 ;       //M
    		 Copy_u32Temp |= 0xC8 << 6 ;  //N
    		 Copy_u32Temp |= 0x8  << 16;  //P
    		 break ;
    	 case PLLCLK_45 :
    		 Copy_u32Temp |= 0x14 ;       //M
    	     Copy_u32Temp |= 0x12C << 6 ;  //N
    	     Copy_u32Temp |= 0x8  << 16;  //P
    	     break ;
       	 case PLLCLK_60 :
        	 Copy_u32Temp |= 0xF ;       //M
        	 Copy_u32Temp |= 0x12C << 6 ;  //N
        	 Copy_u32Temp |= 0x8  << 16;  //P
        	 break ;
         case PLLCLK_84 :
        	 Copy_u32Temp |= 0xF ;       //M
        	 Copy_u32Temp |= 0x3C00 << 6 ;  //N
        	 Copy_u32Temp |= 0x8    << 16;  //P
        	 break ;
         }





     }



	 return loc_u8ErrorStatus ;





