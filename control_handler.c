/*
 * control_handler.c
 *
 *  Created on: Mar 2, 2025
 *      Author: PlasmaPC
 */

#include "control_handler.h"

// Static variables for internal state tracking
static bool doorIsOpen = false;
static uint32_t doorOpenTime = 0;
static bool processPause = false;



void init_gpio(void) {
	// Reset all outputs
	WritePin(&HeaterPin, GPIO_PIN_RESET);  	// Heater
	WritePin(&FanPin, GPIO_PIN_RESET);    		// Fan
	WritePin(&RHPin, GPIO_PIN_RESET);    		// Refrigeration
	WritePin(&EggTurnPin, GPIO_PIN_SET);
	WritePin(&VentPin, GPIO_PIN_SET);
	WritePin(&TiltLeftPin, GPIO_PIN_RESET);  	// TiltLeft
	WritePin(&TiltRightPin, GPIO_PIN_RESET); 	// TiltRight

	HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);

}

void set_gpio_pins(void) {
	// Disable all outputs
	WritePin(&HeaterPin, GPIO_PIN_SET);  		// Heater
	WritePin(&FanPin, GPIO_PIN_SET);    		// Fan1
	WritePin(&RHPin, GPIO_PIN_SET);    			// Refrigeration
	//WritePin(&EggTurnPin, GPIO_PIN_SET);
	WritePin(&VentPin, GPIO_PIN_SET);			// Fan2
	WritePin(&TiltLeftPin, GPIO_PIN_SET);		// motorRelay Turn left
	WritePin(&TiltRightPin, GPIO_PIN_SET);		// motorRelay Turn Right
	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_11);

}


// Function to monitor door status and handle alarms
void Door_Monitor(void) {
    // Check if the door sensor is triggered (door open)
    if (ReadPin(&DoorSensor) == GPIO_PIN_RESET) {
        // Door has been opened
        if (!doorIsOpen) {
            doorOpenTime = HAL_GetTick(); // Record the door open time
            doorIsOpen = true;
        } else if (HAL_GetTick() - doorOpenTime > DOOR_OPEN_ALARM_MS) {
            // Raise an alarm if the door is open beyond the threshold
            Serial2_Write("Door Open\n\r");  // Example serial alarm
        }
    } else {
        // Reset state when the door is closed
        doorIsOpen = false;
        doorOpenTime = 0;
    }
}


// Helper functions for controlling ventilation and heating

void startHeating(void) {
    // Logic to start the heater (turn on GPIO pin or set hardware control)
	WritePin(&HeaterPin, GPIO_PIN_RESET);  // Example: Turning heater ON (active low)
}

void stopHeating(void) {
    // Logic to stop the heater (turn off GPIO pin or set hardware control)
	WritePin(&HeaterPin, GPIO_PIN_SET);  // Example: Turning heater OFF
}

void startVentilation(void) {
    // Logic to start the ventilation (turn on GPIO pin or set hardware control)
	WritePin(&VentPin, GPIO_PIN_RESET);  // Example: Turning on fan
}

void stopVentilation(void) {
    // Logic to stop the ventilation (turn off GPIO pin or set hardware control)
	WritePin(&VentPin, GPIO_PIN_SET);  // Example: Turning off fan
}
