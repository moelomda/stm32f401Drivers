/**
  ******************************************************************************
  * @file    rcc.h
  * @brief   Header file for Reset and Clock Control (RCC) configuration.
  ******************************************************************************
  * @attention
  *
  * This file contains function prototypes and macros related to configuring
  * the RCC peripheral on the STM32F401 microcontroller. These functions are
  * used to initialize the system clock and perform other RCC-related tasks.
  *
  * @note
  *   - Refer to the STM32F401 reference manual and datasheet for detailed information.
  ******************************************************************************
  */

#include "std_types.h"
#define SYSCLK_HSI 0x01        // High-Speed Internal (HSI) clock index
#define SYSCLK_HSE 0x10000      // High-Speed External (HSE) clock index
#define SYSCLK_PLL 0x1000000    // PLL (Phase-Locked Loop) clock index
#define CLK_OFF 0    // Clock is off
#define CLK_ON  1    // Clock is on

/*--------------------------------------------------PERIPHERAL INDEXES---------------------------------------------------------*/
#define DMA1        0x400000    // Direct Memory Access 1
#define DMA2        0x200000    // Direct Memory Access 2
#define GPIO_A      0x01    // General-Purpose Input/Output Port A
#define GPIO_B      0x02    // General-Purpose Input/Output Port B
#define GPIO_C      0x04    // General-Purpose Input/Output Port C
#define GPIO_D      0x08    // General-Purpose Input/Output Port D
#define GPIO_E      0x10   // General-Purpose Input/Output Port E
#define GPIO_H      0x80    // General-Purpose Input/Output Port h
#define USB_OTG     0x80    // USB On-The-Go
#define PW_INTF     0x10000000    // Power Interface
#define I2C_1       0x00200000    // Inter-Integrated Circuit 1
#define I2C_2       0x00400000    // Inter-Integrated Circuit 2
#define I2C_3       0x00800000    // Inter-Integrated Circuit 3
#define USART1      0x00000010    // Universal Synchronous/Asynchronous Receiver/Transmitter 1
#define USART2      0x00020000    // Universal Synchronous/Asynchronous Receiver/Transmitter 2
#define SPI_1       0x00001000    // Serial Peripheral Interface 1
#define SPI_2       0x00004000    // Serial Peripheral Interface 2
#define SPI_3       0x00008000    // Serial Peripheral Interface 3
#define SPI_4       0x00002000    // Serial Peripheral Interface 4
#define TIM1        0x00000001    // Timer 1
#define TIM2        0x00000001    // Timer 2
#define TIM3        0x00000002    // Timer 3
#define TIM4        0x00000004    // Timer 4
#define TIM5        0x00000008    // Timer 5
#define TIM9        0x00010000   // Timer 9
#define TIM10       0x00020000    // Timer 10
#define TIM11       0x00040000    // Timer 11
#define USART6      0x00000020    // Universal Synchronous/Asynchronous Receiver/Transmitter 6
#define SYS_CFGCTRL 0x00004000   // System Configuration Control
#define ADC1        0x00000100    // Analog-to-Digital Converter 1
#define WINDOW_WD   0x00000800   // Window Watchdog
/*---------------------------------------------------------------------------*prescalers index *-----------------------------------------------------*/
#define MCO1_PRE  0xF8FFFFFF  // Index for MCO1 prescaler
#define MCO2_PRE  0xC7FFFFFF   // Index for MCO2 prescaler
#define AHP_PRE   0xFFFFFF0F   // Index for AHP prescaler
#define APB1_PRE  0xFFFFE3FF   // Index for APB1 prescaler
#define APB2_PRE  0xFFFF1FFF   // Index for APB2 prescaler
#define HSE_PRE   0xFFE0FFFF   // Index for HSE prescaler

