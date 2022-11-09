#include "EngineController.hpp"

void EngineController::setSpeed(int32_t newSpeed)
{
    if (newSpeed != params.adjustedSpeed) usedPid->resetPidErrors();
    params.adjustedSpeed = newSpeed;
}

void EngineController::calculateSpeed()
{
    updateCount();
    params.measuredSpeed = (this->params.countedPulses * TIMER_FREQENCY * SECOND_IN_MINUTE) / this->encoderResolution;
    auto pidResponse = usedPid->calculatePidResponse(params.adjustedSpeed, params.measuredSpeed);
    params.outTest = pidResponse;
    params.actualPWM += pidResponse;
    if (params.actualPWM > 1000)
    {
        params.actualPWM = 1000;
    }
    if (params.actualPWM < -1000)
    {
        params.actualPWM = -1000;
    }
    usedEngine->setSpeed(params.actualPWM);
}

void EngineController::updateCount()
{
    this->params.countedPulses = (int16_t)__HAL_TIM_GET_COUNTER(&encoderTimer);
    __HAL_TIM_SET_COUNTER(&encoderTimer, 0);
}
