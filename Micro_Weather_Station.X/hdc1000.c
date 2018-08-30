/**
 * @Author
 *   Adom Kwabena
 * 
 * @File Name
 *   hdc1000.h
 * 
 * @Summary
 *   This header file provides APIs for interfacing with the HDC1000 temperature
 *   and humidity temperature from Texas Instruments 
 */

// Section: Included Files

#include "mcc_generated_files/mcc.h"
#include "hdc1000.h"

// Section: Module APIs

void hdc1000_read(uint8_t length, uint8_t* data_ptr)
{
    // Set status to -1 in order for loop to run at least once
    I2C1_MESSAGE_STATUS status = -1;
    uint8_t time_out = 0;
    
    while (status != I2C1_MESSAGE_FAIL && status != I2C1_MESSAGE_COMPLETE \
           && time_out != HDC1000_I2C_TRY_MAX)
    {
        I2C1_MasterRead(data_ptr, length, HDC1000_ADDRESS, &status);
        // Wait for I2C transaction to complete
        while (status == I2C1_MESSAGE_PENDING);
        // Try again if something goes wrong
        time_out++;
    }
}

void hdc1000_write(uint8_t length, uint8_t* data_ptr)
{
    // Set status to -1 in order for loop to run at least once
    I2C1_MESSAGE_STATUS status = -1;
    uint8_t time_out = 0;
    
    while (status != I2C1_MESSAGE_FAIL && status != I2C1_MESSAGE_COMPLETE \
           && time_out < HDC1000_I2C_TRY_MAX)
    {
        I2C1_MasterWrite(data_ptr, length, HDC1000_ADDRESS, &status);
        // Wait for I2C transaction to complete
        while (status == I2C1_MESSAGE_PENDING);
        // Try again if something goes wrong
        time_out++;
    }
}

void hdc1000_set_reg(uint8_t address, uint16_t value)
{
    uint8_t data[3] = {0, 0, 0};
    data[0] = address;
    // Get MSB of value
    data[1] = value >> 8;
    // Get LSB of value
    data[2] = value;
    hdc1000_write(3, &data[0]);
}

uint16_t hdc1000_get_reg(uint8_t address)
{
    uint8_t data[2] = {0, 0};
    data[0] = address;
    // Send address of register
    hdc1000_write(1, &data[0]);
    // Wait for conversion to complete
    __delay_ms(8);
    // Read data from specified address
    hdc1000_read(2, &data[0]);
    return (data[0] << 8) + data[1];
}

uint16_t hdc1000_get_temperature(void)
{
    return hdc1000_get_reg(TEMPERATURE_REGISTER);
}

uint16_t hdc1000_get_humidity(void)
{
    return hdc1000_get_reg(HUMIDITY_REGISTER);
}

uint16_t * hdc1000_get_everything(void)
{
    // Temperature(address 0x00) is read first before humidity(address 0x01)
    uint8_t data[4] = {TEMPERATURE_REGISTER, 0, 0, 0};
    uint16_t everything[2] = {0, 0};
    hdc1000_write(1, &data[0]);
    // Wait for conversion to complete
    __delay_ms(16);
    hdc1000_read(4, &data[0]);
    // Temperature data
    everything[0] = (data[0] << 8) + data[1];
    // Humidity data
    everything[1] = (data[2] << 8) + data[3];
    return &everything[0];
}