/*---------------------------------------------------------------------------*prescalers values *-----------------------------------------------------*/
#define MCO2_2  	 0x20000000
#define MCO2_3  	 0x28000000
#define MCO2_4 	     0x30000000
#define MCO2_5  	 0x38000000
#define MCO1_2  	 0x04000000   // Prescaler value for MCO1: division by 2
#define MCO1_3  	 0x05000000   // Prescaler value for MCO1: division by 3
#define MCO1_4       0x06000000   // Prescaler value for MCO1: division by 4
#define MCO1_5       0x07000000   // Prescaler value for MCO1: division by 5



#define AHP_PRE_2    0x00000080  // Prescaler value for AHP = 2
#define AHP_PRE_4    0x00000090   // Prescaler value for AHP = 4
#define AHP_PRE_8    0x000000A0  // Prescaler value for AHP = 8
#define AHP_PRE_16   0x000000B0   // Prescaler value for AHP = 16
#define AHP_PRE_64   0x000000C0   // Prescaler value for AHP = 64
#define AHP_PRE_128  0x000000D0   // Prescaler value for AHP = 128
#define AHP_PRE_256  0x000000E0   // Prescaler value for AHP = 256
#define AHP_PRE_512  0x000000F0   // Prescaler value for AHP = 512
#define APB1_2       0x00001000
#define APB1_4       0x00001400
#define APB1_8       0x00001800
#define APB1_16      0x00001C00


#define APB2_PRE_2   0x00008000   // Prescaler value for APB2 = 2
#define APB2_PRE_4   0x0000A000   // Prescaler value for APB2 = 4
#define APB2_PRE_8   0x0000C000   // Prescaler value for APB2 = 8
#define APB2_PRE_16  0x0000E000   // Prescaler value for APB2 = 16


