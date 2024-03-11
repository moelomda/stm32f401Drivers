/*************************************************************
 *                                                           *
 *                    SYSTICK.h                              *
 *                    Header file for SYSTICK module         *
 *                                                           *
 *************************************************************
 *                                                           *
 *                                                           *
 *       Author: Mohamed Elomda                              *
 *                                                           *
 ************************************************************* */

#ifndef SYSTICK_H_
#define SYSTICK_H_
#include "std_types.h"

/**
 * @brief   Clock source for the SysTick timer: Processor clock.
 */
#define PROCESSOR_CLK     1

/**
 * @brief   Clock source for the SysTick timer: AHB divider clock.
 */
#define AHB_DEV8_CLK      0

/**
 * @brief   Option to enable SysTick exception.
 */
#define SYSTICK_EXCEP_EN  1

/**
 * @brief   Option to disable SysTick exception.
 */
#define SYSTICK_EXCEP_DIS 0

/**
 * @brief   Enumeration for SysTick error status.
 */
/* Define periodicity options for SYSTICK timer */
#define PERIODICITY_ONETIME  0 /**< One-time execution */
#define PERIODICITY_AUTO     1 /**< Automatic (periodic) execution */
typedef enum
{
    SYSTICK_enuInvalidClkSrc,  /**< Invalid clock source error. */
    SYSTICK_enuInvalidOption,  /**< Invalid option error. */
    SYSTICK_enuInvalidValue,   /**< Invalid value error. */
    SYSTICK_enuNullPtr,        /**< Null pointer error. */
    SYSTICK_enuSuccess         /**< Success status. */
} SYSTICK_ErrorStatus_t;

typedef void(*SYSTICK_Cbf_t)(void);
/**
 * @brief   Sets the clock source for the SysTick timer.
 * @param   Copy_ClkName: The clock source to be used (0: External reference clock, 1: Processor clock).
 * @return  Status of the operation (success/error).
 */
SYSTICK_ErrorStatus_t SYSTICK_SelectClkSrc(u32 Copy_ClkName);

/**
 * @brief   Controls the SysTick interrupt.
 * @param   Copy_Option: Option to control the interrupt (0: Disable interrupt, 1: Enable interrupt).
 * @return  Status of the operation (success/error).
 */
SYSTICK_ErrorStatus_t SYSTICK_CtrlInterrupt(u32 Copy_Option);

/**
 * @brief   Sets the time value for the SysTick timer.
 * @param   Copy_Value: The value to be loaded into the SysTick timer.
 * @return  Status of the operation (success/error).
 */
SYSTICK_ErrorStatus_t SYSTICK_SetTimeMs(u32 Copy_Value);
SYSTICK_ErrorStatus_t SYSTICK_SetPeriodicty(u8 Copy_Periodicty);

/**
 * @brief   Starts the SysTick timer.
 */
void SYSTICK_Start();

/**
 * @brief   Stops the SysTick timer.
 */
void SYSTICK_Stop();

/**
 * @brief   Sets the callback function for the SysTick interrupt.
 * @param   FuncName: Pointer to the callback function.
 * @return  Status of the operation (success/error).
 */
SYSTICK_ErrorStatus_t SYSTICK_SetCallBack(SYSTICK_Cbf_t FuncName);
#endif /* SYSTICK_H_ */
