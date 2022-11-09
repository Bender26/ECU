#pragma once

struct pidContext
{
    float kp = 1.2;
    float ki = 0.1;
    float kd = 0.2;
    int integralMaxResponse = 1000;
    float sum = 0;
    int ret = 0;
};

class PidController
{
public:
    PidController() : previousDifferentialError{0}, totalIntegralError{0}, pidParameters{} {}

    void resetPidErrors()
    {
        previousDifferentialError = 0;
        totalIntegralError = 0;
    }
    int calculatePidResponse(int setSpeed, int measuredSpeed)
    {
        int speedDifferenceError = setSpeed - measuredSpeed;
        float propotionalResponse{0}, integralResponse{0}, differentialResponse{0};

        totalIntegralError += speedDifferenceError; // sumowanie uchybu

        propotionalResponse = (float)(pidParameters.kp * speedDifferenceError); // odpowiedź członu proporcjonalnego
        integralResponse = (float)(pidParameters.ki * totalIntegralError); // odpowiedź członu całkującego
        differentialResponse =
            (float)(pidParameters.kd * (speedDifferenceError - previousDifferentialError)); // odpowiedź członu
                                                                                            // różniczkującego

        if (integralResponse >= pidParameters.integralMaxResponse)
            integralResponse = pidParameters.integralMaxResponse; // Anti-Windup - ograniczenie
                                                                  // odpowiedzi członu całkującego
        else if (integralResponse <= -pidParameters.integralMaxResponse)
            integralResponse = -pidParameters.integralMaxResponse;

        previousDifferentialError = speedDifferenceError;

        pidParameters.sum = propotionalResponse + integralResponse + differentialResponse;
        pidParameters.ret = static_cast<int>(pidParameters.sum);
        return pidParameters.ret; //(int)(propotionalResponse + integralResponse +
                                  // differentialResponse);
    }

private:
    int previousDifferentialError; // Poprzedni błąd dla członu różniczkującego
    int totalIntegralError;
    pidContext pidParameters; // Suma uchybów dla członu całkującego

    int antiWindupLimit; // Anti-Windup - ograniczenie członu całkującego*/
};