#define RTC_PRE_2    0x00020000   // Prescaler value for RTC = 2
#define RTC_PRE_3    0x00030000   // Prescaler value for RTC = 3
#define RTC_PRE_4    0x00040000   // Prescaler value for RTC = 4
#define RTC_PRE_5    0x00050000   // Prescaler value for RTC = 5
#define RTC_PRE_6    0x00060000   // Prescaler value for RTC = 6
#define RTC_PRE_7    0x00070000   // Prescaler value for RTC = 7
#define RTC_PRE_8    0x00080000   // Prescaler value for RTC = 8
#define RTC_PRE_9    0x00090000   // Prescaler value for RTC = 9
#define RTC_PRE_10   0x000A0000   // Prescaler value for RTC = 10
#define RTC_PRE_11   0x000B0000   // Prescaler value for RTC = 11
#define RTC_PRE_12   0x000C0000   // Prescaler value for RTC = 12
#define RTC_PRE_13   0x000D0000   // Prescaler value for RTC = 13
#define RTC_PRE_14   0x000E0000   // Prescaler value for RTC = 14
#define RTC_PRE_15   0x000F0000   // Prescaler value for RTC = 15
#define RTC_PRE_16   0x00100000   // Prescaler value for RTC = 16
#define RTC_PRE_17   0x00110000   // Prescaler value for RTC = 17
#define RTC_PRE_18   0x00120000   // Prescaler value for RTC = 18
#define RTC_PRE_19   0x00130000   // Prescaler value for RTC = 19
#define RTC_PRE_20   0x00140000   // Prescaler value for RTC = 20
#define RTC_PRE_21   0x00150000   // Prescaler value for RTC = 21
#define RTC_PRE_22   0x00160000   // Prescaler value for RTC = 22
#define RTC_PRE_23   0x00170000   // Prescaler value for RTC = 23
#define RTC_PRE_24   0x00180000   // Prescaler value for RTC = 24
#define RTC_PRE_25   0x00190000   // Prescaler value for RTC = 25
#define RTC_PRE_26   0x001A0000   // Prescaler value for RTC = 26
#define RTC_PRE_27   0x001B0000   // Prescaler value for RTC = 27
#define RTC_PRE_28   0x001C0000   // Prescaler value for RTC = 28
#define RTC_PRE_29   0x001D0000   // Prescaler value for RTC = 29
#define RTC_PRE_30   0x001E0000   // Prescaler value for RTC = 30
#define RTC_PRE_31   0x001F0000   // Prescaler value for RTC = 31
/*---------------------------------------------------------------------------*PLL CFG*-----------------------------------------------------------*/
#define PLLP_DIV_2  0x00000000 // PLLP = 2
#define PLLP_DIV_4  0x00010000 // PLLP = 4
#define PLLP_DIV_6  0x00020000 // PLLP = 6
#define PLLP_DIV_8  0x00030000 // PLLP = 8
#define PLLN_VALUE(x)  ((x) << 4)
#define PLLN_192  PLLN_VALUE(192)
#define PLLN_193  PLLN_VALUE(193)
#define PLLN_194  PLLN_VALUE(194)
#define PLLN_195  PLLN_VALUE(195)
#define PLLN_196  PLLN_VALUE(196)
#define PLLN_197  PLLN_VALUE(197)
#define PLLN_198  PLLN_VALUE(198)
#define PLLN_199  PLLN_VALUE(199)
#define PLLN_200  PLLN_VALUE(200)
#define PLLN_201  PLLN_VALUE(201)
#define PLLN_202  PLLN_VALUE(202)
#define PLLN_203  PLLN_VALUE(203)
#define PLLN_204  PLLN_VALUE(204)
#define PLLN_205  PLLN_VALUE(205)
#define PLLN_206  PLLN_VALUE(206)
#define PLLN_207  PLLN_VALUE(207)
#define PLLN_208  PLLN_VALUE(208)
#define PLLN_209  PLLN_VALUE(209)
#define PLLN_210  PLLN_VALUE(210)
#define PLLN_211  PLLN_VALUE(211)
#define PLLN_212  PLLN_VALUE(212)
#define PLLN_213  PLLN_VALUE(213)
#define PLLN_214  PLLN_VALUE(214)
#define PLLN_215  PLLN_VALUE(215)
#define PLLN_216  PLLN_VALUE(216)
#define PLLN_217  PLLN_VALUE(217)
#define PLLN_218  PLLN_VALUE(218)
#define PLLN_219  PLLN_VALUE(219)
#define PLLN_220  PLLN_VALUE(220)
#define PLLN_221  PLLN_VALUE(221)
#define PLLN_222  PLLN_VALUE(222)
#define PLLN_223  PLLN_VALUE(223)
#define PLLN_224  PLLN_VALUE(224)
#define PLLN_225  PLLN_VALUE(225)
#define PLLN_226  PLLN_VALUE(226)
#define PLLN_227  PLLN_VALUE(227)
#define PLLN_228  PLLN_VALUE(228)
#define PLLN_229  PLLN_VALUE(229)
#define PLLN_230  PLLN_VALUE(230)
#define PLLN_231  PLLN_VALUE(231)
#define PLLN_232  PLLN_VALUE(232)
#define PLLN_233  PLLN_VALUE(233)
#define PLLN_234  PLLN_VALUE(234)
#define PLLN_235  PLLN_VALUE(235)
#define PLLN_236  PLLN_VALUE(236)
#define PLLN_237  PLLN_VALUE(237)
#define PLLN_238  PLLN_VALUE(238)
#define PLLN_239  PLLN_VALUE(239)
#define PLLN_240  PLLN_VALUE(240)
#define PLLN_241  PLLN_VALUE(241)
#define PLLN_242  PLLN_VALUE(242)
#define PLLN_243  PLLN_VALUE(243)
#define PLLN_244  PLLN_VALUE(244)
#define PLLN_245  PLLN_VALUE(245)
#define PLLN_246  PLLN_VALUE(246)
#define PLLN_247  PLLN_VALUE(247)
#define PLLN_248  PLLN_VALUE(248)
#define PLLN_249  PLLN_VALUE(249)
#define PLLN_250  PLLN_VALUE(250)
#define PLLN_251  PLLN_VALUE(251)
#define PLLN_252  PLLN_VALUE(252)
#define PLLN_253  PLLN_VALUE(253)
#define PLLN_254  PLLN_VALUE(254)
#define PLLN_255  PLLN_VALUE(255)
#define PLLN_256  PLLN_VALUE(256)
#define PLLN_257  PLLN_VALUE(257)
#define PLLN_258  PLLN_VALUE(258)
#define PLLN_259  PLLN_VALUE(259)
#define PLLN_260  PLLN_VALUE(260)
#define PLLN_261  PLLN_VALUE(261)
#define PLLN_262  PLLN_VALUE(262)
#define PLLN_263  PLLN_VALUE(263)
#define PLLN_264  PLLN_VALUE(264)
#define PLLN_265  PLLN_VALUE(265)
#define PLLN_266  PLLN_VALUE(266)
#define PLLN_267  PLLN_VALUE(267)
#define PLLN_268  PLLN_VALUE(268)
#define PLLN_269  PLLN_VALUE(269)
#define PLLN_270  PLLN_VALUE(270)
#define PLLN_271  PLLN_VALUE(271)
#define PLLN_272  PLLN_VALUE(272)
#define PLLN_273  PLLN_VALUE(273)
#define PLLN_274  PLLN_VALUE(274)
#define PLLN_275  PLLN_VALUE(275)
#define PLLN_276  PLLN_VALUE(276)
#define PLLN_277  PLLN_VALUE(277)
#define PLLN_278  PLLN_VALUE(278)
#define PLLN_279  PLLN_VALUE(279)
#define PLLN_280  PLLN_VALUE(280)
#define PLLN_281  PLLN_VALUE(281)
#define PLLN_282  PLLN_VALUE(282)
#define PLLN_283  PLLN_VALUE(283)
#define PLLN_284  PLLN_VALUE(284)
#define PLLN_285  PLLN_VALUE(285)
#define PLLN_286  PLLN_VALUE(286)
#define PLLN_287  PLLN_VALUE(287)
#define PLLN_288  PLLN_VALUE(288)
#define PLLN_289  PLLN_VALUE(289)
#define PLLN_290  PLLN_VALUE(290)
#define PLLN_291  PLLN_VALUE(291)
#define PLLN_292  PLLN_VALUE(292)
#define PLLN_293  PLLN_VALUE(293)
#define PLLN_294  PLLN_VALUE(294)
#define PLLN_295  PLLN_VALUE(295)
#define PLLN_296  PLLN_VALUE(296)
#define PLLN_297  PLLN_VALUE(297)
#define PLLN_298  PLLN_VALUE(298)
#define PLLN_299  PLLN_VALUE(299)
#define PLLN_300  PLLN_VALUE(300)
#define PLLN_301  PLLN_VALUE(301)
#define PLLN_302  PLLN_VALUE(302)
#define PLLN_303  PLLN_VALUE(303)
#define PLLN_304  PLLN_VALUE(304)
#define PLLN_305  PLLN_VALUE(305)
#define PLLN_306  PLLN_VALUE(306)
#define PLLN_307  PLLN_VALUE(307)
#define PLLN_308  PLLN_VALUE(308)
#define PLLN_309  PLLN_VALUE(309)
#define PLLN_310  PLLN_VALUE(310)
#define PLLN_311  PLLN_VALUE(311)
#define PLLN_312  PLLN_VALUE(312)
#define PLLN_313  PLLN_VALUE(313)
#define PLLN_314  PLLN_VALUE(314)
#define PLLN_315  PLLN_VALUE(315)
#define PLLN_316  PLLN_VALUE(316)
#define PLLN_317  PLLN_VALUE(317)
#define PLLN_318  PLLN_VALUE(318)
#define PLLN_319  PLLN_VALUE(319)
#define PLLN_320  PLLN_VALUE(320)
#define PLLN_321  PLLN_VALUE(321)
#define PLLN_322  PLLN_VALUE(322)
#define PLLN_323  PLLN_VALUE(323)
#define PLLN_324  PLLN_VALUE(324)
#define PLLN_325  PLLN_VALUE(325)
#define PLLN_326  PLLN_VALUE(326)
#define PLLN_327  PLLN_VALUE(327)
#define PLLN_328  PLLN_VALUE(328)
#define PLLN_329  PLLN_VALUE(329)
#define PLLN_330  PLLN_VALUE(330)
#define PLLN_331  PLLN_VALUE(331)
#define PLLN_332  PLLN_VALUE(332)
#define PLLN_333  PLLN_VALUE(333)
#define PLLN_334  PLLN_VALUE(334)
#define PLLN_335  PLLN_VALUE(335)
#define PLLN_336  PLLN_VALUE(336)
#define PLLN_337  PLLN_VALUE(337)
#define PLLN_338  PLLN_VALUE(338)
#define PLLN_339  PLLN_VALUE(339)
#define PLLN_340  PLLN_VALUE(340)
#define PLLN_341  PLLN_VALUE(341)
#define PLLN_342  PLLN_VALUE(342)
#define PLLN_343  PLLN_VALUE(343)
#define PLLN_344  PLLN_VALUE(344)
#define PLLN_345  PLLN_VALUE(345)
#define PLLN_346  PLLN_VALUE(346)
#define PLLN_347  PLLN_VALUE(347)
#define PLLN_348  PLLN_VALUE(348)
#define PLLN_349  PLLN_VALUE(349)
#define PLLN_350  PLLN_VALUE(350)
#define PLLN_351  PLLN_VALUE(351)
#define PLLN_352  PLLN_VALUE(352)
#define PLLN_353  PLLN_VALUE(353)
#define PLLN_354  PLLN_VALUE(354)
#define PLLN_355  PLLN_VALUE(355)
#define PLLN_356  PLLN_VALUE(356)
#define PLLN_357  PLLN_VALUE(357)
#define PLLN_358  PLLN_VALUE(358)
#define PLLN_359  PLLN_VALUE(359)
#define PLLN_360  PLLN_VALUE(360)
#define PLLN_361  PLLN_VALUE(361)
#define PLLN_362  PLLN_VALUE(362)
#define PLLN_363  PLLN_VALUE(363)
#define PLLN_364  PLLN_VALUE(364)
#define PLLN_365  PLLN_VALUE(365)
#define PLLN_366  PLLN_VALUE(366)
#define PLLN_367  PLLN_VALUE(367)
#define PLLN_368  PLLN_VALUE(368)
#define PLLN_369  PLLN_VALUE(369)
#define PLLN_370  PLLN_VALUE(370)
#define PLLN_371  PLLN_VALUE(371)
#define PLLN_372  PLLN_VALUE(372)
#define PLLN_373  PLLN_VALUE(373)
#define PLLN_374  PLLN_VALUE(374)
#define PLLN_375  PLLN_VALUE(375)
#define PLLN_376  PLLN_VALUE(376)
#define PLLN_377  PLLN_VALUE(377)
#define PLLN_378  PLLN_VALUE(378)
#define PLLN_379  PLLN_VALUE(379)
#define PLLN_380  PLLN_VALUE(380)
#define PLLN_381  PLLN_VALUE(381)
#define PLLN_382  PLLN_VALUE(382)
#define PLLN_383  PLLN_VALUE(383)
#define PLLN_384  PLLN_VALUE(384)
#define PLLN_385  PLLN_VALUE(385)
#define PLLN_386  PLLN_VALUE(386)
#define PLLN_387  PLLN_VALUE(387)
#define PLLN_388  PLLN_VALUE(388)
#define PLLN_389  PLLN_VALUE(389)
#define PLLN_390  PLLN_VALUE(390)
#define PLLN_391  PLLN_VALUE(391)
#define PLLN_392  PLLN_VALUE(392)
#define PLLN_393  PLLN_VALUE(393)
#define PLLN_394  PLLN_VALUE(394)
#define PLLN_395  PLLN_VALUE(395)
#define PLLN_396  PLLN_VALUE(396)
#define PLLN_397  PLLN_VALUE(397)
#define PLLN_398  PLLN_VALUE(398)
#define PLLN_399  PLLN_VALUE(399)
#define PLLN_400  PLLN_VALUE(400)
#define PLLN_401  PLLN_VALUE(401)
#define PLLN_402  PLLN_VALUE(402)
#define PLLN_403  PLLN_VALUE(403)
#define PLLN_404  PLLN_VALUE(404)
#define PLLN_405  PLLN_VALUE(405)
#define PLLN_406  PLLN_VALUE(406)
#define PLLN_407  PLLN_VALUE(407)
#define PLLN_408  PLLN_VALUE(408)
#define PLLN_409  PLLN_VALUE(409)
#define PLLN_410  PLLN_VALUE(410)
#define PLLN_411  PLLN_VALUE(411)
#define PLLN_412  PLLN_VALUE(412)
#define PLLN_413  PLLN_VALUE(413)
#define PLLN_414  PLLN_VALUE(414)
#define PLLN_415  PLLN_VALUE(415)
#define PLLN_416  PLLN_VALUE(416)
#define PLLN_417  PLLN_VALUE(417)
#define PLLN_418  PLLN_VALUE(418)
#define PLLN_419  PLLN_VALUE(419)
#define PLLN_420  PLLN_VALUE(420)
#define PLLN_421  PLLN_VALUE(421)
#define PLLN_422  PLLN_VALUE(422)
#define PLLN_423  PLLN_VALUE(423)
#define PLLN_424  PLLN_VALUE(424)
#define PLLN_425  PLLN_VALUE(425)
#define PLLN_426  PLLN_VALUE(426)
#define PLLN_427  PLLN_VALUE(427)
#define PLLN_428  PLLN_VALUE(428)
#define PLLN_429  PLLN_VALUE(429)
#define PLLN_430  PLLN_VALUE(430)
#define PLLN_431  PLLN_VALUE(431)
#define PLLN_432  PLLN_VALUE(432)

