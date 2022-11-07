/*
 * engineController.hpp
 *
 *  Created on: Mar 30, 2022
 *      Author: Bender
 */

#pragma once
#include "Engine.hpp"
#include "PidController.hpp"

#define ENCODER_RESOLUTION			8
#define TIMER_CONF_BOTH_EDGE_T1T2	4
#define MOTOR_GEAR					120
#define	TIMER_FREQENCY				100
#define	SECOND_IN_MINUTE			60

class IEngineController{
public:
	virtual ~IEngineController() = default;
	virtual void setParams(TIM_HandleTypeDef,Engine*) = 0;
	virtual void setSpeed(int32_t) = 0;
	virtual void calculateSpeed() = 0;
};
class EngineController : public IEngineController{
public:
	EngineController() :
		measuredSpeed{0},
		speed{0},
		actualPWM{0},
		resolution{ENCODER_RESOLUTION * TIMER_CONF_BOTH_EDGE_T1T2 * MOTOR_GEAR},
		pulse_count{0}
		{
			pid = new PidController(test);
		}

	EngineController(TIM_HandleTypeDef timer,Engine* ptr) :
		measuredSpeed{0},
		speed{0},
		actualPWM{0},
		timer{timer},
		resolution{ENCODER_RESOLUTION * TIMER_CONF_BOTH_EDGE_T1T2 * MOTOR_GEAR},
		pulse_count{0},
		usedEngine{ptr}
		{
			HAL_TIM_Encoder_Start(&timer, TIM_CHANNEL_ALL);
			pid = new PidController(test);
		}

	void setParams(TIM_HandleTypeDef tim,Engine* ptr){
		timer = tim;
		HAL_TIM_Encoder_Start(&timer, TIM_CHANNEL_ALL);
		usedEngine = ptr;
	}
	void setSpeed(int32_t newSpeed)
	{
		if(newSpeed != speed) pid->reset();
		speed = newSpeed;
	}


	void calculateSpeed(){
		updateCount();
		measuredSpeed = (this->pulse_count * TIMER_FREQENCY * SECOND_IN_MINUTE) / this->resolution;
		auto output = pid->calculatePid(speed, measuredSpeed);
		outTest = output;
		actualPWM = +output;
		usedEngine->setSpeed(actualPWM);
	}

	int32_t measuredSpeed;			// prędkość silnika
	int32_t speed;
	int32_t actualPWM;
	int32_t outTest;
private:
	TIM_HandleTypeDef timer;
	uint16_t resolution;		//rozdzielczość silnika
	int32_t pulse_count;		//zliczone impulsy
	PidController* pid;
	Engine* usedEngine;
	void updateCount(){
			this->pulse_count = (int16_t)__HAL_TIM_GET_COUNTER(&timer);
			__HAL_TIM_SET_COUNTER(&timer, 0);
		}
};
