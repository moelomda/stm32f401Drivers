/**
  ******************************************************************************
  * @file    LEDCfg.h
  * @brief   Header file for LED module configurations.
  ******************************************************************************
  */
#ifndef LED_CFG_H_
#define LED_CFG_H_

/**
 * @brief   Enumeration of LEDs.
 * @details This enumeration defines the names of LEDs that can be used in the
 *          application. Users should add LED names between `led_alarm` and
 *          `led_green`. The `_led_num` enumerator should not be modified,
 *          as it indicates the total number of LEDs in the enumeration.
 * @note    Do not modify `_led_num`, as it represents the total number of LEDs.
 */
typedef enum {
    led_alarm,      /**< LED representing an alarm */
    led_green,      /**< Green LED */
    _led_num        /**< Total number of LEDs (Do not modify this enumerator) */
} leds_t;

#endif /* LED_CFG_H_ */
