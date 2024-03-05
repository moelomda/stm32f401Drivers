#ifndef NVIC_H_
#define NVIC_H_

#include "Stm32F401C_Interrupts.h"
#include "std_types.h"

#define IRQ_ENABLE     1    // Enable IRQ
#define IRQ_DISABLE    0    // Disable IRQ
#define SET_PENDING    1    // Set interrupt as pending
#define CLR_PENDING    0    // Clear pending interrupt
#define INT_ACTIVE     1    // Interrupt active
#define INT_NACTIVE    0    // Interrupt not active


#define NVIC_PRIORITYGROUP_4_NONE     (0x3 << 8)  // (4 bits) for group (0bit) for subgroup
#define NVIC_PRIORITYGROUP_3_1        (0x4 << 8)  // (3 bits) for group (1bit) for subgroup
#define NVIC_PRIORITYGROUP_2_2        (0x5 << 8)  // (2 bits) for group (2bits) for subgroup
#define NVIC_PRIORITYGROUP_1_3        (0x6 << 8)  // (1 bit1) for group (3bit) for subgroup
#define NVIC_PRIORITYGROUP_0_NONE     (0x7 << 8)  // (0 bits) for group (4bit) for subgroup


#define PRIORITY_0     0
#define PRIORITY_1     1
#define PRIORITY_2     2
#define PRIORITY_3     3
#define PRIORITY_4     4
#define PRIORITY_5     5
#define PRIORITY_6     6
#define PRIORITY_7     7
#define PRIORITY_8     8
#define PRIORITY_9     9
#define PRIORITY_10    10
#define PRIORITY_11    11
#define PRIORITY_12    12
#define PRIORITY_13    13
#define PRIORITY_14    14
#define PRIORITY_15    15
#define PRIORITY_16    16
#define PRIORITY_17    17
#define PRIORITY_18    18
#define PRIORITY_19    19
#define PRIORITY_20    20
#define PRIORITY_21    21
#define PRIORITY_22    22
#define PRIORITY_23    23
#define PRIORITY_24    24
#define PRIORITY_25    25
#define PRIORITY_26    26
#define PRIORITY_27    27
#define PRIORITY_28    28
#define PRIORITY_29    29
#define PRIORITY_30    30
#define PRIORITY_31    31
#define PRIORITY_32    32
#define PRIORITY_33    33
#define PRIORITY_34    34
#define PRIORITY_35    35
#define PRIORITY_36    36
#define PRIORITY_37    37
#define PRIORITY_38    38
#define PRIORITY_39    39
#define PRIORITY_40    40
#define PRIORITY_41    41
#define PRIORITY_42    42
#define PRIORITY_43    43
#define PRIORITY_44    44
#define PRIORITY_45    45
#define PRIORITY_46    46
#define PRIORITY_47    47
#define PRIORITY_48    48
#define PRIORITY_49    49
#define PRIORITY_50    50
#define PRIORITY_51    51
#define PRIORITY_52    52
#define PRIORITY_53    53
#define PRIORITY_54    54
#define PRIORITY_55    55
#define PRIORITY_56    56
#define PRIORITY_57    57
#define PRIORITY_58    58
#define PRIORITY_59    59
#define PRIORITY_60    60
#define PRIORITY_61    61
#define PRIORITY_62    62
#define PRIORITY_63    63
#define PRIORITY_64    64
#define PRIORITY_65    65
#define PRIORITY_66    66
#define PRIORITY_67    67
#define PRIORITY_68    68
#define PRIORITY_69    69
#define PRIORITY_70    70
#define PRIORITY_71    71
#define PRIORITY_72    72
#define PRIORITY_73    73
#define PRIORITY_74    74
#define PRIORITY_75    75
#define PRIORITY_76    76
#define PRIORITY_77    77
#define PRIORITY_78    78
#define PRIORITY_79    79
#define PRIORITY_80    80
#define PRIORITY_81    81
#define PRIORITY_82    82
#define PRIORITY_83    83
#define PRIORITY_84    84
#define PRIORITY_85    85
#define PRIORITY_86    86
#define PRIORITY_87    87
#define PRIORITY_88    88
#define PRIORITY_89    89
#define PRIORITY_90    90
#define PRIORITY_91    91
#define PRIORITY_92    92
#define PRIORITY_93    93
#define PRIORITY_94    94
#define PRIORITY_95    95
#define PRIORITY_96    96
#define PRIORITY_97    97
#define PRIORITY_98    98
#define PRIORITY_99    99
#define PRIORITY_100   100
#define PRIORITY_101   101
#define PRIORITY_102   102
#define PRIORITY_103   103
#define PRIORITY_104   104
#define PRIORITY_105   105
#define PRIORITY_106   106
#define PRIORITY_107   107
#define PRIORITY_108   108
#define PRIORITY_109   109
#define PRIORITY_110   110
#define PRIORITY_111   111
#define PRIORITY_112   112
#define PRIORITY_113   113
#define PRIORITY_114   114
#define PRIORITY_115   115
#define PRIORITY_116   116
#define PRIORITY_117   117
#define PRIORITY_118   118
#define PRIORITY_119   119
#define PRIORITY_120   120
#define PRIORITY_121   121
#define PRIORITY_122   122
#define PRIORITY_123   123
#define PRIORITY_124   124
#define PRIORITY_125   125
#define PRIORITY_126   126
#define PRIORITY_127   127
/**
 * @brief   Enumeration for NVIC error status.
 * @details This enumeration defines the possible error statuses that can occur
 *          during NVIC (Nested Vector Interrupt Controller) configuration or usage.
 *          - NVIC_enuInvalidIrq: Indicates an invalid IRQ number.
 *          - NVIC_enuInvalidStatus: Indicates an invalid status or condition.
 *          - NVIC_enuInvalidPriority: Indicates an invalid priority level.
 *          - NVIC_enuNullPtr: Indicates a null pointer error.
 *          - NVIC_enuInvalidGrouping: Indicates an invalid priority grouping configuration.
 */
