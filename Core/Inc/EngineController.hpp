/*
 * engineController.hpp
 *
 *  Created on: Mar 30, 2022
 *      Author: Bender
 */

#pragma once
#include "Engine.hpp"
#include "PidController.hpp"

#define ENCODER_RESOLUTION 8
#define TIMER_CONF_BOTH_EDGE_T1T2 4
#define MOTOR_GEAR 120
#define TIMER_FREQENCY 10
#define SECOND_IN_MINUTE 60

struct engineParams
{
    int32_t measuredSpeed{0};
    int32_t adjustedSpeed{0};
    int32_t actualPWM{0};
    int32_t countedPulses{0};
    int32_t outTest{0};
};

class IEngineController
{
public:
    virtual ~IEngineController() = default;
    virtual void setSpeed(int32_t) = 0;
    virtual void calculateSpeed() = 0;
};
class EngineController : public IEngineController
{
public:
    EngineController(TIM_HandleTypeDef timer, Engine* ptr, engineParams& param)
        : encoderTimer{timer}
        , encoderResolution{ENCODER_RESOLUTION * TIMER_CONF_BOTH_EDGE_T1T2 * MOTOR_GEAR}
        , usedEngine{ptr}
        , params{param}
    {
        HAL_TIM_Encoder_Start(&timer, TIM_CHANNEL_ALL);
        usedPid = new PidController();
    }
    ~EngineController() override { delete usedPid; }

    void setSpeed(int32_t newSpeed) override;

    void calculateSpeed() override;

private:
    void updateCount();

    TIM_HandleTypeDef encoderTimer;
    uint16_t encoderResolution;
    PidController* usedPid;
    Engine* usedEngine;
    engineParams& params;
};
