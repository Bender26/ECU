#pragma once

struct param{
	float Kp = 4.5;//
	float Ki = 0.8;//0.8;
	float Kd = 0.5;//0.5
	int windup = 1000;
} test;
param test2{1.2,0.1,0.2};
param test3{1.2,0.8,0.5};
param test4{4.5,0.1,0.2};

class PidController{
public:
	PidController( float kp, float ki, float kd, int antiWindupLimit) :
		previousError{0},
		totalError{0},
		kp{kp},
		ki{ki},
		kd{kd},
		antiWindupLimit{antiWindupLimit}
		{}
	PidController(param& par) :
		previousError{0},
		totalError{0},
		kp{par.Kp},
		ki{par.Ki},
		kd{par.Kd},
		antiWindupLimit{par.windup}
		{}

	void reset()
	{
		previousError = 0;
		totalError = 0;
	}
	int calculatePid(int setpoint, int process_variable)
	{
		int error;
		float pTerm, iTerm, dTerm;

		error = setpoint - process_variable;		//obliczenie uchybu
		totalError += error;			//sumowanie uchybu

		pTerm = (float)(kp * error);		//odpowiedź członu proporcjonalnego
		iTerm = (float)(ki * totalError);	//odpowiedź członu całkującego
		dTerm = (float)(kd * (error - previousError));//odpowiedź członu różniczkującego

		if(iTerm >= antiWindupLimit) iTerm = antiWindupLimit;	//Anti-Windup - ograniczenie odpowiedzi członu całkującego
		else if(iTerm <= -antiWindupLimit) iTerm = -antiWindupLimit;

		previousError = error;	//aktualizacja zmiennej z poprzednią wartością błędu

		return (int)(pTerm + iTerm + dTerm);		//odpowiedź regulatora
	}
private:
	int previousError; 		//Poprzedni błąd dla członu różniczkującego
	int totalError;		//Suma uchybów dla członu całkującego
	float kp;			//Wzmocnienie członu proporcjonalnego
	float ki;			//Wzmocnienie członu całkującego*/
	float kd;			//Wzmocnienie członu różniczkującego*/
	int antiWindupLimit;		//Anti-Windup - ograniczenie członu całkującego*/
};
