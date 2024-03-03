/*
 * Stm32F401C_Interrupts.h
 *
 *  Created on: ???/???/????
 *      Author: Mohamed Elomda
 */

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
    WWDG_IRQ = 0,
    EXTI16_PVD_IRQ,
    EXTI21_TAMP_STAMP_IRQ,
    EXTI22_RTC_WKUP_IRQ,
    FLASH_IRQ,
    RCC_IRQ,
    EXTI0_IRQ,
    EXTI1_IRQ,
    EXTI2_IRQ,
    EXTI3_IRQ,
    EXTI4_IRQ,
    DMA1_Stream0_IRQ,
    DMA1_Stream1_IRQ,
    DMA1_Stream2_IRQ,
    DMA1_Stream3_IRQ,
    DMA1_Stream4_IRQ,
    DMA1_Stream5_IRQ,
    DMA1_Stream6_IRQ,
    ADC1_IRQ,
    EXTI9_5_IRQ,
    TIM1_BRK_TIM9_IRQ,
    TIM1_UP_TIM10_IRQ,
    TIM1_TRG_COM_TIM11_IRQ,
    TIM1_CC_IRQ,
    TIM2_IRQ,
    TIM3_IRQ,
    TIM4_IRQ,
    I2C1_EV_IRQ,
    I2C1_ER_IRQ,
    I2C2_EV_IRQ,
    I2C2_ER_IRQ,
    SPI1_IRQ,
    SPI2_IRQ,
    USART1_IRQ,
    USART2_IRQ,
    EXTI15_10_IRQ,
    EXTI17_RTC_Alarm_IRQ,
    EXTI18_OTG_FS_WKUP_IRQ,
    DMA1_Stream7_IRQ,
    SDIO_IRQ,
    TIM5_IRQ,
    SPI3_IRQ,
    DMA2_Stream0_IRQ,
    DMA2_Stream1_IRQ,
    DMA2_Stream2_IRQ,
    DMA2_Stream3_IRQ,
    DMA2_Stream4_IRQ,
    OTG_FS_IRQ,
    DMA2_Stream5_IRQ,
    DMA2_Stream6_IRQ,
    DMA2_Stream7_IRQ,
    USART6_IRQ,
    I2C3_EV_IRQ,
    I2C3_ER_IRQ,
    FPU_IRQ,
    SPI4_IRQ
}IRQn_t;
#endif /* STM32F401C_INTERRUPTS_H_ */
