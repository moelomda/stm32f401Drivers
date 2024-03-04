
#ifndef STM32F401C_INTERRUPTS_H_
#define STM32F401C_INTERRUPTS_H_
/**
 * @brief Enumeration of STM32F401C Drivers Interrupts.
 *
 * This enumeration lists the interrupts available in the STM32F401C microcontroller.
 * Each interrupt is assigned a unique identifier starting from 0.
 *
 * The interrupt identifiers are as follows:
 *   - WWDG_IRQ: Window Watchdog interrupt
 *   - EXTI16_PVD_IRQ: EXTI Line 16/PVD interrupt
 *   - EXTI21_TAMP_STAMP_IRQ: EXTI Line 21/Tamper and TimeStamp interrupt
 *   - EXTI22_RTC_WKUP_IRQ: EXTI Line 22/RTC Wakeup interrupt
 *   - FLASH_IRQ: Flash global interrupt
 *   - RCC_IRQ: RCC global interrupt
 *   - EXTI0_IRQ: EXTI Line0 interrupt
 *   - EXTI1_IRQ: EXTI Line1 interrupt
 *   - EXTI2_IRQ: EXTI Line2 interrupt
 *   - EXTI3_IRQ: EXTI Line3 interrupt
 *   - EXTI4_IRQ: EXTI Line4 interrupt
 *   - DMA1_Stream0_IRQ: DMA1 Stream0 global interrupt
 *   - DMA1_Stream1_IRQ: DMA1 Stream1 global interrupt
 *   - DMA1_Stream2_IRQ: DMA1 Stream2 global interrupt
 *   - DMA1_Stream3_IRQ: DMA1 Stream3 global interrupt
 *   - DMA1_Stream4_IRQ: DMA1 Stream4 global interrupt
 *   - DMA1_Stream5_IRQ: DMA1 Stream5 global interrupt
 *   - DMA1_Stream6_IRQ: DMA1 Stream6 global interrupt
 *   - ADC1_IRQ: ADC1 global interrupt
 *   - EXTI9_5_IRQ: EXTI Line[9:5] interrupts
 *   - TIM1_BRK_TIM9_IRQ: TIM1 Break and TIM9 global interrupt
 *   - TIM1_UP_TIM10_IRQ: TIM1 Update and TIM10 global interrupt
 *   - TIM1_TRG_COM_TIM11_IRQ: TIM1 Trigger, Commutation, and TIM11 global interrupt
 *   - TIM1_CC_IRQ: TIM1 Capture Compare interrupt
 *   - TIM2_IRQ: TIM2 global interrupt
 *   - TIM3_IRQ: TIM3 global interrupt
 *   - TIM4_IRQ: TIM4 global interrupt
 *   - I2C1_EV_IRQ: I2C1 event interrupt
 *   - I2C1_ER_IRQ: I2C1 error interrupt
 *   - I2C2_EV_IRQ: I2C2 event interrupt
 *   - I2C2_ER_IRQ: I2C2 error interrupt
 *   - SPI1_IRQ: SPI1 global interrupt
 *   - SPI2_IRQ: SPI2 global interrupt
 *   - USART1_IRQ: USART1 global interrupt
 *   - USART2_IRQ: USART2 global interrupt
 *   - EXTI15_10_IRQ: EXTI Line[15:10] interrupts
 *   - EXTI17_RTC_Alarm_IRQ: EXTI Line 17/RTC Alarm interrupt
 *   - EXTI18_OTG_FS_WKUP_IRQ: EXTI Line 18/OTG FS Wakeup interrupt
 *   - DMA1_Stream7_IRQ: DMA1 Stream7 global interrupt
 *   - SDIO_IRQ: SDIO global interrupt
 *   - TIM5_IRQ: TIM5 global interrupt
 *   - SPI3_IRQ: SPI3 global interrupt
 *   - DMA2_Stream0_IRQ: DMA2 Stream0 global interrupt
 *   - DMA2_Stream1_IRQ: DMA2 Stream1 global interrupt
 *   - DMA2_Stream2_IRQ: DMA2 Stream2 global interrupt
 *   - DMA2_Stream3_IRQ: DMA2 Stream3 global interrupt
 *   - DMA2_Stream4_IRQ: DMA2 Stream4 global interrupt
 *   - OTG_FS_IRQ: OTG FS global interrupt
 *   - DMA2_Stream5_IRQ: DMA2 Stream5 global interrupt
 *   - DMA2_Stream6_IRQ: DMA2 Stream6 global interrupt
 *   - DMA2_Stream7_IRQ: DMA2 Stream7 global interrupt
 *   - USART6_IRQ: USART6 global interrupt
 *   - I2C3_EV_IRQ: I2C3 event interrupt
 *   - I2C3_ER_IRQ: I2C3 error interrupt
 *   - FPU_IRQ: FPU global interrupt
 *   - SPI4_IRQ: SPI4 global interrupt
 */
