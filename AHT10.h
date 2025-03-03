/*
 * AHT10.h
 *
 *  Created on: Mar 2, 2025
 *      Author: PlasmaPC
 */

#ifndef INC_AHT10_H_
#define INC_AHT10_H_

#include "uart_config.h"

// Structure to store AHT10 sensor data
typedef struct {
    float temperature;
    float humidity;
} AHT10_Data;

extern AHT10_Data sensorData; // Declare global struct variable

// Function prototypes
void AHT10_Init(void);
void AHT10_Read_Data(void);

#endif /* INC_AHT10_H_ */
