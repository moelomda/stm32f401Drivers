/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   GPIO driver implementation for STM32F401 microcontroller
  ******************************************************************************
  * @author   Mohamed Ahmed Fouad
  * @date     2024-02-13
  ******************************************************************************
  * @details
  * This file contains the implementation of the GPIO driver for the STM32F401
  * microcontroller. It provides functions to initialize GPIO pins, set or clear
  * specific pins, read pin states, and deinitialize GPIO peripherals. The driver
  * is designed to work with the STM32F401 series of microcontrollers and offers
  * an easy-to-use interface for controlling GPIO pins for various applications.
  ******************************************************************************
  */
#include "GPIO.h"
#define NUM_PORTS 6
#define	NULL	            (void*)0
#define GPIOA				((volatile Gpio_strRegister* const) 0x40020000)
#define GPIOB				((volatile Gpio_strRegister* const) 0x40020400)
#define GPIOC				((volatile Gpio_strRegister* const) 0x40020800)
#define GPIOD				((volatile Gpio_strRegister* const) 0x40020C00)
#define GPIOE				((volatile Gpio_strRegister* const) 0x40021000)
#define GPIOH				((volatile Gpio_strRegister* const) 0x40021C00)
#define FOUR_BITS_CLEAR  1<<4

#define FOUR_BITS    4
typedef struct
{
	volatile u32 Moder;
	volatile u32 Otyper;
	volatile u32 Ospeedr;
	volatile u32 Pupdr;
	volatile u32 Idr;
	volatile u32 Odr;
	volatile u32 Bsrr;
	volatile u32 Lckr;
	volatile u32 Afrl;
}Gpio_strRegister;

volatile Gpio_strRegister * const GPIO[NUM_PORTS] = {GPIOA,GPIOB ,GPIOC,GPIOD,GPIOE,GPIOH};
GPIO_ErrorStatus_t GPIO_Init(GpioPinCfg_t  *Copy_StrData)
{
    u8 Loc_ErrorStatus = GPIO_OK;
    u32 Loc_PinDirec   = Copy_StrData-> GPIO_Direction;
    u32 Loc_PinMode    = Copy_StrData -> GPIO_Mode;
    u32 Loc_PinSpeed   = Copy_StrData-> GPIO_Speed;
    u32 Loc_PinNum     = Copy_StrData -> GPIO_Pin;
    u32 Loc_Temp       = GPIO[Copy_StrData-> GPIO_Port]->Moder;

    if (Copy_StrData->GPIO_Port > NUM_PORTS - 1 )
    {
        Loc_ErrorStatus = GPIO_enuInvalidPortNum;
    }

    else if (Copy_StrData->GPIO_Pin > GPIO_PIN_15 )
    {
        Loc_ErrorStatus = GPIO_enuInvalidPinNum;
    }
    else if (Copy_StrData->GPIO_Direction > GPIO_ANALOG )
    {
        Loc_ErrorStatus = GPIO_enuInvalidMode;
    }
    else if (Copy_StrData->GPIO_Speed > GPIO_SPEED_VERY_HIGH )
    {
        Loc_ErrorStatus = GPIO_enuInvalidSpeed;
    }
    else
    {
        // Clear and set the pin direction in Moder register
        Loc_Temp &= ~(0x3 << (2* Loc_PinNum));
        Loc_Temp |= Loc_PinDirec << Loc_PinNum * 2;
        GPIO[Copy_StrData->GPIO_Port]->Moder = Loc_Temp;
        // Clear and set the pin mode in Otyper register
        if(Copy_StrData->GPIO_Direction == GPIO_OUTPUT)
        {
        Loc_Temp = GPIO[Copy_StrData->GPIO_Port]->Otyper;
        Loc_Temp &= ~(1<<Loc_PinNum);
         Loc_Temp |= Loc_PinMode << Loc_PinNum;
        GPIO[Copy_StrData->GPIO_Port]->Otyper = Loc_Temp;
        }
        // Clear and set the pin pull-up/pull-down in Pupdr register
        else
        {
        Loc_Temp = GPIO[Copy_StrData->GPIO_Port]->Pupdr;
        Loc_Temp &= ~(0x3 << (2* Loc_PinNum));
        Loc_Temp |= Loc_PinMode << Loc_PinNum * 2;
        GPIO[Copy_StrData->GPIO_Port]->Pupdr = Loc_Temp;
        }
        // Clear and set the pin output speed in Ospeedr register
        Loc_Temp = GPIO[Copy_StrData->GPIO_Port]->Ospeedr;
        Loc_Temp &= ~(0x3 << (2* Loc_PinNum));
        Loc_Temp |= Loc_PinSpeed << Loc_PinNum * 2;
        GPIO[Copy_StrData->GPIO_Port]->Ospeedr = Loc_Temp;
    }
      return Loc_ErrorStatus;
}
GPIO_ErrorStatus_t GPIO_SetPinValue(u32 Copy_PortNum, u32 Copy_PinNum, u32 Copy_PinValue)
{
	 u8 Loc_ErrorStatus = GPIO_OK;
	 if (Copy_PortNum > NUM_PORTS - 1 )
	    {
	        Loc_ErrorStatus = GPIO_enuInvalidPortNum;
	    }
	    else if (Copy_PinNum> GPIO_PIN_15 )
	    {
	        Loc_ErrorStatus = GPIO_enuInvalidPinNum;
	    }
	    else
	    {
	    	if (Copy_PinValue == LOGIC_HIGH)
	    	{
	    	GPIO[Copy_PortNum]->Bsrr |=  1 << (Copy_PinNum);
	    	}
	    	else
	    	{
	        GPIO[Copy_PortNum]->Bsrr |=  1 << (Copy_PinNum+16);
	    	}
        }
  return Loc_ErrorStatus ;
}
GPIO_ErrorStatus_t GPIO_GetPinValue(u32 Copy_PortNum, u32 Copy_PinNum, u32 *Add_PinValue)
{
	 u8 Loc_ErrorStatus = GPIO_OK;
		 if (Copy_PortNum > NUM_PORTS - 1 )
		    {
		        Loc_ErrorStatus = GPIO_enuInvalidPortNum;
		    }
		    else if (Copy_PinNum> GPIO_PIN_15 )
		    {
		        Loc_ErrorStatus = GPIO_enuInvalidPinNum;
		    }
		    else if  (Add_PinValue == NULL )
		    {
		    	Loc_ErrorStatus = GPIO_enuNullPtr ;
		    }
		    else
		    {
		          u32 Loc_TempReg = GPIO[Copy_PortNum]->Idr ;
		    	 *Add_PinValue = (Loc_TempReg & (1 <<  Copy_PinNum ))>> Copy_PinNum;
		    }
		  return Loc_ErrorStatus ;
}
