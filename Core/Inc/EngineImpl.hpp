/*
 * Engine.hpp
 *
 *  Created on: Mar 25, 2022
 *      Author: Bender
 */

#pragma once

#include "tim.h"
struct engP
{
    uint32_t speed{0};
};

class Engine
{
public:
    Engine(TIM_HandleTypeDef htim, engP& dart) : htim{htim}, dart{dart}
    {
        HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1);
        HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_2);
        HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_3);
        HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_4);
    }

    void setSpeed(int32_t receivedSpeed)
    {
        if (receivedSpeed > 0)
        {
            // if (receivedSpeed > 100) receivedSpeed = 100;
            dart.speed = receivedSpeed + 500; //* slope + startValue;
            up();
        }
        else if (receivedSpeed < 0)
        {
            // if (receivedSpeed < -100) receivedSpeed = -100;
            dart.speed = (-receivedSpeed); //* slope + startValue;
            down();
        }
        else
        {
            fullStop();
        }
    }

private:
    void up()
    {
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, dart.speed);
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, 0);
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_3, dart.speed);
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_4, 0);
    }
    void down()
    {
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, dart.speed);
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_3, 0);
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_4, dart.speed);
    }
    void fullStop()
    {
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, 0);
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_3, 0);
        __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_4, 0);
    }

    TIM_HandleTypeDef htim;
    uint32_t speed;
    engP& dart;
    const uint16_t startValue{600}; // 600
    const uint8_t slope{6}; // 6 // 1200/100 = 12 - so setting up
};
