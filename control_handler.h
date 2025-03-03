/*
 * control_handler.h
 *
 *  Created on: Mar 2, 2025
 *      Author: PlasmaPC
 */

#ifndef INC_CONTROL_HANDLER_H_
#define INC_CONTROL_HANDLER_H_

#include "pid_control.h"
#include "setpoints.h"
#include "uart_config.h"
#include "gpio_conf.h"


// Configuration constants
#define DOOR_OPEN_ALARM_MS 5000  // Define alarm time threshold

// Function prototypes


void init_gpio(void);
void set_gpio_pins(void);
void Door_Monitor(void);


// Control functions declarations
void set_gpio_pins(void);
void Door_Monitor(void);


void startHeating(void);
void stopHeating(void);
void startVentilation(void);
void stopVentilation(void);





#endif /* INC_CONTROL_HANDLER_H_ */
