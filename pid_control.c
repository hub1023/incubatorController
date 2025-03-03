/*
 * pid_control.c
 *
 *  Created on: Mar 3, 2025
 *      Author: PlasmaPC
 */


#include <math.h>  // Include for fmaxf, fminf
#include <stdio.h> // Include for snprintf
#include "pid_control.h"

// Static variable to store previous PID output for rate limiting
static float lastPidOutput = 0.0;
static int tuningDone = 0; // Ensure auto-tuning only happens once

// PID Output Limits
#define MIN_OUTPUT -50.0f
#define MAX_OUTPUT  50.0f

// Integral Windup Limits
#define MAX_INTEGRAL 20.0f
#define MIN_INTEGRAL -20.0f

// PID Rate Change Limit
#define MAX_PID_RATE_CHANGE 2.0f

// PID Auto-Tuning Parameters (Ziegler-Nichols)
#define KU 6.0f
#define TU 4.0f

// Feed-Forward Gain
#define KF 1.5f

// Temperature Deadband
#define DEADBAND 0.5f // Adjust this to a suitable range for your system

// Function to auto-tune PID parameters
void autoTunePID(PIDControl* pidCtrl) {
    pidCtrl->Kp = 0.6f * KU;
    pidCtrl->Ki = 1.2f * KU / TU;
    pidCtrl->Kd = 0.075f * KU * TU;
}

// PID Control Function with Anti-Windup and Output Clamping
float pidControl(float error, float feedForward, PIDControl* pidCtrl) {
    if (!tuningDone) {
        autoTunePID(pidCtrl);
        tuningDone = 1;
    }

    float proportional, integral, derivative, pidOutput;

    // Proportional Term
    proportional = pidCtrl->Kp * error;

    // Integral Term with Anti-Windup
    if (fabs(error) > 0.1) {  // Only accumulate the integral if error is significant
        pidCtrl->integral += error;
    } else {
        pidCtrl->integral = 0.0; // Reset integral if the error is small
    }
    // Apply integral windup limits
    pidCtrl->integral = fmaxf(fminf(pidCtrl->integral, MAX_INTEGRAL), MIN_INTEGRAL);
    integral = pidCtrl->Ki * pidCtrl->integral;

    // Derivative Term (Rate of Change of Error)
    derivative = pidCtrl->Kd * (error - pidCtrl->prevError);

    // Save Current Error for Next Iteration
    pidCtrl->prevError = error;

    // Compute Final PID Output with Feed-Forward
    pidOutput = proportional + integral + derivative + (KF * feedForward);

    // Apply Output Clamping to prevent saturation
    if (pidOutput > MAX_OUTPUT) {
        pidOutput = MAX_OUTPUT;
    } else if (pidOutput < MIN_OUTPUT) {
        pidOutput = MIN_OUTPUT;
    }

    return pidOutput;
}

// Function to adjust heating based on PID output
void adjustHeating(float pidOutput, float targetTemperature, float currentTemperature) {
    // Limit the PID output to a reasonable range
    pidOutput = fminf(fmaxf(pidOutput, lastPidOutput - MAX_PID_RATE_CHANGE),
                      lastPidOutput + MAX_PID_RATE_CHANGE);

    // Check if we are within the deadband range of the target temperature
    if (fabs(targetTemperature - currentTemperature) < DEADBAND) {
        // If within deadband, turn off the heater
        stopHeating();
    } else if (pidOutput > 0) {
        // Turn heater ON if PID output is positive
        startHeating();
    } else {
        // Turn heater OFF if PID output is negative or zero
        stopHeating();
    }

    // Format the message with PID output and send it via Serial2
    snprintf(tx_data, sizeof(tx_data), "pidOutput %.1f,", pidOutput);
    Serial2_Write(tx_data);
    snprintf(tx_data, sizeof(tx_data), "error %.1f,", (targetTemperature - currentTemperature));
        Serial2_Write(tx_data);

    lastPidOutput = pidOutput;
}

// Function to control temperature
void controlTemperature(void) {
    float targetTemperature = setpoints.values[1]; // Target heating temperature (HTR_TEMP-SP)
    float currentTemperature = sensorData.temperature; // Read from temperature sensor

    // Calculate temperature error
    float temperatureError = targetTemperature - currentTemperature;
    float feedForward = 0.0f;  // Assuming no feedforward for now

    // Get PID output based on temperature error
    float pidOutput = pidControl(temperatureError, feedForward, &pidCtrl);

    // Adjust heating based on PID output
    adjustHeating(pidOutput, targetTemperature, currentTemperature);
}

// Function to control the ventilation system
void controlVentilation(void) {
    float targetHumidity = setpoints.values[0];  // Target humidity (CH_%RH SP)
    float currentHumidity = sensorData.humidity;  // Read from humidity sensor

    // Calculate humidity error
    float humidityError = targetHumidity - currentHumidity;

    // Depending on the humidity error, trigger ventilation
    if (humidityError > 0) {
        // Reduce ventilation if humidity is too high (e.g., stop ventilation)
        stopVentilation();
    } else {
        // Increase ventilation if humidity is too low (e.g., start ventilation)
        startVentilation();
    }
}
