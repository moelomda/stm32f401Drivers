#include "LCD.h"
LCD_Str_t LCD_config = {
    // Configuration for LCD_StrRsReg (Register Select pin)
    .LCD_StrRsReg = {
        .GPIO_Port = PORT_A,                // GPIO port for Register Select pin
        .GPIO_Pin = GPIO_PIN_0,             // GPIO pin for Register Select pin
        .GPIO_Direction = GPIO_OUTPUT,      // GPIO direction for Register Select pin (output)
        .GPIO_Mode = GPIO_OTYPE_PUSHPULL    // GPIO mode for Register Select pin (push-pull)
    },
    // Configuration for LCD_StrEnReg (Enable pin)
    .LCD_StrEnReg = {
        .GPIO_Port = PORT_A,                // GPIO port for Enable pin
        .GPIO_Pin = GPIO_PIN_1,             // GPIO pin for Enable pin
        .GPIO_Direction = GPIO_OUTPUT,      // GPIO direction for Enable pin (output)
        .GPIO_Mode = GPIO_OTYPE_PUSHPULL    // GPIO mode for Enable pin (push-pull)
    },
    // Configuration for LCD_StrDataReg (Data pins)
    .LCD_StrDataReg = {
        // Configuration for LCD_StrDataReg[0]
        [0] = {
            .GPIO_Port = PORT_A,                // GPIO port for Data pin 0
            .GPIO_Pin = GPIO_PIN_2,             // GPIO pin for Data pin 0
            .GPIO_Direction = GPIO_OUTPUT,      // GPIO direction for Data pin 0 (output)
            .GPIO_Mode = GPIO_OTYPE_PUSHPULL    // GPIO mode for Data pin 0 (push-pull)
        },
        // Configuration for LCD_StrDataReg[1]
        [1] = {
            .GPIO_Port = PORT_A,                // GPIO port for Data pin 1
            .GPIO_Pin = GPIO_PIN_3,             // GPIO pin for Data pin 1
            .GPIO_Direction = GPIO_OUTPUT,      // GPIO direction for Data pin 1 (output)
            .GPIO_Mode = GPIO_OTYPE_PUSHPULL    // GPIO mode for Data pin 1 (push-pull)
        },
        // Repeat the above configuration for Data pins [2] to [5]
        // Configuration for LCD_StrDataReg[2]
        [2] = {
            .GPIO_Port = PORT_A,
            .GPIO_Pin = GPIO_PIN_4,
            .GPIO_Direction = GPIO_OUTPUT,
            .GPIO_Mode = GPIO_OTYPE_PUSHPULL
        },
        // Configuration for LCD_StrDataReg[3]
        [3] = {
            .GPIO_Port = PORT_A,
            .GPIO_Pin = GPIO_PIN_5,
            .GPIO_Direction = GPIO_OUTPUT,
            .GPIO_Mode = GPIO_OTYPE_PUSHPULL
        },
        // Configuration for LCD_StrDataReg[4]
        [4] = {
            .GPIO_Port = PORT_A,
            .GPIO_Pin = GPIO_PIN_6,
            .GPIO_Direction = GPIO_OUTPUT,
            .GPIO_Mode = GPIO_OTYPE_PUSHPULL
        },
        // Configuration for LCD_StrDataReg[5]
        [5] = {
            .GPIO_Port = PORT_A,
            .GPIO_Pin = GPIO_PIN_7,
            .GPIO_Direction = GPIO_OUTPUT,
            .GPIO_Mode = GPIO_OTYPE_PUSHPULL
        },
        // Configuration for LCD_StrDataReg[6] (Using PORTB)
        [6] = {
            .GPIO_Port = PORT_B,
            .GPIO_Pin = GPIO_PIN_0,
            .GPIO_Direction = GPIO_OUTPUT,
            .GPIO_Mode = GPIO_OTYPE_PUSHPULL
        },
        // Configuration for LCD_StrDataReg[7] (Using PORTB)
        [7] = {
            .GPIO_Port = PORT_B,
            .GPIO_Pin = GPIO_PIN_1,
            .GPIO_Direction = GPIO_OUTPUT,
            .GPIO_Mode = GPIO_OTYPE_PUSHPULL
        }
    }
};
