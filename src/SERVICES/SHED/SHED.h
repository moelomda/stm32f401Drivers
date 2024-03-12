#ifndef SHED_H_
#define SHED_H_

#include "SHEDCfg.h"
#include "std_types.h"

// Type definition for a function pointer to a runnable callback
typedef void (*RunableCb_t) (void);

// Structure to hold information about a runnable task
typedef struct {
    char *Name;          // Name of the task
    u32 PeriodicityMs;   // Periodicity of the task in milliseconds
    u32 Priorty;         // Priority of the task
    RunableCb_t Cb;     // Callback function pointer for the task
} Runnable_t;

// Enum defining possible error status for the SHED module
typedef enum {
    SHED_enuOk,         // Operation successful
    SHED_enuNok,        // Operation failed
} SHED_ErrorStatus_t;

// Function prototypes
void SHED_Init();       // Initialize the SHED module
void SHED_Start();      // Start the SHED module

#endif /* SHED_H_ */
