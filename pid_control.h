/*
 * pid_control.h
 *
 *  Created on: Mar 3, 2025
 *      Author: PlasmaPC
 */

#include "AHT10.h"
#include "setpoints.h"
#include "uart_config.h"

#ifndef INC_PID_CONTROL_H_
#define INC_PID_CONTROL_H_



float pidControl(float error, float feedForward, PIDControl* pidCtrl);
void adjustHeating(float pidOutput, float targetTemperature, float currentTemperature);
//void adjustHeating(float currentTemperature, float targetTemperature);
void controlTemperature(void);
void controlVentilation(void);

#endif /* INC_PID_CONTROL_H_ */
