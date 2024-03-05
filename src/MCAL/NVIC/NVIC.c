#include "NVIC.h"
// Constants
#define ONE              1
#define AIRCR_PRI_CLR    0xFFFFF8FF
#define GROUPS_BASE      (0x3 << 8)
#define BITS_32          32
#define FOUR_BITS        4

// NVIC structure
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
} NVIC_PERI_T;

// NVIC base address
#define NVIC  ((NVIC_PERI_T*)(0xE000E100))
#define AIRCR (*(volatile u32*)0xE000ED0C)

NVIC_enuErrorStatus_t NVIC_IRQControl(IRQn_t IRQn , u32 Copy_Status)
{
    NVIC_enuErrorStatus_t Loc_ErrorStatus = NVIC_enuSuccesseded;

    if (IRQn > NVIC_IRQNumber)
    {
        Loc_ErrorStatus = NVIC_enuInvalidIrq;
    }
    else if (Copy_Status != IRQ_ENABLE && Copy_Status != IRQ_DISABLE)
    {
        Loc_ErrorStatus = NVIC_enuInvalidStatus;
    }
    else
    {
        if (Copy_Status == IRQ_ENABLE)
        {
            NVIC->NVIC_ISER[IRQn / BITS_32] = (ONE << (IRQn % BITS_32));  // Enable interrupt
        }
        else
        {
            NVIC->NVIC_ICER[IRQn / BITS_32] = (ONE << (IRQn % BITS_32));  // Disable interrupt
        }
    }

    return Loc_ErrorStatus;
}

NVIC_enuErrorStatus_t NVIC_IRQPendingControl(IRQn_t IRQn , u32 Copy_Status)
{
    NVIC_enuErrorStatus_t Loc_ErrorStatus = NVIC_enuSuccesseded;

    if (IRQn > NVIC_IRQNumber)
    {
        Loc_ErrorStatus = NVIC_enuInvalidIrq;
    }
    else if (Copy_Status != SET_PENDING && Copy_Status != CLR_PENDING)
    {
        Loc_ErrorStatus = NVIC_enuInvalidStatus;
    }
    else
    {
        if (Copy_Status == SET_PENDING)
        {
            NVIC->NVIC_ISPR[IRQn / BITS_32] = (ONE << (IRQn % BITS_32));  // Set pending
        }
        else
        {
            NVIC->NVIC_ICPR[IRQn / BITS_32] = (ONE << (IRQn % BITS_32));  // Clear pending
        }
    }

    return Loc_ErrorStatus;
}

NVIC_enuErrorStatus_t NVIC_GetActive(IRQn_t IRQn, u32 *Add_Status)
{
    NVIC_enuErrorStatus_t Loc_ErrorStatus = NVIC_enuSuccesseded;

    if (IRQn > NVIC_IRQNumber)
    {
        Loc_ErrorStatus = NVIC_enuInvalidIrq;
    }
    else if (!Add_Status)
    {
        Loc_ErrorStatus = NVIC_enuNullPtr;
    }
    else
    {
        u16 Loc_RegisterNum = IRQn / BITS_32;
        u16 Loc_BitPosition = IRQn % BITS_32;
        u32 Loc_TempIabr = (NVIC->NVIC_IABR[Loc_RegisterNum]);
        *Add_Status = (Loc_TempIabr & (ONE << Loc_BitPosition)) >> Loc_BitPosition;
    }

    return Loc_ErrorStatus;
}

NVIC_enuErrorStatus_t NVIC_GenerateSwINT(IRQn_t IRQn)
{
    NVIC_enuErrorStatus_t Loc_ErrorStatus = NVIC_enuSuccesseded;

    if (IRQn > NVIC_IRQNumber)
    {
        Loc_ErrorStatus = NVIC_enuInvalidIrq;
    }
    else
    {
        u32 Loc_TempStir = NVIC->NVIC_STIR;
        Loc_TempStir |= IRQn;
        NVIC->NVIC_STIR = Loc_TempStir;
    }
     return Loc_ErrorStatus;
}
void NVIC_SetIRQPriority(IRQn_t IRQn, u32 Copy_GroupPriorty, u32 Copy_SubGroupPriorty, u32 Copy_GroupName)
{
    u32 Loc_Aircr = AIRCR;
    u16 Loc_bitIndex = ((IRQn % FOUR_BITS) * 8) + FOUR_BITS;
    u16 Loc_PriortyValue = Copy_SubGroupPriorty | (Copy_GroupPriorty << ((Copy_GroupName - GROUPS_BASE) >> 8));
    u32 Loc_TempIpr = NVIC->NVIC_IPR[IRQn / FOUR_BITS];

    Loc_TempIpr &= ~(0xF << Loc_bitIndex);
    Loc_TempIpr |= Loc_PriortyValue << Loc_bitIndex;
    NVIC->NVIC_IPR[IRQn / FOUR_BITS] = Loc_TempIpr;

    Loc_Aircr &= AIRCR_PRI_CLR;
    Loc_Aircr |= Copy_GroupName;
    AIRCR = Loc_Aircr;
}
