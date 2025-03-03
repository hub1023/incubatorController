/*
 * uart_config.c
 *
 *  Created on: Mar 2, 2025
 *      Author: PlasmaPC
 */

#include "uart_config.h"




#define CMD_BUF_SIZE 50

ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

char cmd_buffer[CMD_BUF_SIZE] = { 0 };
bool cmd_rcv = false;
char tx_data[50];
uint8_t rx_data;
uint8_t devInit_cmd;
uint16_t DevAddress;

/* Initialize rx Serial Communication */
void SerialRx_Init(void) {
    memset(cmd_buffer, 0, CMD_BUF_SIZE);
    HAL_UART_Receive_IT(&huart2, &rx_data, 1);
}

/* Read Data via UART2 */
void Serial2_Read(uint8_t *rx_data) {
    HAL_UART_Receive_IT(&huart2, rx_data, 1);  // Removed incorrect '&' operator
}

/* Initialize tx Serial Communication */
void SerialTx_Init(void) {
    memset(cmd_buffer, 0, CMD_BUF_SIZE);
    // Removed unnecessary transmit call
}

/* Send Data via UART2 */
void Serial2_Write(const char *tx_data) {
    HAL_UART_Transmit(&huart2, (uint8_t*)tx_data, strlen(tx_data), 100);
}

/* Initialize I2C Communication */
void I2C_Write(uint8_t *i2c_cmd) {
	HAL_I2C_Master_Transmit(&hi2c1, DevAddress, i2c_cmd, 1, HAL_MAX_DELAY);
}

/* UART Interrupt Callback */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {
		static uint8_t index = 0;

		if (rx_data == '\n') {
			cmd_buffer[index] = '\0';  // Null-terminate string
			cmd_rcv = true;
			index = 0;  // Reset buffer index
		} else {
			if (index < CMD_BUF_SIZE - 1) {
				cmd_buffer[index++] = rx_data;
			}
		}

		// Restart UART reception
		Serial2_Read(&rx_data);
	}
}

