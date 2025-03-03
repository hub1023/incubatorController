/*
 * gpio_conf.c
 *
 *  Created on: Mar 2, 2025
 *      Author: PlasmaPC
 */

#include "gpio_conf.h"

// Define sensor pin configurations as constants
const GPIO_PinConfig DoorSensor = { GPIOA, GPIO_PIN_6 };
const GPIO_PinConfig AutoMode = { GPIOC, GPIO_PIN_8 };
const GPIO_PinConfig TiltLeftSensor = { GPIOC, GPIO_PIN_7 };
const GPIO_PinConfig TiltRightSensor = { GPIOA, GPIO_PIN_7 };

// Define keypad pin configurations as constants
const GPIO_PinConfig DownKey = { GPIOB, GPIO_PIN_3 };
const GPIO_PinConfig UpKey = { GPIOB, GPIO_PIN_5 };
const GPIO_PinConfig MenuKey = { GPIOB, GPIO_PIN_4 };
const GPIO_PinConfig SelectKey = { GPIOB, GPIO_PIN_10 };

// Define output pin configurations as constants
const GPIO_PinConfig HeaterPin = { GPIOA, GPIO_PIN_15 };
const GPIO_PinConfig FanPin = { GPIOC, GPIO_PIN_10 };
const GPIO_PinConfig RHPin = { GPIOC, GPIO_PIN_11 };
const GPIO_PinConfig EggTurnPin = { GPIOC, GPIO_PIN_12 };
const GPIO_PinConfig VentPin = { GPIOD, GPIO_PIN_2 };
const GPIO_PinConfig PC9Pin = { GPIOC, GPIO_PIN_9 };
const GPIO_PinConfig TiltRightPin = { GPIOC, GPIO_PIN_2 };
const GPIO_PinConfig TiltLeftPin = { GPIOC, GPIO_PIN_3 };

// Read state of pin (corrected return type)
GPIO_PinState ReadPin(const GPIO_PinConfig *pinConfig) {
	return HAL_GPIO_ReadPin(pinConfig->Port, pinConfig->Pin);
}

// Write state of pin
void WritePin(const GPIO_PinConfig *pinConfig, GPIO_PinState state) {
	HAL_GPIO_WritePin(pinConfig->Port, pinConfig->Pin, state);
}


// Application of ReadPin function (corrected argument)
void read_sensor_state(void) {

	// Sensor
	if (ReadPin(&DoorSensor) == GPIO_PIN_RESET) {
		//Serial2_Write("Door Open\n\r");
	}

	if (ReadPin(&TiltLeftSensor) == GPIO_PIN_RESET) {
		Serial2_Write("TiltLeftSensor\n\r");
	}

	if (ReadPin(&TiltRightSensor) == GPIO_PIN_RESET) {
		Serial2_Write("TiltRightSensor\n\r");
	}

	if (ReadPin(&AutoMode) == GPIO_PIN_RESET) {
		Serial2_Write("AutoMode\n\r");
	}

	// Keypad

	if (ReadPin(&SelectKey) == GPIO_PIN_RESET) {
		Serial2_Write("SelectKey\n\r");
	}

	if (ReadPin(&MenuKey) == GPIO_PIN_RESET) {
		Serial2_Write("MenuKey\n\r");
	}

	if (ReadPin(&UpKey) == GPIO_PIN_RESET) {
		Serial2_Write("UpKey\n\r");
	}

	if (ReadPin(&DownKey) == GPIO_PIN_RESET) {
		Serial2_Write("DownKey\n\r");
	}

}
/*
 void Write_Pin(GPIO_PinConfig pinConfig, GPIO_PinState state) {
 HAL_GPIO_WritePin(pinConfig.Port, pinConfig.Pin, state);
 }

 // Read a specific pin state

 GPIO_PinState ReadPin(IptPinConf sensorID) {
 if (sensorID >= NUM_INPUTS) {
 return GPIO_PIN_RESET; // Return a safe default if invalid sensorID
 }
 return HAL_GPIO_ReadPin(inputPins[sensorID].Port, inputPins[sensorID].Pin);
 }
 */
