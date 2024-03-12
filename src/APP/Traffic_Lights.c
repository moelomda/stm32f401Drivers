/*
 * Traffic_Lights.c
 *
 *  Created on: March 12, 2024
 *      Author: Mohamed Elomda
 */

#include "LED.h"

#define PERIODICTY    1

u8 Prev = 0;

typedef enum {
    green,
    yellow,
    red,
} Traffic_enuState_t;

Traffic_enuState_t light;

void GreenOn() {
    LED_SetLedState(led_Green , LED_ON);
    LED_SetLedState(led_Yellow , LED_OFF);
    LED_SetLedState(led_Red , LED_OFF);
}

void YellowOn() {
    LED_SetLedState(led_Green , LED_OFF);
    LED_SetLedState(led_Yellow , LED_ON);
    LED_SetLedState(led_Red , LED_OFF);
}

void RedOn() {
    LED_SetLedState(led_Green , LED_OFF);
    LED_SetLedState(led_Yellow , LED_OFF);
    LED_SetLedState(led_Red , LED_ON);
}

void Traffic_Runnable() {
    static u32 TimeMs = 0;
    TimeMs += PERIODICTY ;

    switch(light) {
        case green:
            GreenOn();
            if(TimeMs == 6) {
                TimeMs = 0;
                light = yellow ;
                Prev = green;
            }
            break;

        case yellow:
            YellowOn();
            if((TimeMs == 2) && (Prev == green)) {
                TimeMs = 0;
                light = red;
                Prev = yellow;
            }
            else if((TimeMs == 2) && (Prev == red)) {
                TimeMs = 0;
                light = green;
                Prev = yellow;
            }
            break;

        case red:
            RedOn();
            if(TimeMs == 3)
                TimeMs = 0;
            light = yellow;
            Prev = red;
            break;
    }
}
