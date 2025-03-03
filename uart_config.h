/*
 * uart_config.h
 *
 *  Created on: Mar 2, 2025
 *      Author: PlasmaPC
 */

#ifndef INC_UART_CONFIG_H_
#define INC_UART_CONFIG_H_

#include "main.h"
#include <stdbool.h>

extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/* Global Variables */
extern char tx_data[50];  // Define as a buffer
extern uint8_t rx_data;
extern bool cmd_rcv;
extern uint8_t devInit_cmd;
extern uint16_t DevAddress;

/* Function Prototypes */
void Serial_Init(void);
void Serial2_Write(const char *tx_data);  // Fix prototype
void Serial2_Read(uint8_t *rx_data);
void I2C_Write(uint8_t *i2c_cmd);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


#endif /* INC_UART_CONFIG_H_ */
