#include "LED.h"
#include "GPIO.h"
extern const ledcfg_t Leds[_led_num];
void LED_Init(void)
{
GpioPinCfg_t Led_Cfg ;
u8 Loc_Iterator ;
Led_Cfg.GPIO_Direction = GPIO_OUTPUT ;
Led_Cfg.GPIO_Speed = GPIO_SPEED_HIGH  ;
Led_Cfg.GPIO_Mode = GPIO_OTYPE_PUSHPULL ;
for(Loc_Iterator =0; Loc_Iterator <_led_num; Loc_Iterator ++)
{
	Led_Cfg.GPIO_Port =Leds[Loc_Iterator].Port;
	Led_Cfg.GPIO_Pin =Leds[Loc_Iterator].Pin;
	GPIO_Init(&Led_Cfg);
	GPIO_SetPinValue(Leds[Loc_Iterator].Port ,Leds[Loc_Iterator].Pin , Leds[Loc_Iterator].defaultstate ^ Leds[Loc_Iterator].Connection);
}
}
void LED_SetLedState (u32 Led_Name , u32 Led_State)
{
	GPIO_SetPinValue(Leds[Led_Name].Port ,Leds[Led_Name].Pin , (Led_State) ^ (Leds[Led_Name].Connection));
}