typedef enum {
    NVIC_WINDOW_WATCHDOG_TIMER = 0,
    NIVC_EXTERNAL_LINE16 = 1,
    NIVC_EXTERNAL_LINE21 = 2,
    NIVC_EXTERNAL_LINE22 = 3,
    NIVC_FLASH_INTERRUPT = 4,
    NVIC_RCC_INTERRUPT = 5,
    NVIC_EXT0_INTERRRUPT = 6,
    NVIC_EXT1_INTERRRUPT = 7,
    NVIC_EXT2_INTERRRUPT = 8,
    NVIC_EXT3_INTERRRUPT = 9,
    NVIC_EXT4_INTERRRUPT = 10,
    NVIC_DMA1_STREAM0 = 11,
    NVIC_DMA1_STREAM1 = 12,
    NVIC_DMA1_STREAM2 = 13,
    NVIC_DMA1_STREAM3 = 14,
    NVIC_DMA1_STREAM4 = 15,
    NVIC_DMA1_STREAM5 = 16,
    NVIC_DMA1_STREAM6 = 17,
    NVIC_ADC_INTERRUPT = 18,
    NVIC_EXT9_INTERRUPT = 23,
    NVIC_TIM1_BRK_INTERRUPT = 24,
    NVIC_TIM1_UP_INTERRUPT = 25,
    NVIC_TIMI1_TRG_INTERRUPT = 26,
    NVIC_TIMI1_CC_INTERRUPT = 27,
    NVIC_TIMI2_INTERRUPT = 28,
    NVIC_TIMI3_INTERRUPT = 29,
    NVIC_TIMI4_INTERRUPT = 30,
    NVIC_I2C1_EV_INTERRUPT = 31,
    NVIC_I2C1_ER_INTERRUPT = 32,
    NVIC_I2C2_EV_INTERRUPT = 33,
    NVIC_I2C2_ER_INTERRUPT = 34,
    NVIC_SPI1_INTERRUPT = 35,
    NVIC_SPI2_INTERRUPT = 36,
    NVIC_USART1_INTERRUPT = 37,
    NVIC_USART2_INTERRUPT = 38,
    NVIC_EXTI15_INTERRUPT = 40,
    NVIC_EXTI17_INTERRUPT = 41,
    NVIC_EXTI18_INTERRUPT = 42,
    NVIC_DMA1_INTERRUPT = 47,
    NVIC_SDIO_INTERRUPT = 49,
    NVIC_TIM5_INTERRUPT = 50,
    NVIC_SPI3_INTERRUPT = 51,
    NVIC_DMA2_STREAM0_INTERRUPT = 56,
    NVIC_DMA2_STREAM1_INTERRUPT = 57,
    NVIC_DMA2_STREAM2_INTERRUPT = 58,
    NVIC_DMA2_STREAM3_INTERRUPT = 59,
    NVIC_DMA2_STREAM4_INTERRUPT = 60,
    NVIC_OTG_FS_INTERRUPT = 67,
    NVIC_DMA2_STREAM5_INTERRUPT = 68,
    NVIC_DMA2_STREAM6_INTERRUPT = 69,
    NVIC_DMA2_STREAM7_INTERRUPT = 70,
    NVIC_USART6_INTERRUPT = 71,
    NVIC_I2C3_EV_INTERRUPT = 72,
    NVIC_I2C3_ER_INTERRUPT = 73,
    NVIC_FPU_INTERRUPT = 81,
    NVIC_SPI4_INTERRUPT = 84,
	NVIC_IRQNumber
} IRQn_t;
#endif /* STM32F401C_INTERRUPTS_H_ */