#define PLLM_VALUE(x)    ((x) << 0)

#define PLLM_2    PLLM_VALUE(2)
#define PLLM_3    PLLM_VALUE(3)
#define PLLM_4    PLLM_VALUE(4)
#define PLLM_5    PLLM_VALUE(5)
#define PLLM_6    PLLM_VALUE(6)
#define PLLM_7    PLLM_VALUE(7)
#define PLLM_8    PLLM_VALUE(8)
#define PLLM_9    PLLM_VALUE(9)
#define PLLM_10   PLLM_VALUE(10)
#define PLLM_11   PLLM_VALUE(11)
#define PLLM_12   PLLM_VALUE(12)
#define PLLM_13   PLLM_VALUE(13)
#define PLLM_14   PLLM_VALUE(14)
#define PLLM_15   PLLM_VALUE(15)
#define PLLM_16   PLLM_VALUE(16)
#define PLLM_17   PLLM_VALUE(17)
#define PLLM_18   PLLM_VALUE(18)
#define PLLM_19   PLLM_VALUE(19)
#define PLLM_20   PLLM_VALUE(20)
#define PLLM_21   PLLM_VALUE(21)
#define PLLM_22   PLLM_VALUE(22)
#define PLLM_23   PLLM_VALUE(23)
#define PLLM_24   PLLM_VALUE(24)
#define PLLM_25   PLLM_VALUE(25)
#define PLLM_26   PLLM_VALUE(26)
#define PLLM_27   PLLM_VALUE(27)
#define PLLM_28   PLLM_VALUE(28)
#define PLLM_29   PLLM_VALUE(29)
#define PLLM_30   PLLM_VALUE(30)
#define PLLM_31   PLLM_VALUE(31)
#define PLLM_32   PLLM_VALUE(32)
#define PLLM_33   PLLM_VALUE(33)
#define PLLM_34   PLLM_VALUE(34)
#define PLLM_35   PLLM_VALUE(35)
#define PLLM_36   PLLM_VALUE(36)
#define PLLM_37   PLLM_VALUE(37)
#define PLLM_38   PLLM_VALUE(38)
#define PLLM_39   PLLM_VALUE(39)
#define PLLM_40   PLLM_VALUE(40)
#define PLLM_41   PLLM_VALUE(41)
#define PLLM_42   PLLM_VALUE(42)
#define PLLM_43   PLLM_VALUE(43)
#define PLLM_44   PLLM_VALUE(44)
#define PLLM_45   PLLM_VALUE(45)
#define PLLM_46   PLLM_VALUE(46)
#define PLLM_47   PLLM_VALUE(47)
#define PLLM_48   PLLM_VALUE(48)
#define PLLM_49   PLLM_VALUE(49)
#define PLLM_50   PLLM_VALUE(50)
#define PLLM_51   PLLM_VALUE(51)
#define PLLM_52   PLLM_VALUE(52)
#define PLLM_53   PLLM_VALUE(53)
#define PLLM_54   PLLM_VALUE(54)
#define PLLM_55   PLLM_VALUE(55)
#define PLLM_56   PLLM_VALUE(56)
#define PLLM_57   PLLM_VALUE(57)
#define PLLM_58   PLLM_VALUE(58)
#define PLLM_59   PLLM_VALUE(59)
#define PLLM_60   PLLM_VALUE(60)
#define PLLM_61   PLLM_VALUE(61)
#define PLLM_62   PLLM_VALUE(62)
#define PLLM_63   PLLM_VALUE(63)

