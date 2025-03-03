/*
 * AHT10.c
 *
 *  Created on: Mar 2, 2025
 *      Author: PlasmaPC
 */

#include "AHT10.h"


// AHT10-specific constants and commands
#define AHT10_ADDRESS (0x38 << 1)               // AHT10 I2C address
#define AHT10_CMD_TRIGGER_MEASUREMENT 0xAC      // Command to trigger measurement
#define AHT10_INIT_DELAY 100                    // Initialization delay in ms
#define AHT10_MEASUREMENT_DELAY 80              // Measurement delay in ms

// Global variable to store sensor data
AHT10_Data sensorData = {0.0f, 0.0f};

// I2C communication buffer
static uint8_t AHT10_Init_Cmd[] = {0xE1, 0x08, 0x00}; // Initialization command
static uint8_t AHT10_RX_Data[6];                      // Buffer to store received data

//extern I2C_HandleTypeDef hi2c1; // Ensure this is defined in your main code

// Function to initialize AHT10
void AHT10_Init(void) {
    if (HAL_I2C_Master_Transmit(&hi2c1, AHT10_ADDRESS, AHT10_Init_Cmd,
                                sizeof(AHT10_Init_Cmd), HAL_MAX_DELAY) == HAL_OK) {
        HAL_Delay(AHT10_INIT_DELAY);  // Allow time for initialization
        Serial2_Write("AHT10 Initialized Successfully\r\n");
    } else {
        Serial2_Write("AHT10 Initialization Error\r\n");
    }
}

// Function to read data from AHT10
void AHT10_Read_Data(void) {
    uint8_t cmd = AHT10_CMD_TRIGGER_MEASUREMENT;

    // Trigger measurement
    if (HAL_I2C_Master_Transmit(&hi2c1, AHT10_ADDRESS, &cmd, 1, HAL_MAX_DELAY) != HAL_OK) {
        Serial2_Write("AHT10 Command Error\r\n");
        return;
    }

    HAL_Delay(AHT10_MEASUREMENT_DELAY);  // Wait for measurement to complete

    // Receive 6 bytes of data from AHT10
    if (HAL_I2C_Master_Receive(&hi2c1, AHT10_ADDRESS, AHT10_RX_Data, 6, HAL_MAX_DELAY) == HAL_OK) {
        uint32_t rawHumidity = (AHT10_RX_Data[1] << 12) | (AHT10_RX_Data[2] << 4) | (AHT10_RX_Data[3] >> 4);
        uint32_t rawTemperature = ((AHT10_RX_Data[3] & 0x0F) << 16) | (AHT10_RX_Data[4] << 8) | AHT10_RX_Data[5];

        // Corrected assignments
        sensorData.humidity = (float) rawHumidity * 100.0f / 1048576.0f;
        sensorData.temperature = (float) rawTemperature * 200.0f / 1048576.0f - 50.0f;

        // Declare tx_data buffer
        char tx_data[50];
        /*snprintf(tx_data, sizeof(tx_data), "Temp_*C: %.1f , RH_%%: %.1f \r\n",
                 sensorData.temperature, sensorData.humidity);*/

        snprintf(tx_data, sizeof(tx_data), "%.1f,%.1f \r\n",
                       sensorData.temperature, sensorData.humidity);

        Serial2_Write(tx_data);

    } else {
        Serial2_Write("AHT10 Read Error\r\n");
    }
}
