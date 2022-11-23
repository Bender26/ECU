#pragma once

#include "Engine.hpp"
#include "PidController.hpp"

constexpr int resolution{8};
constexpr int timerBothEdges{4};
constexpr int gear{120};
constexpr int measurementFrequency{10};
constexpr int seconds{60};

struct engineParams
{
    int16_t measuredSpeed{0};
    int16_t adjustedSpeed{0};
    int16_t actualPWM{0};
    int16_t countedPulses{0};
};

class IEngineController
{
public:
    virtual ~IEngineController() = default;
    virtual void setSpeed(int16_t) = 0;
    virtual void calculatePWMOutput() = 0;
    virtual void stopEngine() = 0;
};
class EngineController : public IEngineController
{
public:
    EngineController(TIM_HandleTypeDef timer, Engine* ptr, engineParams& param)
        : encoderTimer{timer}, encoderResolution{resolution * timerBothEdges * gear}, usedEngine{ptr}, params{param}
    {
        HAL_TIM_Encoder_Start(&timer, TIM_CHANNEL_ALL);
        usedPid = new PidController();
    }
    ~EngineController() override { delete usedPid; }

    void setSpeed(int16_t newSpeed) final;

    void calculatePWMOutput() final;

    void stopEngine() final;

private:
    void updateCount();

    TIM_HandleTypeDef encoderTimer;
    uint16_t encoderResolution;
    PidController* usedPid;
    Engine* usedEngine;
    engineParams& params;
};