typedef enum
{
   Rcc_enuInvalidClkName,  // Error: Invalid clock name
   Rcc_enuInvalidClkState, // Error: Invalid clock state
   Rcc_enuSucceded,        // Success: Operation succeeded
   Rcc_enuCantCloseClk,    // Error: Unable to close the clock
   Rcc_enuCLkNotReady,     // Error: Clock is not ready
   Rcc_enuInvalidperName,
   Rcc_ennInvalidpresclrname,
   Rcc_enuCantCfgPllOn,
} Rcc_ErrorStatus_t;

/**
  ******************************************************************************
  * @file    rcc_config.h
  * @brief   RCC Clock Control API
  ******************************************************************************
  * @attention
  *
  * This API provides functions for enabling or disabling various clocks
  * in the Reset and Clock Control (RCC) peripheral of a microcontroller,
  * such as the STM32 series.
  *
  ******************************************************************************
  * @param   Copy_u8ClkName: Clock name to be configured.
  *
  * @param   Copy_u8ClkState: Desired clock state.
  *            - Options: RCC_CLOCK_ON, RCC_CLOCK_OFF
  * @retval  Rcc_ErrorStatus_t: Status indicating success or error.
  *
  ******************************************************************************
  * @note
  *   - The API allows controlling the state (ON or OFF) of various clocks.
  *   - 'Copy_u8ClkName' parameter specifies the clock domain to be configured.
  *   - 'Copy_u8ClkState' parameter sets the desired state of the clock (ON or OFF).
  ******************************************************************************
  */
