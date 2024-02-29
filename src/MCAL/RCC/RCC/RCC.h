/**
  ******************************************************************************
  * @file    rcc.h
  * @brief   Header file for Reset and Clock Control (RCC) configuration.
  ******************************************************************************
  * @attention
  *
  * This file contains function prototypes and macros related to configuring
  * the RCC peripheral on the STM32F401 microcontroller. These functions are
  * used to initialize the system clock and perform other RCC-related tasks.
  *
  * @note
  *   - Refer to the STM32F401 reference manual and datasheet for detailed information.
  ******************************************************************************
  */

#include "../lib/std_types.h"
#include "RCCCfg.h"

/** @brief Structure representing the RCC peripheral registers. */
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


typedef enum
{
   Rcc_enuInvalidClkName,  // Error: Invalid clock name
   Rcc_enuInvalidClkState, // Error: Invalid clock state
   Rcc_enuSucceded,        // Success: Operation succeeded
   Rcc_enuCantCloseClk,    // Error: Unable to close the clock
   Rcc_enuCLkNotReady,     // Error: Clock is not ready
   Rcc_enuInvalidperName,
   Rcc_ennInvalidpresclrname,
   Rcc_enuCantCfgPllOn,
} Rcc_ErrorStatus_t;


#define HSI_CLK 0    // High-Speed Internal (HSI) clock index
#define HSE_CLK 1    // High-Speed External (HSE) clock index
#define PLL_CLK 2    // PLL (Phase-Locked Loop) clock index

#define CLK_OFF 0    // Clock is off
#define CLK_ON  1    // Clock is on
/*--------------------------------------------------MASKS---------------------------------------------------------*/
// Mask to clear the SW bits in RCC_CFGR register
#define CFGR_SW_MASK  0xFFFFFFFC
#define MCO1_MASK     0xF8FFFFFF
#define MCO2_MASK     0xC7FFFFFF
#define AHP_MASK      0xFFFFFF0F
#define APB1_MASK     0xFFFFE3FF
#define APB2_MASK     0xFFFF1FFF
#define HSE_MASK      0xFFE0FFFF
#define PLL_MASK      0xF0BC7000
/*--------------------------------------------------PERIPHERAL INDEXES---------------------------------------------------------*/
#define DMA1        0    // Direct Memory Access 1
#define DMA2        1    // Direct Memory Access 2
#define GPIO_A      2    // General-Purpose Input/Output Port A
#define GPIO_B      3    // General-Purpose Input/Output Port B
#define GPIO_C      4    // General-Purpose Input/Output Port C
#define GPIO_D      5    // General-Purpose Input/Output Port D
#define GPIO_E      6    // General-Purpose Input/Output Port E
#define GPIO_H      7    // General-Purpose Input/Output Port h
#define USB_OTG     8    // USB On-The-Go
#define PW_INTF     9    // Power Interface
#define I2C_1      10    // Inter-Integrated Circuit 1
#define I2C_2      11    // Inter-Integrated Circuit 2
#define I2C_3      12    // Inter-Integrated Circuit 3
#define USART1     13    // Universal Synchronous/Asynchronous Receiver/Transmitter 1
#define USART2     14    // Universal Synchronous/Asynchronous Receiver/Transmitter 2
#define SPI_1      15    // Serial Peripheral Interface 1
#define SPI_2      16    // Serial Peripheral Interface 2
#define SPI_3      17    // Serial Peripheral Interface 3
#define SPI_4      18    // Serial Peripheral Interface 4
#define TIM1       19    // Timer 1
#define TIM2       20    // Timer 2
#define TIM3       21    // Timer 3
#define TIM4       22    // Timer 4
#define TIM5       23    // Timer 5
#define TIM9       24    // Timer 9
#define TIM10      25    // Timer 10
#define TIM11      26    // Timer 11
#define USART6     27    // Universal Synchronous/Asynchronous Receiver/Transmitter 6
#define SYS_CFGCTRL 28   // System Configuration Control
#define ADC1       29    // Analog-to-Digital Converter 1
#define WINDOW_WD  30    // Window Watchdog
/*---------------------------------------------------------------------------*prescalers index *-----------------------------------------------------*/
#define MCO1_PRE  0   // Index for MCO1 prescaler
#define MCO2_PRE  1   // Index for MCO2 prescaler
#define AHP_PRE   2   // Index for AHP prescaler
#define APB1_PRE  3   // Index for APB1 prescaler
#define APB2_PRE  4   // Index for APB2 prescaler
#define HSE_PRE   5   // Index for HSE prescaler

/*---------------------------------------------------------------------------*prescalers values *-----------------------------------------------------*/
#define MCO1_PRE_2   0x4   // Prescaler value for MCO1 = 2
#define MCO1_PRE_3   0x5   // Prescaler value for MCO1 = 3
#define MCO1_PRE_4   0x6   // Prescaler value for MCO1 = 4
#define MCO1_PRE_5   0x7   // Prescaler value for MCO1 = 5

