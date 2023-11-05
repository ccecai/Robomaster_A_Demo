//
// Created by 1 on 2023-11-04.
//

#ifndef ROBOMASTER_A_LED_H
#define ROBOMASTER_A_LED_H

#include "gpio.h"

#define BUZZER_ON __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,1000)
#define BUZZER_OFF __HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,0)

void LED1_Flash(void);
void LED2_Flash(void);
void WaterLED(void);

#endif //ROBOMASTER_A_LED_H