Rcc_ErrorStatus_t Rcc_SetClkOnOff(u32 Copy_u32ClkName, u8 Copy_u8ClkState);
/**
  ******************************************************************************
  * @brief  Sets the system clock to the specified clock source.
  ******************************************************************************
  * | Parameter     | Description                                   |
  * |---------------|-----------------------------------------------|
  * | Copy_u8ClkName| Clock name to be set as the system clock.     |
  * |               | Options: HSI_CLK, HSE_CLK, PLL_CLK            |
  ******************************************************************************
  * @retval Rcc_ErrorStatus_t: Status indicating success or error.
  ******************************************************************************
  * | Return Value               | Description                             |
  * |----------------------------|-----------------------------------------|
  * | Rcc_enuSucceded            | Operation succeeded.                    |
  * | Rcc_enuInvalidClkName      | Specified clock name is invalid.        |
  * | Rcc_enuClkNotReady         | Specified clock is not ready.           |
  ******************************************************************************
  * @note
  *   - To set a clock as the system clock, it must be turned on and ready.
  *   - This function checks if the specified clock is ready and then sets
  *     it as the system clock. If the clock is not ready or an invalid clock
  *     name is provided, it returns an appropriate error status.
  ******************************************************************************
  */

Rcc_ErrorStatus_t Rcc_SetSysClk(u32 Copy_u32ClkName);
/**
  ******************************************************************************
  * @brief  Enables or disables a peripheral.
  ******************************************************************************
  * | Parameter     | Description                                   |
  * |---------------|-----------------------------------------------|
  * | Copy_u8Name   | Peripheral to be enabled or disabled.         |
  * |               | Options: DMA1, DMA2, GPIO_A, GPIO_B, ...      |
  * | Copy_u8State  | State to set for the peripheral.              |
  * |               | Options: CLK_ON (enable), CLK_OFF (disable)  |
  ******************************************************************************
  * @retval Rcc_ErrorStatus_t: Status indicating success or error.
  ******************************************************************************
  * | Return Value            | Description                            |
  * |-------------------------|----------------------------------------|
  * | Rcc_enuSucceded         | Operation succeeded.                   |
  * | Rcc_enuInvalidClkName   | Specified peripheral name is invalid.  |
  ******************************************************************************
  * @note
  *   - This function enables or disables a peripheral based on the provided
  *     peripheral name and state.
  ******************************************************************************
  */


