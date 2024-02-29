/**
  ******************************************************************************
  * @file    LEDCfg.c
  * @brief   Configuration file for LED module.
  ******************************************************************************
  * @attention
  *
  * This file contains the configurations for the LED module. It includes the
  * definitions of LED configurations, such as GPIO port, pin, connection type,
  * and default state.
  ******************************************************************************
  */
#include "LED_Cfg.h"
#include "LED.h"
const ledcfg_t Leds[_led_num] ={
[led_alarm]=
{
.Port = GPIO_A,
.Pin  = GPIO_PIN_1,
.Connection = LED_FORWARD,
.defaultstate = LED_ON ,
},
[led_green]=
{
.Port = GPIO_B,
.Pin  = GPIO_PIN_5,
.Connection = LED_FORWARD,
.defaultstate = LED_ON ,
}
};
