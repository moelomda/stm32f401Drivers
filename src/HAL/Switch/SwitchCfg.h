#ifndef SWITCHCFG_H_
#define SWITCHCFG_H_

/**
  ******************************************************************************
  * @file    SWITCHCfg.h
  * @brief   Header file for SWITCH module configurations.
  ******************************************************************************
  * @attention
  *
  * This file contains the configurations for the SWITCH module. It defines the
  * enumeration of switches that can be used in the application. Users should add
  * switch names between `Switch_Led` and `Switch_Buzzer`. The `_Switch_num` enumerator
  * should not be modified, as it indicates the total number of switches in the
  * enumeration.
  *
  ******************************************************************************
  */

typedef enum {
    Switch_Led,         /**< Switch connected to LED */
    Switch_Buzzer,      /**< Switch connected to buzzer */
    _Switch_num,        /**< Total number of switches (Do not modify this enumerator) */
} switches_t;

#endif /* SWITCHCFG_H_ */
