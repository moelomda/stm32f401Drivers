/*
 * NVIC.h
 *
 *  Created on: ???/???/????
 *      Author: Mohamed Elomda
 */
#ifndef NVIC_H_
#define NVIC_H_

#include "Stm32F401C_Interrupts.h"
#include "std_types.h"

#define IRQ_ENABLE    1
#define IRQ_DISABLE  0
#define SET_PENDING    1
#define CLR_PENDING    0
#define INT_ACTIVE     1
#define INT_NACTIVE    0

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
#define PRIORITY_128   128
#define PRIORITY_129   129
#define PRIORITY_130   130
#define PRIORITY_131   131
#define PRIORITY_132   132
#define PRIORITY_133   133
#define PRIORITY_134   134
#define PRIORITY_135   135
#define PRIORITY_136   136
#define PRIORITY_137   137
#define PRIORITY_138   138
#define PRIORITY_139   139
#define PRIORITY_140   140
#define PRIORITY_141   141
#define PRIORITY_142   142
#define PRIORITY_143   143
#define PRIORITY_144   144
#define PRIORITY_145   145
#define PRIORITY_146   146
#define PRIORITY_147   147
#define PRIORITY_148   148
#define PRIORITY_149   149
#define PRIORITY_150   150
#define PRIORITY_151   151
#define PRIORITY_152   152
#define PRIORITY_153   153
#define PRIORITY_154   154
#define PRIORITY_155   155
#define PRIORITY_156   156
#define PRIORITY_157   157
#define PRIORITY_158   158
#define PRIORITY_159   159
#define PRIORITY_160   160
#define PRIORITY_161   161
#define PRIORITY_162   162
#define PRIORITY_163   163
#define PRIORITY_164   164
#define PRIORITY_165   165
#define PRIORITY_166   166
#define PRIORITY_167   167
#define PRIORITY_168   168
#define PRIORITY_169   169
#define PRIORITY_170   170
#define PRIORITY_171   171
#define PRIORITY_172   172
#define PRIORITY_173   173
#define PRIORITY_174   174
#define PRIORITY_175   175
#define PRIORITY_176   176
#define PRIORITY_177   177
#define PRIORITY_178   178
#define PRIORITY_179   179
#define PRIORITY_180   180
#define PRIORITY_181   181
#define PRIORITY_182   182
#define PRIORITY_183   183
#define PRIORITY_184   184
#define PRIORITY_185   185
#define PRIORITY_186   186
#define PRIORITY_187   187
#define PRIORITY_188   188
#define PRIORITY_189   189
#define PRIORITY_190   190
#define PRIORITY_191   191
#define PRIORITY_192   192
#define PRIORITY_193   193
#define PRIORITY_194   194
#define PRIORITY_195   195
#define PRIORITY_196   196
#define PRIORITY_197   197
#define PRIORITY_198   198
#define PRIORITY_199   199
#define PRIORITY_200   200
#define PRIORITY_201   201
#define PRIORITY_202   202
#define PRIORITY_203   203
#define PRIORITY_204   204
#define PRIORITY_205   205
#define PRIORITY_206   206
#define PRIORITY_207   207
#define PRIORITY_208   208
#define PRIORITY_209   209
#define PRIORITY_210   210
#define PRIORITY_211   211
#define PRIORITY_212   212
#define PRIORITY_213   213
#define PRIORITY_214   214
#define PRIORITY_215   215
#define PRIORITY_216   216
#define PRIORITY_217   217
#define PRIORITY_218   218
#define PRIORITY_219   219
#define PRIORITY_220   220
#define PRIORITY_221   221
#define PRIORITY_222   222
#define PRIORITY_223   223
#define PRIORITY_224   224
#define PRIORITY_225   225
#define PRIORITY_226   226
#define PRIORITY_227   227
#define PRIORITY_228   228
#define PRIORITY_229   229
#define PRIORITY_230   230
#define PRIORITY_231   231
#define PRIORITY_232   232
#define PRIORITY_233   233
#define PRIORITY_234   234
#define PRIORITY_235   235
#define PRIORITY_236   236
#define PRIORITY_237   237
#define PRIORITY_238   238
#define PRIORITY_239   239
#define PRIORITY_240   240
#define PRIORITY_241   241
#define PRIORITY_242   242
#define PRIORITY_243   243
#define PRIORITY_244   244
#define PRIORITY_245   245
#define PRIORITY_246   246
#define PRIORITY_247   247
#define PRIORITY_248   248
#define PRIORITY_249   249
#define PRIORITY_250   250
#define PRIORITY_251   251
#define PRIORITY_252   252
#define PRIORITY_253   253
#define PRIORITY_254   254
#define PRIORITY_255   255

/**
 * @brief   Controls the specified interrupt in the NVIC.
 * @param   IRQn: The interrupt to be controlled.
 * @param   Copy_Status: The status to be set for the interrupt (enable/disable).
 * @note    This function provides control over the specified interrupt in the Nested Vector Interrupt Controller (NVIC),
 *          allowing for enabling, disabling, or configuring interrupt priority and other settings.
 */
void NVIC_IRQControl(IRQn_t IRQn , u32 Copy_Status);

/**
 * @brief   Sets the priority of the specified interrupt in the NVIC.
 * @param   IRQn: The interrupt for which the priority is to be set.
 * @param   priority: The priority level to be assigned to the interrupt.
 * @note    This function sets the priority level of the specified interrupt in the Nested Vector Interrupt Controller (NVIC).
 */
void NVIC_IRQPriority(IRQn_t IRQn, u32 priority);

/**
 * @brief   Controls the pending status of the specified interrupt in the NVIC.
 * @param   IRQn: The interrupt to be controlled.
 * @param   Copy_Status: The pending status to be set for the interrupt (set/clear).
 * @note    This function allows controlling the pending status of the specified interrupt in the Nested Vector Interrupt Controller (NVIC).
 */
void NVIC_IRQPendingControl(IRQn_t IRQn , u32 Copy_Status);

/**
 * @brief   Gets the active status of the specified interrupt in the NVIC.
 * @param   IRQn: The interrupt for which the active status is to be retrieved.
 * @param   Add_Status: Pointer to a variable to store the active status of the interrupt.
 * @note    This function retrieves the active status of the specified interrupt in the Nested Vector Interrupt Controller (NVIC),
 *          indicating whether the interrupt is currently active or not.
 */
void NVIC_GetActive(IRQn_t IRQn, u32 *Add_Status);


/**
 * @brief   Generates a software interrupt for the specified interrupt in the NVIC.
 * @param   IRQn: The interrupt for which the software interrupt is to be generated.
 * @note    This function generates a software interrupt for the specified interrupt in the Nested Vector Interrupt Controller (NVIC),
 *          allowing software to trigger interrupt handling routines as if the interrupt were triggered by hardware.
 */
void NVIC_GenerateSwINT(IRQn_t IRQn);

/**
 * @brief   Sets the priority grouping field in the NVIC.
 * @param   Copy_PriorityGrouping: The priority grouping value to be set.
 * @note    This function sets the priority grouping field in the Nested Vector Interrupt Controller (NVIC),
 *          which determines the number of bits used for preemption and subpriority levels in the interrupt priority.
 *          Refer to the device reference manual for the supported priority grouping values.
 */
void NVIC_SetPriorityGrouping(u32 Copy_PriorityGrouping);

#endif /* NVIC_H_ */
