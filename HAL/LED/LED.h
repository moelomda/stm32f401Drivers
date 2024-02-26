/**
  ******************************************************************************
  * @file    LED.h
  * @brief   Header file for LED module.
  ******************************************************************************
  * @attention
  *
  * This file contains the definitions and prototypes related to the LED module.
  * It provides functions for initializing and controlling LEDs connected to the
  * microcontroller.
  *
  * @note
  *   - Refer to the specific LED hardware documentation for connection details.
  ******************************************************************************
  */

#ifndef LED_H_
#define LED_H_

#include "std_types.h"
#include "LED_Cfg.h"
#include "GPIO.h"
#define LED_FORWARD  0
#define LED_REVERSE  1
#define LED_ON       1
#define LED_OFF      0

/**
 * @brief   LED Configuration Structure
 * @details This structure defines the configuration parameters for an LED.
 *           - port: The GPIO port to which the LED is connected.
 *           - pin: The pin number on the LED port to which the LED is connected.
 *           - connection: The LED connection type (e.g., LED_FORWARD or LED_REVERSE).
 *           - defaultstate: The default state of the LED (e.g., LED_STATE_ON or LED_STATE_OFF).
 */
typedef struct {
    u32 Port;               /**< LED port to which the LED is connected */
    u32 Pin;                /**< Pin number on the LED port */
    u8 Connection;          /**< LED connection type */
    u8 defaultstate;       /**< Default state of the LED */
} ledcfg_t;
typedef enum
{
    LED_OK = 0,
	LED_enuInvalidPortNum,
	LED_enuInvalidPinNum,
	LED_enuInvalidMode,
	LED_enuNullPtr,
    LED_NOK
} LED_ErrorStatus_t;

/**
 * @brief   Initialize the LED module.
 * @details This function initializes the GPIO pins connected to the LEDs based on the
 *           configuration provided in the GPIO configuration table.
 * @return  None
 */
void LED_Init(void);
/**
 * @brief   Set the status of an LED.
 * @param   Led_Name: The index of the LED in the configuration table.
 * @param   Led_State: The status to set for the LED (0 for OFF, 1 for ON).
 * @return  None
 */
void LED_SetLedState (u32 Led_Name , u32 Led_State);

#endif /* LED_H_ */