typedef enum {
    NVIC_enuInvalidIrq,
    NVIC_enuInvalidStatus,
    NVIC_enuInvalidPriority,
    NVIC_enuNullPtr,
    NVIC_enuInvalidGrouping,
	NVIC_enuSuccesseded,
} NVIC_enuErrorStatus_t;

/**
 * @brief   Controls the specified interrupt in the NVIC.
 * @param   IRQn: The interrupt to be controlled.
 * @param   Copy_Status: The status to be set for the interrupt (enable/disable).
 * @note    This function provides control over the specified interrupt in the Nested Vector Interrupt Controller (NVIC),
 *          allowing for enabling, disabling, or configuring interrupt priority and other settings.
 * @return  Error status indicating the success or failure of the operation.
 */
NVIC_enuErrorStatus_t NVIC_IRQControl(IRQn_t IRQn, u32 Copy_Status);
/**
 * @brief   Controls the pending status of the specified interrupt in the NVIC.
 * @param   IRQn: The interrupt to be controlled.
 * @param   Copy_Status: The pending status to be set for the interrupt (set/clear).
 * @note    This function allows controlling the pending status of the specified interrupt in the Nested Vector Interrupt Controller (NVIC).
 * @return  Error status indicating the success or failure of the operation.
 */
NVIC_enuErrorStatus_t NVIC_IRQPendingControl(IRQn_t IRQn, u32 Copy_Status);

/**
 * @brief   Gets the active status of the specified interrupt in the NVIC.
 * @param   IRQn: The interrupt for which the active status is to be retrieved.
 * @param   Add_Status: Pointer to a variable to store the active status of the interrupt.
 * @note    This function retrieves the active status of the specified interrupt in the Nested Vector Interrupt Controller (NVIC),
 *          indicating whether the interrupt is currently active or not.
 * @return  Error status indicating the success or failure of the operation.
 */
NVIC_enuErrorStatus_t NVIC_GetActive(IRQn_t IRQn, u32 *Add_Status);

/**
 * @brief   Generates a software interrupt for the specified interrupt in the NVIC.
 * @param   IRQn: The interrupt for which the software interrupt is to be generated.
 * @note    This function generates a software interrupt for the specified interrupt in the Nested Vector Interrupt Controller (NVIC),
 *          allowing software to trigger interrupt handling routines as if the interrupt were triggered by hardware.
 * @return  Error status indicating the success or failure of the operation.
 */
NVIC_enuErrorStatus_t NVIC_GenerateSwINT(IRQn_t IRQn);

/**
 * @brief   Sets the priority of the specified interrupt in the NVIC.
 * @param   IRQn: The interrupt for which the priority is to be set.
 * @param   Copy_GroupPriorty: The group priority value to be assigned.
 * @param   Copy_SubGroupPriorty: The subpriority value to be assigned.
 * @param   Copy_GroupName: The configuration for priority grouping.
 * @note    This function sets the priority level of the specified interrupt in the Nested Vector Interrupt Controller (NVIC).
 *          It allows configuring both group priority and subpriority, based on the provided priority grouping configuration.
 */
void NVIC_SetIRQPriority(IRQn_t IRQn, u32 Copy_GroupPriorty, u32 Copy_SubGroupPriorty, u32 Copy_GroupName);

#endif /* NVIC_H_ */