#define AHP_PRE_2    0x8   // Prescaler value for AHP = 2
#define AHP_PRE_4    0x9   // Prescaler value for AHP = 4
#define AHP_PRE_8    0xA   // Prescaler value for AHP = 8
#define AHP_PRE_16   0xB   // Prescaler value for AHP = 16
#define AHP_PRE_64   0xC   // Prescaler value for AHP = 64
#define AHP_PRE_128  0xD   // Prescaler value for AHP = 128
#define AHP_PRE_256  0xE   // Prescaler value for AHP = 256
#define AHP_PRE_512  0xF   // Prescaler value for AHP = 512

#define APB1_PRE_2   0x4   // Prescaler value for APB1 = 2
#define APB1_PRE_4   0x5   // Prescaler value for APB1 = 4
#define APB1_PRE_8   0x6   // Prescaler value for APB1 = 8
#define APB1_PRE_16  0x7   // Prescaler value for APB1 = 16

#define APB2_PRE_2   0x4   // Prescaler value for APB2 = 2
#define APB2_PRE_4   0x5   // Prescaler value for APB2 = 4
#define APB2_PRE_8   0x6   // Prescaler value for APB2 = 8
#define APB2_PRE_16  0x7   // Prescaler value for APB2 = 16

#define HSE_PRE_2    0x2   // Prescaler value for HSE = 2
#define HSE_PRE_3    0x3   // Prescaler value for HSE = 3
#define HSE_PRE_4    0x4   // Prescaler value for HSE = 4
#define HSE_PRE_5    0x5   // Prescaler value for HSE = 5
#define HSE_PRE_6    0x6   // Prescaler value for HSE = 6
#define HSE_PRE_7    0x7   // Prescaler value for HSE = 7
#define HSE_PRE_8    0x8   // Prescaler value for HSE = 8
#define HSE_PRE_9    0x9   // Prescaler value for HSE = 9
#define HSE_PRE_10   0xA   // Prescaler value for HSE = 10
#define HSE_PRE_11   0xB   // Prescaler value for HSE = 11
#define HSE_PRE_12   0xC   // Prescaler value for HSE = 12
#define HSE_PRE_13   0xD   // Prescaler value for HSE = 13
#define HSE_PRE_14   0xE   // Prescaler value for HSE = 14
#define HSE_PRE_15   0xF   // Prescaler value for HSE = 15
#define HSE_PRE_16   0x10  // Prescaler value for HSE = 16
#define HSE_PRE_17   0x11  // Prescaler value for HSE = 17
#define HSE_PRE_18   0x12  // Prescaler value for HSE = 18
#define HSE_PRE_19   0x13  // Prescaler value for HSE = 19
#define HSE_PRE_20   0x14  // Prescaler value for HSE = 20
#define HSE_PRE_21   0x15  // Prescaler value for HSE = 21
#define HSE_PRE_22   0x16  // Prescaler value for HSE = 22
#define HSE_PRE_23   0x17  // Prescaler value for HSE = 23
#define HSE_PRE_24   0x18  // Prescaler value for HSE = 24
#define HSE_PRE_25   0x19  // Prescaler value for HSE = 25
#define HSE_PRE_26   0x1A  // Prescaler value for HSE = 26
#define HSE_PRE_27   0x1B  // Prescaler value for HSE = 27
#define HSE_PRE_28   0x1C  // Prescaler value for HSE = 28
#define HSE_PRE_29   0x1D  // Prescaler value for HSE = 29
#define HSE_PRE_30   0x1E  // Prescaler value for HSE = 30
#define HSE_PRE_31   0x1F  // Prescaler value for HSE = 31
/*------------------------------------------------------*PLL CFG *------------------------------------------------------------*/
#define HSE_PLLCLK_SRC  0
#define HSI_PLLCLK_SRC  1


/*-------------------------*PLL CLK OPTIONS*----------------------------*/
#define PLLCLK_30  0
#define PLLCLK_45  1
#define PLLCLK_60  2
#define PLLCLK_84  3

/**
  ******************************************************************************
  * @file    rcc_config.h
  * @brief   RCC Clock Control API
  ******************************************************************************
  * @attention
  *
  * This API provides functions for enabling or disabling various clocks
  * in the Reset and Clock Control (RCC) peripheral of a microcontroller,
  * such as the STM32 series.
  *
  ******************************************************************************
  * @param   Copy_u8ClkName: Clock name to be configured.
  *
  * @param   Copy_u8ClkState: Desired clock state.
  *            - Options: RCC_CLOCK_ON, RCC_CLOCK_OFF
  * @retval  Rcc_ErrorStatus_t: Status indicating success or error.
  *
  ******************************************************************************
  * @note
  *   - The API allows controlling the state (ON or OFF) of various clocks.
  *   - 'Copy_u8ClkName' parameter specifies the clock domain to be configured.
  *   - 'Copy_u8ClkState' parameter sets the desired state of the clock (ON or OFF).
  ******************************************************************************
  */
