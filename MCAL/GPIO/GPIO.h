/**
  ******************************************************************************
  * @file    gpio_driver.h
  * @brief   GPIO driver for STM32F401 microcontroller
  ******************************************************************************
  * @author   Mohamed Ahmed Fouad
  * @date     2024-02-13
  ******************************************************************************
  * @details
  * This GPIO driver provides functions to initialize GPIO pins, set or clear
  * specific pins, read pin states, and deinitialize GPIO peripherals on the
  * STM32F401 microcontroller. It is designed to work with the STM32F401 series
  * of microcontrollers and provides an easy-to-use interface for controlling
  * GPIO pins for various applications.
  ******************************************************************************
  */
#ifndef GPIO_H_
#define GPIO_H_
#include "std_types.h"
/*-------------------------------------------------------*PORTS*--------------------------------------------------------------------*/
#define PORT_A	0
#define PORT_B	1
#define PORT_C	2
#define PORT_D	3
#define PORT_E	4
#define PORT_H	5
/**********************************************************GPIO Pins*****************************************************************/
#define GPIO_PIN_0   0   // Pin 0
#define GPIO_PIN_1   1   // Pin 1
#define GPIO_PIN_2   2   // Pin 2
#define GPIO_PIN_3   3   // Pin 3
#define GPIO_PIN_4   4   // Pin 4
#define GPIO_PIN_5   5   // Pin 5
#define GPIO_PIN_6   6   // Pin 6
#define GPIO_PIN_7   7   // Pin 7
#define GPIO_PIN_8   8   // Pin 8
#define GPIO_PIN_9   9   // Pin 9
#define GPIO_PIN_10  10  // Pin 10
#define GPIO_PIN_11  11  // Pin 11
#define GPIO_PIN_12  12  // Pin 12
#define GPIO_PIN_13  13  // Pin 13
#define GPIO_PIN_14  14  // Pin 14
#define GPIO_PIN_15  15  // Pin 15
/*--------------------------------------------------------*Pin Modes*---------------------------------------------------------------*/
#define GPIO_INPUT      0x0  // Input (reset state)
#define GPIO_OUTPUT     0x1  // General purpose output mode
#define GPIO_AF_M       0x2  // Alternate function mode
#define GPIO_ANALOG     0x3  // Analog mode
/*--------------------------------------------------------*Output Type*--------------------------------------------------------------*/
#define GPIO_OTYPE_PUSHPULL    0x0 // Output push-pull (reset state)
#define GPIO_OTYPE_OPENDRAIN   0x1  // Output open-drain
/*---------------------------------------------------------*Input*-------------------------------------------------------------------*/
#define GPIO_PULL_NO     0x0   // No pull-up, pull-down
#define GPIO_PULL_UP     0x1   // Pull-up
#define GPIO_PULL_DOWN   0x2   // Pull-down
/*-------------------------------------------------------- *Speed*--------------------------------------------------------------------*/
#define GPIO_SPEED_LOW         0x0   // Low speed
#define GPIO_SPEED_MEDIUM      0x1   // Medium speed
#define GPIO_SPEED_HIGH        0x2   // High speed
#define GPIO_SPEED_VERY_HIGH   0x3   // Very high speed
/*--------------------------------------------------------*AF Pin*--------------------------------------------------------------------*/
#define GPIO_AFR_AF0    0x00000000   // Alternate function 0
#define GPIO_AFR_AF1    0x00000001   // Alternate function 1
#define GPIO_AFR_AF2    0x00000002   // Alternate function 2
#define GPIO_AFR_AF3    0x00000003   // Alternate function 3
#define GPIO_AFR_AF4    0x00000004   // Alternate function 4
#define GPIO_AFR_AF5    0x00000005   // Alternate function 5
#define GPIO_AFR_AF6    0x00000006   // Alternate function 6
#define GPIO_AFR_AF7    0x00000007   // Alternate function 7
#define GPIO_AFR_AF8    0x00000008   // Alternate function 8
#define GPIO_AFR_AF9    0x00000009   // Alternate function 9
#define GPIO_AFR_AF10   0x0000000A   // Alternate function 10
#define GPIO_AFR_AF11   0x0000000B   // Alternate function 11
#define GPIO_AFR_AF12   0x0000000C   // Alternate function 12
#define GPIO_AFR_AF13   0x0000000D   // Alternate function 13
#define GPIO_AFR_AF14   0x0000000E   // Alternate function 14
#define GPIO_AFR_AF15   0x0000000F   // Alternate function 15
/*-----------------------------------------------------------*Pin Value*------------------------------------------------------------------*/
#define LOGIC_HIGH   1
#define LOGIC_LOW    0

typedef struct
{
   u32    GPIO_Port ;
   u32    GPIO_Pin ;
   u32    GPIO_Speed ;
   u32    GPIO_Direction ;
   u32    GPIO_Mode ;
   u32    GPIO_AF ;
   u32    GPIO_AF_Mode ;

}GpioPinCfg_t;
typedef enum
{
    GPIO_OK = 0,
	GPIO_enuInvalidPortNum,
	GPIO_enuInvalidPinNum,
	GPIO_enuInvalidMode,
	GPIO_enuInvalidAF,
	GPIO_enuInvalidSpeed,
	GPIO_enuNullPtr,
    GPIO_NOK
} GPIO_ErrorStatus_t;


/**
  * @brief  Initializes a GPIO pin.
  * @param  Copy_StrData: Structure containing the GPIO pin configuration.
  * @retval GPIO_ErrorStatus_t: Indicates the status of the GPIO initialization.
  */
GPIO_ErrorStatus_t GPIO_Init(GpioPinCfg_t  *Copy_StrData);

/**
  * @brief  Sets the value of a GPIO pin.
  * @param  Copy_PortNum: The index of the GPIO port (e.g., PORT_A, PORT_B, etc.).
  * @param  Copy_PinNum: The pin number within the GPIO port.
  * @param  Copy_PinValue: The value to set for the GPIO pin (0 or 1).
  * @retval GPIO_ErrorStatus_t: Indicates the status of the GPIO pin value setting.

  */
GPIO_ErrorStatus_t GPIO_SetPinValue(u32 Copy_PortNum, u32 Copy_PinNum, u32 Copy_PinValue);

/**
  * @brief  Gets the value of a GPIO pin.
  * @param  Copy_PortNum: The index of the GPIO port (e.g., PORT_A, PORT_B, etc.).
  * @param  Copy_PinNum: The pin number within the GPIO port.
  * @param  Add_PinValue: Pointer to a variable to store the pin value.
  * @retval GPIO_ErrorStatus_t: Indicates the status of the GPIO pin value reading.
  *
  */
GPIO_ErrorStatus_t GPIO_GetPinValue(u32 Copy_PortNum, u32 Copy_PinNum, u32 *Add_PinValue);
#endif /* GPIO_H_ */
