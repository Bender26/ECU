#include "PidController.hpp"

void PidController::resetPidErrors()
{
    pidParameters.previousDifferentialError = 0;
    pidParameters.totalIntegralError = 0;
}
int PidController::calculatePidResponse(int setSpeed, int measuredSpeed)
{
    int speedDifferenceError = setSpeed - measuredSpeed;
    float propotionalResponse{0}, integralResponse{0}, differentialResponse{0};

    pidParameters.totalIntegralError += speedDifferenceError;

    propotionalResponse = (float)(pidParameters.kp * speedDifferenceError);
    integralResponse = (float)(pidParameters.ki * pidParameters.totalIntegralError);
    differentialResponse = (float)(pidParameters.kd * (speedDifferenceError - pidParameters.previousDifferentialError));

    if (integralResponse >= pidParameters.integralMaxResponse)
        integralResponse = pidParameters.integralMaxResponse;
    else if (integralResponse <= -pidParameters.integralMaxResponse)
        integralResponse = -pidParameters.integralMaxResponse;

    pidParameters.previousDifferentialError = speedDifferenceError;

    pidParameters.summaryOfAll = propotionalResponse + integralResponse + differentialResponse;
    pidParameters.pidResponse = static_cast<int>(pidParameters.summaryOfAll);
    return pidParameters.pidResponse;
}
