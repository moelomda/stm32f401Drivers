#include "SHED.h"

/* Forward declarations of tasks */
extern void Runnable_APP1(void);
extern void Runnable_APP2(void);
extern void Switch_Runnable(void);
/* Definition of task array */
const Runnable_t Run_Arr[_Tasks_Number] =
{
    [Task1_Runabble] =
    {
        .Name = "Runabble1",
        .PeriodicityMs = 1000,
        .Priorty = 1,
		.DelayMs = 3,
        .Cb = &Runnable_APP1,
    },

    [Task2_Runabble] =
    {
        .Name = "Runabble2",
        .PeriodicityMs = 500,
        .Priorty = 0,
		.DelayMs = 5,
        .Cb = &Runnable_APP2,
    },
	[SW_Runabble] =
	{
	        .Name = "SW_Runnable",
	        .PeriodicityMs = 5,
	        .Priorty = 0,
			.DelayMs = 0,
	        .Cb = &Switch_Runnable,
	 }
};
