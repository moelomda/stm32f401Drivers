#include "SHED.h"

/* Forward declarations of tasks */
extern void Runnable_APP1(void);
extern void Runnable_APP2(void);

/* Definition of task array */
const Runnable_t Run_Arr[_Tasks_Number] =
{
    [Task1_Runabble] =
    {
        .Name = "Runabble1",
        .PeriodicityMs = 30,
        .Priorty = 1,
        .Cb = &Runnable_APP1,
    },

    [Task2_Runabble] =
    {
        .Name = "Runabble2",
        .PeriodicityMs = 15,
        .Priorty = 0,
        .Cb = &Runnable_APP2,
    }
};
