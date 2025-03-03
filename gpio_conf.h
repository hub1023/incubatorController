/*
 * gpio_conf.h
 *
 *  Created on: Mar 2, 2025
 *      Author: PlasmaPC
 */

#ifndef INC_GPIO_CONF_H_
#define INC_GPIO_CONF_H_

#include "main.h"

// GPIO pin configuration structure
typedef struct {
    GPIO_TypeDef *Port;
    uint16_t Pin;
} GPIO_PinConfig;

// Define sensor pin configurations as constants
extern const GPIO_PinConfig TiltLeftSensor;
extern const GPIO_PinConfig TiltRightSensor;
extern const GPIO_PinConfig DoorSensor;

// Define keypad pin configurations as constants
extern const GPIO_PinConfig DownKey;
extern const GPIO_PinConfig UpKey;
extern const GPIO_PinConfig MenuKey;
extern const GPIO_PinConfig SelectKey;
extern const GPIO_PinConfig AutoMode;

// Output pin configurations (const, as they are fixed at runtime)
extern const GPIO_PinConfig FanPin;
extern const GPIO_PinConfig HeaterPin;
extern const GPIO_PinConfig RHPin;
extern const GPIO_PinConfig TiltLeftPin;
extern const GPIO_PinConfig TiltRightPin;
extern const GPIO_PinConfig VentPin;
extern const GPIO_PinConfig EggTurnPin;
extern const GPIO_PinConfig PC9Pin;

// Function Prototypes
GPIO_PinState ReadPin(const GPIO_PinConfig *pinConfig);  // Corrected return type
void WritePin(const GPIO_PinConfig *pinConfig, GPIO_PinState state);

#endif /* INC_GPIO_CONF_H_ */