Rcc_ErrorStatus_t Rcc_SetPeripheralOnOff(u32 Copy_u32Name , u8 Copy_u8State );

/**
  ******************************************************************************
  * @brief  Sets the prescaler value for a specific peripheral.
  ******************************************************************************
  * | Parameter     | Description                                   |
  * |---------------|-----------------------------------------------|
  * | Copy_u8Name   | Peripheral name to set the prescaler for.     |
  * |               | Options: Refer to the peripheral names.       |
  * | Copy_u8Value  | Value to set as the prescaler for the peripheral.|
  * |               | Value range depends on the specific peripheral.|
  ******************************************************************************
  * @retval Rcc_ErrorStatus_t: Status indicating success or error.
  ******************************************************************************
  * | Return Value               | Description                             |
  * |----------------------------|-----------------------------------------|
  * | Rcc_enuSucceded            | Operation succeeded.                    |
  * | Rcc_enuInvalidClkName      | Specified peripheral name is invalid.   |
  * | Rcc_enuInvalidValue        | Specified prescaler value is invalid.   |
  ******************************************************************************
  * @note
  *   - This function sets the prescaler value for a specific peripheral.
  *   - The valid range of prescaler values depends on the specific peripheral.
  *   - If the specified peripheral name is invalid or the prescaler value is
  *     out of range, it returns an appropriate error status.
  ******************************************************************************
  */

