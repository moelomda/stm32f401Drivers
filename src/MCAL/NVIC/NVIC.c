#include "NVIC.h"
#define ONE  1
#define AIRCR_PRI_CLR 0xFFFFF8FF
typedef struct {
    u32 NVIC_ISER[8];       /**< Interrupt Set-Enable Registers */
    u32 Reserved[24];       /**< Reserved space */
    u32 NVIC_ICER[8];       /**< Interrupt Clear-Enable Registers */
    u32 Reserved1[24];      /**< Reserved space */
    u32 NVIC_ISPR[8];       /**< Interrupt Set-Pending Registers */
    u32 Reserved2[24];      /**< Reserved space */
    u32 NVIC_ICPR[8];       /**< Interrupt Clear-Pending Registers */
    u32 Reserved3[24];      /**< Reserved space */
    u32 NVIC_IABR[8];       /**< Interrupt Active Bit Registers */
    u32 Reserved4[56];      /**< Reserved space */
    u32 NVIC_IPR[59];       /**< Interrupt Priority Registers */
    u32 Reserved5[643];     /**< Reserved space */
    u32 NVIC_STIR;          /**< Software Trigger Interrupt Register */
} Nvic_tstrRegister;

#define NVIC 	((Nvic_tstrRegister*)(0xE000E100))
#define AIRCR	(*(volatile u32*)0xE000ED0C)

NVIC_enuErrorStatus_t NVIC_IRQControl(IRQn_t IRQn , u32 Copy_Status)
{
  NVIC_enuErrorStatus_t Loc_ErrorStatus =NVIC_enuSuccesseded;
  if(IRQn > NVIC_IRQNumber)
  {
	  Loc_ErrorStatus =NVIC_enuInvalidIrq;
  }
  else if (Copy_Status != IRQ_ENABLE && Copy_Status != IRQ_DISABLE)
  {
	  Loc_ErrorStatus = NVIC_enuInvalidStatus;
  }
  else
  {
  if(Copy_Status == IRQ_ENABLE )
  {
    NVIC->NVIC_ISER[(IRQn  / 32)]|= ONE << (IRQn  % 32)  ;
  }
  else
  {
    NVIC->NVIC_ICER[(IRQn  / 32)]|= ONE << (IRQn  % 32)  ;
  }
  }
  return Loc_ErrorStatus;
}
NVIC_enuErrorStatus_t NVIC_IRQPriority(IRQn_t IRQn, u32 priority)
{
	 NVIC_enuErrorStatus_t Loc_ErrorStatus =NVIC_enuSuccesseded;
	  if(IRQn > NVIC_IRQNumber)
	  {
		  Loc_ErrorStatus =NVIC_enuInvalidIrq;
	  }
	  else if (priority > PRIORITY_127)
	  {
		  Loc_ErrorStatus = NVIC_enuInvalidPriority;
	  }
	  else
	  {
			u16 Loc_RegisterNum =  IRQn  / 4 ;
			u16 Loc_bitIndex    = ((IRQn % 4 ) * 8)+ 4;
			u32 Loc_TempIpr = NVIC->NVIC_IPR[Loc_RegisterNum];
			Loc_TempIpr &= ~(0xF<<Loc_bitIndex);
			Loc_TempIpr |= priority << Loc_bitIndex ;
			NVIC->NVIC_IPR[Loc_RegisterNum]=Loc_TempIpr;
	  }
	  return Loc_ErrorStatus;
}
NVIC_enuErrorStatus_t NVIC_IRQPendingControl(IRQn_t IRQn , u32 Copy_Status)
{
	 NVIC_enuErrorStatus_t Loc_ErrorStatus =NVIC_enuSuccesseded;
	  if(IRQn > NVIC_IRQNumber)
	  {
		  Loc_ErrorStatus =NVIC_enuInvalidIrq;
	  }
	  else if (Copy_Status != SET_PENDING && Copy_Status != CLR_PENDING)
	  {
		  Loc_ErrorStatus = NVIC_enuInvalidStatus;
	  }
	  else
	  {
   if(Copy_Status == SET_PENDING)
   {
	NVIC->NVIC_ISPR[(IRQn  / 32)]|= ONE << (IRQn  % 32) ;
   }
   else
   {
	NVIC->NVIC_ICPR[(IRQn  / 32)]|= ONE << (IRQn  % 32) ;
   }
   }
	  return Loc_ErrorStatus;
}
NVIC_enuErrorStatus_t NVIC_GetActive(IRQn_t IRQn, u32 *Add_Status)
{
	 NVIC_enuErrorStatus_t Loc_ErrorStatus =NVIC_enuSuccesseded;
		  if(IRQn > NVIC_IRQNumber)
		  {
			  Loc_ErrorStatus =NVIC_enuInvalidIrq;
		  }
		  else if (!Add_Status)
		  {
			  Loc_ErrorStatus =NVIC_enuNullPtr;
		  }
		  else
		  {
			u16 Loc_RegisterNum = IRQn  / 32 ;
			u16 Loc_BitPosition = IRQn  % 32 ;
			u32 Loc_TempIabr =(NVIC->NVIC_IABR[Loc_RegisterNum]);
			*Add_Status=(Loc_TempIabr & (ONE<<Loc_BitPosition))>>Loc_BitPosition;
		  }
		  return Loc_ErrorStatus;
}
NVIC_enuErrorStatus_t NVIC_GenerateSwINT(IRQn_t IRQn)
{
  NVIC_enuErrorStatus_t Loc_ErrorStatus =NVIC_enuSuccesseded;
	   if(IRQn > NVIC_IRQNumber)
		{
	     Loc_ErrorStatus =NVIC_enuInvalidIrq;
		}
	   else
	   {
		  u32 Loc_TempStir = NVIC->NVIC_STIR ;
		  Loc_TempStir |= IRQn ;
		  NVIC->NVIC_STIR = Loc_TempStir ;
	   }
	   return Loc_ErrorStatus;
}
void NVIC_SetPriorityGrouping(u32 Copy_PriorityGrouping)
{
    u32 Loc_Aircr =AIRCR ;
    Loc_Aircr&= AIRCR_PRI_CLR ;
    Loc_Aircr|=Copy_PriorityGrouping;
    AIRCR = Loc_Aircr;
}