Rcc_ErrorStatus_t Rcc_ClkOnOff(u8 Copy_u8ClkName, u8 Copy_u8ClkState);
/**
  ******************************************************************************
  * @brief  Sets the system clock to the specified clock source.
  ******************************************************************************
  * | Parameter     | Description                                   |
  * |---------------|-----------------------------------------------|
  * | Copy_u8ClkName| Clock name to be set as the system clock.     |
  * |               | Options: HSI_CLK, HSE_CLK, PLL_CLK            |
  ******************************************************************************
  * @retval Rcc_ErrorStatus_t: Status indicating success or error.
  ******************************************************************************
  * | Return Value               | Description                             |
  * |----------------------------|-----------------------------------------|
  * | Rcc_enuSucceded            | Operation succeeded.                    |
  * | Rcc_enuInvalidClkName      | Specified clock name is invalid.        |
  * | Rcc_enuClkNotReady         | Specified clock is not ready.           |
  ******************************************************************************
  * @note
  *   - To set a clock as the system clock, it must be turned on and ready.
  *   - This function checks if the specified clock is ready and then sets
  *     it as the system clock. If the clock is not ready or an invalid clock
  *     name is provided, it returns an appropriate error status.
  ******************************************************************************
  */

Rcc_ErrorStatus_t Rcc_SetSysClk(u8 Copy_u8ClkName);
/**
  ******************************************************************************
  * @brief  Enables or disables a peripheral.
  ******************************************************************************
  * | Parameter     | Description                                   |
  * |---------------|-----------------------------------------------|
  * | Copy_u8Name   | Peripheral to be enabled or disabled.         |
  * |               | Options: DMA1, DMA2, GPIO_A, GPIO_B, ...      |
  * | Copy_u8State  | State to set for the peripheral.              |
  * |               | Options: CLK_ON (enable), CLK_OFF (disable)  |
  ******************************************************************************
  * @retval Rcc_ErrorStatus_t: Status indicating success or error.
  ******************************************************************************
  * | Return Value            | Description                            |
  * |-------------------------|----------------------------------------|
  * | Rcc_enuSucceded         | Operation succeeded.                   |
  * | Rcc_enuInvalidClkName   | Specified peripheral name is invalid.  |
  ******************************************************************************
  * @note
  *   - This function enables or disables a peripheral based on the provided
  *     peripheral name and state.
  ******************************************************************************
  */


Rcc_ErrorStatus_t Rcc_PeripheralOnOff(u8 Copy_u8Name , u8 Copy_u8State );

/**
  ******************************************************************************
  * @brief  Sets the prescaler value for a specific peripheral.
  ******************************************************************************
  * | Parameter     | Description                                   |
  * |---------------|-----------------------------------------------|
  * | Copy_u8Name   | Peripheral name to set the prescaler for.     |
  * |               | Options: Refer to the peripheral names.       |
  * | Copy_u8Value  | Value to set as the prescaler for the peripheral.|
  * |               | Value range depends on the specific peripheral.|
  ******************************************************************************
  * @retval Rcc_ErrorStatus_t: Status indicating success or error.
  ******************************************************************************
  * | Return Value               | Description                             |
  * |----------------------------|-----------------------------------------|
  * | Rcc_enuSucceded            | Operation succeeded.                    |
  * | Rcc_enuInvalidClkName      | Specified peripheral name is invalid.   |
  * | Rcc_enuInvalidValue        | Specified prescaler value is invalid.   |
  ******************************************************************************
  * @note
  *   - This function sets the prescaler value for a specific peripheral.
  *   - The valid range of prescaler values depends on the specific peripheral.
  *   - If the specified peripheral name is invalid or the prescaler value is
  *     out of range, it returns an appropriate error status.
  ******************************************************************************
  */

Rcc_ErrorStatus_t Rcc_SetPreScaler(u8 Copy_u8Name , u8 Copy_u8Value);
/**
  ******************************************************************************
  * @brief  Adjusts the PLL configuration
  ******************************************************************************
  * | Parameter     | Description                                   |
  * |---------------|-----------------------------------------------|
  * | copy_u8ClkSrc | Source of the PLL clock.                      |
  * |               | Options: HSE_CLK, HSI_CLK                    |
  * | Copy_u8Value  | Desired value for the PLL clock.              |
  * |               | The interpretation of this value depends on   |
  * |               | the chosen clock source.                      |
  ******************************************************************************
  * @retval Rcc_ErrorStatus_t: Status indicating success or error.
  ******************************************************************************
  * | Return Value               | Description                             |
  * |----------------------------|-----------------------------------------|
  * | Rcc_enuSucceded            | Operation succeeded.                    |
  * | Rcc_enuInvalidClkName      | Specified name is invalid.              |
  * | Rcc_enuInvalidValue        | Specified configuration value is invalid|
  ******************************************************************************
  * @note
  *   - This function adjusts the PLL configuration .
  *   - The valid range and interpretation of the configuration value depend
  *     on the chosen PLL clock source (HSE or HSI).
  ******************************************************************************
  */

Rcc_ErrorStatus_t Rcc_setPLLCfg(u8 copy_u8ClkSrc  , u8 Copy_u8Value);

















