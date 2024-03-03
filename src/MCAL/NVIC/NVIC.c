#include "NVIC.h"

#define ONE  1
typedef struct
{
	u32 NVIC_ISER[8];

	u32 Reserved[24];

	u32 NVIC_ICER[8];

	u32 Reserved1[24];

	u32 NVIC_ISPR[8];

	u32 Reserved2[24];

	u32 NVIC_ICPR[8];

	u32 Reserved3[24];

	u32 NVIC_IABR[8];

	u32 Reserved4[56];

	u32 NVIC_IPR[59];

	u32 Reserved5[643];

	u32 NVIC_STIR;

}Nvic_tstrRegister;
#define NVIC 	((Nvic_tstrRegister*)(0xE000E100))
#define ACIR	(*(volatile u32*)0xE000ED0C)
void NVIC_IRQControl(IRQn_t IRQn , u32 Copy_Status)
{
	u16 Loc_RegisterNum = IRQn  / 32 ;
	u16 Loc_BitPosition = IRQn  % 32 ;
  if(Copy_Status == IRQ_ENABLE )
  {
    NVIC->NVIC_ISER[Loc_RegisterNum]|= ONE << Loc_BitPosition ;
  }
  else
  {
    NVIC->NVIC_ICER[Loc_RegisterNum]|= ONE << Loc_BitPosition ;
  }
}
void NVIC_IRQPriority(IRQn_t IRQn, u32 priority)
{
	u16 Loc_RegisterNum =  IRQn  / 4 ;
	u16 Loc_bitIndex    = (IRQn % 4 ) * 8;
	u32 Loc_TempIpr = NVIC->NVIC_IPR[Loc_RegisterNum];
	Loc_TempIpr &= ~(0xF<<Loc_bitIndex);
	Loc_TempIpr |= priority << Loc_bitIndex ;
	NVIC->NVIC_IPR[Loc_RegisterNum]=Loc_TempIpr;
}
NVIC_IRQPendingControl(IRQn_t IRQn , u32 Copy_Status)
{
	u16 Loc_RegisterNum = IRQn  / 32 ;
	u16 Loc_BitPosition = IRQn  % 32 ;
   if(Copy_Status == SET_PENDING)
   {
	NVIC->NVIC_ISPR[Loc_RegisterNum]|= ONE << Loc_BitPosition ;
   }
   else
   {
	NVIC->NVIC_ICPR[Loc_RegisterNum]|= ONE << Loc_BitPosition ;
   }
}
void NVIC_GetActive(IRQn_t IRQn, u32 *Add_Status)
{
	u16 Loc_RegisterNum = IRQn  / 32 ;
	u16 Loc_BitPosition = IRQn  % 32 ;
	u32 Loc_TempIabr =(NVIC->NVIC_IABR[Loc_RegisterNum]);
	  *Add_Status=(Loc_TempIabr & (ONE<<Loc_BitPosition))>>Loc_BitPosition;
}
void NVIC_GenerateSwINT(IRQn_t IRQn)
{
  u32 Loc_TempStir = NVIC->NVIC_STIR ;
  Loc_TempStir |= IRQn ;
  NVIC->NVIC_STIR = Loc_TempStir ;
}



