/*
 * engineController.hpp
 *
 *  Created on: Mar 30, 2022
 *      Author: Bender
 */

#pragma once
#include "EngineImpl.hpp"
#include "PidControllerImpl.hpp"

#define ENCODER_RESOLUTION 8
#define TIMER_CONF_BOTH_EDGE_T1T2 4
#define MOTOR_GEAR 120 // 120
#define TIMER_FREQENCY 20
#define SECOND_IN_MINUTE 60

struct engineParams
{
    int32_t measuredSpeed{0}; // prędkość silnika
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
    virtual int getPWM() = 0;
    // virtual void measureSpeed() = 0;
};
class EngineController : public IEngineController
{
public:
    EngineController(TIM_HandleTypeDef timer, Engine* ptr, engineParams& param)
        : //		measuredSpeed{0},
          //		adjustedSpeed{0},
          //		actualPWM{0},
        encoderTimer{timer}
        , encoderResolution{ENCODER_RESOLUTION * TIMER_CONF_BOTH_EDGE_T1T2 * MOTOR_GEAR}
        ,
        //		countedPulses{0},
        usedEngine{ptr}
        , params{param}
    {
        HAL_TIM_Encoder_Start(&timer, TIM_CHANNEL_ALL);
        usedPid = new PidController(test2);
    }
    ~EngineController() override { delete usedPid; }

    void setSpeed(int32_t newSpeed) override
    {
        if (newSpeed != params.adjustedSpeed) usedPid->resetPidErrors();
        params.adjustedSpeed = newSpeed;
    }

    void calculateSpeed() override
    {
        updateCount();
        params.measuredSpeed =
            (this->params.countedPulses * TIMER_FREQENCY * SECOND_IN_MINUTE) / this->encoderResolution;
        auto pidResponse = usedPid->calculatePidResponse(params.adjustedSpeed, params.measuredSpeed);
        params.outTest = pidResponse;
        params.actualPWM = +pidResponse;
        usedEngine->setSpeed(params.actualPWM);
    }
    //  void measureSpeed() override {
    //    updateCount();
    //    usedEngine->setSpeed(params.adjustedSpeed);
    //  }
    int getPWM() override { return params.actualPWM; }

private:
    void updateCount()
    {
        this->params.countedPulses = (int16_t)__HAL_TIM_GET_COUNTER(&encoderTimer);
        __HAL_TIM_SET_COUNTER(&encoderTimer, 0);
    }
    //
    //	int32_t measuredSpeed;			// prędkość silnika
    //	int32_t adjustedSpeed;
    //	int32_t actualPWM;
    TIM_HandleTypeDef encoderTimer;
    uint16_t encoderResolution;
    //	int32_t countedPulses;
    PidController* usedPid;
    Engine* usedEngine;
    engineParams& params;

    //	int32_t outTest;
};
