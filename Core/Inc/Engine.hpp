/*
 * Engine.hpp
 *
 *  Created on: Mar 25, 2022
 *      Author: Bender
 */

#pragma once

#include "tim.h"

class Engine
{
public:
    Engine(TIM_HandleTypeDef htim) : htim{htim}
    {
        HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1);
        HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_2);
        HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_3);
        HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_4);
    }

    void setSpeed(int16_t speed)
    {
        if (speed > 0)
        {
            if (speed > 1000)
            {
                speed = 1000;
            }
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, 0);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, speed);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_3, 0);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_4, speed);
        }
        else if (speed < 0)
        {
            if (speed < -1000)
            {
                speed = -1000;
            }
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, -speed);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, 0);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_3, -speed);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_4, 0);
        }
        else
        {
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, 0);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, 0);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_3, 0);
            __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_4, 0);
        }
    }

private:
    TIM_HandleTypeDef htim;
};
