//
// Created by 1 on 2023-11-02.
//
#include "Mymain.h"

void Mymain_Init(void)
{
    can1_filter_init();
    can2_filter_init();
    RetargetInit(&huart3);
    HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
}