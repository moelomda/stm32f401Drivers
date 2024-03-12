/**
 * @file    SHED.c
 * @brief   Scheduler (SHED) implementation file.
 */

#include "SHED.h"
#include "SYSTICK.h"

#define TICKTIME 1 /**< Time in milliseconds for each tick */

typedef struct {
	//Runnable_t * Runnable;
    u32 RemainingTimeMs; /**< Remaining time in milliseconds for the task */
} RunabbleInfo_t;

static volatile u32 PendingTicks = 0; /**< Number of pending ticks */
static RunabbleInfo_t RInfo_Arr[_Tasks_Number]; /**< Array to store task information */
extern const Runnable_t Run_Arr[_Tasks_Number];

/**
 * @brief   Callback function for the SYSTICK timer.
 *          Increments the number of pending ticks.
 */
void tickcb(void)
{
    PendingTicks++;
}

static void SHED(void)
{
    u32 Idx;
    for (Idx = 0; Idx < _Tasks_Number; Idx++)
    {
        if (Run_Arr[Idx].Cb && RInfo_Arr[Idx].RemainingTimeMs == 0)
        {
            Run_Arr[Idx].Cb(); /**< Execute the task callback */
            RInfo_Arr[Idx].RemainingTimeMs = Run_Arr[Idx].PeriodicityMs; /**< Reset the remaining time */
        }
        RInfo_Arr[Idx].RemainingTimeMs -= TICKTIME; /**< Decrement the remaining time */
    }
}
void SHED_Init()
{
    u32 Idx;
    SYSTICK_SelectClkSrc(AHB_DEV8_CLK); /**< Select the clock source for the SYSTICK timer */
    SYSTICK_CtrlInterrupt(SYSTICK_EXCEP_EN); /**< Enable SYSTICK interrupts */
    SYSTICK_SetPeriodicty(PERIODICITY_AUTO); /**< Set SYSTICK periodicity to automatic */
    SYSTICK_SetTimeMs(TICKTIME); /**< Set SYSTICK timer time to TICKTIME milliseconds */
    SYSTICK_SetCallBack(tickcb); /**< Set the callback function for SYSTICK interrupts */
    SHED_Start(); /**< Start the scheduler */
    for (Idx = 0; Idx < _Tasks_Number; Idx++)
    {
    	//RInfo_Arr[Run_Arr[Idx].Priorty].Runnable = Run_Arr[Idx];
        RInfo_Arr[Run_Arr[Idx].Priorty].RemainingTimeMs = Run_Arr[Idx].DelayMs; /**< Initialize task information */
    }
}
void SHED_Start()
{
    SYSTICK_Start(); /**< Start the SYSTICK timer */
    while (1)
    {
        if (PendingTicks)
        {
            PendingTicks--; /**< Decrement the number of pending ticks */
            SHED(); /**< Execute the scheduler */
        }
    }
}
