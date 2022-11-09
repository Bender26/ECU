#pragma once

struct pidContext
{
    float kp = 1.2;
    float ki = 0.1;
    float kd = 0.2;
    int integralMaxResponse = 1000;
    int previousDifferentialError;
    int totalIntegralError;
    float summaryOfAll = 0;
    int pidResponse = 0;
};

class PidController
{
public:
    PidController() : pidParameters{} {}

    void resetPidErrors();
    int calculatePidResponse(int setSpeed, int measuredSpeed);

private:
    pidContext pidParameters;
};