Rcc_ErrorStatus_t Rcc_SetPreScaler(u32 Copy_u8Name , u32 Copy_u8Value);
/**
  ******************************************************************************
  * @brief  Adjusts the PLL configuration
  ******************************************************************************
  * @param  copy_u8ClkSrc: Source of the PLL clock.
  *         - Options: HSE_CLK, HSI_CLK
  * @param  Copy_u8_MValue: Desired value for the PLL clock's M factor.
  * @param  Copy_u8_NValue: Desired value for the PLL clock's N factor.
  * @param  Copy_u8_PValue: Desired value for the PLL clock's P factor.
  * @retval Rcc_ErrorStatus_t: Status indicating success or error.
  *         - Rcc_enuSucceded: Operation succeeded.
  *         - Rcc_enuInvalidClkName: Specified name is invalid.
  *         - Rcc_enuInvalidValue: Specified configuration value is invalid.
  ******************************************************************************
  * @note
  *   - This function adjusts the PLL configuration.
  *   - The valid range and interpretation of the configuration values depend
  *     on the chosen PLL clock source (HSE or HSI).
  ******************************************************************************
  */
Rcc_ErrorStatus_t Rcc_SetPLLCfg   (u32 copy_u32ClkSrc  , u32 CopyMValue , u32 CopyNValue , u32 CopyPValue);

