#include "SYSTICK.h"
#include "SYSTICKCfg.h"
#define CLK_SRC_CLR  ~(1<<2)
#define INT_CLR      ~(1<<1)
#define MAX_Val      0x00FFFFFF
#define STK_CTRL_ENABLE_MSK  0x00000001
#define RESET          0
#define SEC_TO_MS     1048
typedef struct{   
    u32 Systick_Ctrl;
	u32 Systick_Load;
	u32 Systick_Value;
	u32 Systick_Calib;
}SYSTICK_Registers_t;
#define SYSTICK	((SYSTICK_Registers_t*)0xE000E010)
u8 SYSTICK_Periodicty ;
SYSTICK_Cbf_t SYSTICK_Cbf ;
SYSTICK_ErrorStatus_t SYSTICK_SelectClkSrc(u32 Copy_ClkName){
  u8 Loc_ErrorStatus = SYSTICK_enuSuccess ;
  u32 Loc_TempCtrl =  SYSTICK->Systick_Ctrl;
  if(Copy_ClkName > PROCESSOR_CLK){
	  Loc_ErrorStatus = SYSTICK_enuInvalidClkSrc ;
  }
  else{   Loc_TempCtrl &= CLK_SRC_CLR ;
	  Loc_TempCtrl |= (Copy_ClkName << 2);
	  SYSTICK->Systick_Ctrl= Loc_TempCtrl;
  }
   return Loc_ErrorStatus ;
}
SYSTICK_ErrorStatus_t SYSTICK_CtrlInterrupt(u32 Copy_Option){
	u8 Loc_ErrorStatus = SYSTICK_enuSuccess ;
	u32 Loc_TempCtrl =  SYSTICK->Systick_Ctrl;
	if(Copy_Option > SYSTICK_EXCEP_EN ){
		  Loc_ErrorStatus = SYSTICK_enuInvalidOption;
	  }
	  else{
	  Loc_TempCtrl &= INT_CLR ;
	  Loc_TempCtrl |= (Copy_Option << 1);
	  SYSTICK->Systick_Ctrl= Loc_TempCtrl;
      }
	return Loc_ErrorStatus ;
}
SYSTICK_ErrorStatus_t SYSTICK_SetTimeMs(u32 Copy_Value){
	u8 Loc_ErrorStatus = SYSTICK_enuSuccess ;
	u32 Temp_ClkSrc = (((SYSTICK->Systick_Ctrl)>>(2))&1);
	if(Copy_Value > MAX_Val){
		Loc_ErrorStatus= SYSTICK_enuInvalidValue;
	}
	else{
	u32 Loc_InputFrq= ((Temp_ClkSrc ==PROCESSOR_CLK) ? PROCESSPR_CLK_FRQ : (PROCESSPR_CLK_FRQ  /8));
	Copy_Value=(Copy_Value*Loc_InputFrq)/SEC_TO_MS;
	SYSTICK->Systick_Load = (Copy_Value-1);
	}
	return Loc_ErrorStatus ;
}
void SYSTICK_Start(){
	SYSTICK->Systick_Value &= RESET;
	SYSTICK->Systick_Ctrl|=STK_CTRL_ENABLE_MSK;
}
void SYSTICK_Stop(){
	SYSTICK->Systick_Ctrl&=~STK_CTRL_ENABLE_MSK;
}
SYSTICK_ErrorStatus_t SYSTICK_SetPeriodicty(u8 Copy_Periodicty){
	u8 Loc_ErrorStatus = SYSTICK_enuSuccess ;
	if(Copy_Periodicty > PERIODICITY_AUTO){
	  Loc_ErrorStatus = SYSTICK_enuInvalidOption;
	}
	else{
		SYSTICK_Periodicty = Copy_Periodicty;
	}
	return Loc_ErrorStatus ;
}
SYSTICK_ErrorStatus_t SYSTICK_SetCallBack(SYSTICK_Cbf_t FuncName){
	u8 Loc_ErrorStatus = SYSTICK_enuSuccess ;
	if(FuncName){
	   SYSTICK_Cbf = FuncName;
	}
	else{
		Loc_ErrorStatus = SYSTICK_enuNullPtr ;
	}
	return Loc_ErrorStatus;
}
void SysTick_Handler(void){
    if(SYSTICK_Periodicty==PERIODICITY_ONETIME) {
        SYSTICK_Stop();
    }
    if(SYSTICK_Cbf) {
    SYSTICK_Cbf();
    }
}
