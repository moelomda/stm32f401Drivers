#include "Switch.h"

extern const Switchcfg_t Switches[_Switch_num];
u8 Switch_State[_Switch_num];
void Switch_Runnable();
void Switch_Init(void)
{
    GpioPinCfg_t Switch;
    u8 Loc_Iterator;

    Switch.GPIO_Direction = GPIO_INPUT;
    Switch.GPIO_Speed = GPIO_SPEED_LOW;

    for (Loc_Iterator = 0; Loc_Iterator < _Switch_num; Loc_Iterator++)
    {
        Switch.GPIO_Port = Switches[Loc_Iterator].Port;
        Switch.GPIO_Pin = Switches[Loc_Iterator].Pin;
        Switch.GPIO_Mode = Switches[Loc_Iterator].PhysicalState;
        GPIO_Init(&Switch);
    }
}

void Switch_GetSwitchState(u32 SwitchName, u32 *Add_SwitchState)
{
    u32 Loc_State;
    u32 Loc_Temp = 0 ;
    GPIO_GetPinValue(Switches[SwitchName].Port, Switches[SwitchName].Pin, &Loc_State);
    if(Switches[SwitchName].PhysicalState == GPIO_PULL_UP)
    {
      Loc_Temp = 1 ;
    }
    else
    {
      Loc_Temp = 0 ;
    }
    *Add_SwitchState = (Switch_State[SwitchName])^(Loc_Temp);
}
void Switch_Runnable()
{
   u8 Loc_Iterator= 0 ;
   u32 Curr_State;
   u8 Prev_State[_Switch_num];
   u8 Counts[_Switch_num];
   for(Loc_Iterator = 0 ; Loc_Iterator < _Switch_num ; Loc_Iterator++ ){
   GPIO_GetPinValue(Switches[Loc_Iterator].Port, Switches[Loc_Iterator].Pin, &Curr_State);
   if(Curr_State == Prev_State[Loc_Iterator] )
   {
	   Counts[Loc_Iterator]++;
   }
   else
   {
	   Counts[Loc_Iterator]= 0;
   }
   if(Counts[Loc_Iterator]==5)
   {
     Switch_State[Loc_Iterator]=Curr_State;
     Counts[Loc_Iterator]= 0;
   }
     Prev_State[Loc_Iterator]= Curr_State;
   }
}
