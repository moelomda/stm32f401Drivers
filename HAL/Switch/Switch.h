#ifndef SWITCH_H_
#define SWITCH_H_

/**
  ******************************************************************************
  * @file    SWITCH.h
  * @brief   Header file for SWITCH module.
  ******************************************************************************
  * @attention
  *
  * This file contains the definitions and prototypes related to the SWITCH module.
  * It provides functions for initializing and reading the state of switches connected
  * to the microcontroller.
  *
  * @note
  *   - Refer to the specific switch hardware documentation for connection details.
  ******************************************************************************
  */

#include "std_types.h"
#include "GPIO.h"
#include "SwitchCfg.h"

#define SWITCH_NOT_PRESSED  0
#define SWITCH_PRESSED      1

typedef struct {
    u32 Port;
    u32 Pin;
    u8 PhysicalState;
} Switchcfg_t;

void Switch_Init(void);
void Switch_GetSwitchState(u32 SwitchName, u32 *Add_SwitchState);

#endif /* SWITCH_H_ */
