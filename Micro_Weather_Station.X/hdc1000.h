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

#ifndef HDC1000_H
#define	HDC1000_H

// Section: Module Definitions

// HDC1000 I2C and register addresses
#define HDC1000_ADDRESS         0x40
#define TEMPERATURE_REGISTER    0x00
#define HUMIDITY_REGISTER       0X01
#define CONFIG_REGISTER         0X02
#define SERIAL_ID_1             0xFB
#define SERIAL_ID_2             0xFC
#define SERIAL_ID_3             0xFD
#define MANUFACTURER_ID         0xFE
#define DEVICE_ID               0xFF

// Useful for setting and clearing bits of the configuration register
#define HEATER_ON              0x2000
#define HEATER_OFF             0x0000
#define MODE_TEMP_OR_HUMID     0x0000
#define MODE_TEMP_AND_HUMID    0x1000              
#define BATTERY_STATUS_MASK    0x0800      
#define TRES_11                0x0400
#define TRES_14                0x0000
#define HRES_8                 0x0200
#define HRES_11                0x0100
#define HRES_14                0x0000                 

// Enables retransmission of a byte if something goes wrong,
// the number of retries after a failure is HDC1000_I2C_TRY_MAX
#define HDC1000_I2C_TRY_MAX        5

// Optional macros for data acquisition
#define GET_TEMPERATURE()      hdc1000_get_reg(TEMPERATURE_REGISTER)
#define GET_HUMIDITY()         hdc1000_get_reg(HUMIDITY_REGISTER)

// Section: Module APIs

/**
 * @Summary
 *   This function abstracts I2C read transactions with the HDC1000 chip
 * 
 * @Preconditions
 *   I2C1_Initialize() should have been called before calling this function.
 *   
 * @Param
 *   length   - the number of bytes to be read from the HDC1000 chip.
 * 
 * @Param
 *   data_ptr - a pointer to an array in which data received from the chip is
 *   stored.
 * 
 * @Returns
 *    None
 */
void hdc1000_read(uint8_t length, uint8_t * data_ptr);

/**
 * @Summary
 *   This function abstracts I2C write transactions with the HDC1000 chip
 * 
 * @Preconditions
 *   I2C1_Initialize() should have been called before calling this function.
 *   Global and Peripheral Interrupts should be enabled before calling this
 *   function.
 *   
 * @Param
 *   length   - the number of bytes to be sent to the HDC1000 chip.
 * 
 * @Param
 *   data_ptr - a pointer to an array from which data will be sent
 * 
 * @Returns
 *    None
 */
void hdc1000_write(uint8_t length, uint8_t * data_ptr);

/**
 * @Summary
 *   This function provides a means to edit the values of a register
 * 
 * @Param 
 *   address - the address of the register to be modified.
 * 
 * @Param
 *   value - the new contents of the register
 * 
 * @Returns
 *   None.
 */
void hdc1000_set_reg(uint8_t address, uint16_t value);

/**
 * @Summary
 *   This function provides access to the contents of the registers
 *   of the HDC1000 chip.
 * 
 * @Param 
 *   address - the address of the register to be accessed.
 * 
 * @Returns
 *   The contents of the register specified.
 */
uint16_t hdc1000_get_reg(uint8_t address);

/**
 * @Summary
 *   This function triggers a temperature conversion and returns the result.
 * 
 * @Preconditions
 *   Initialize the contents of the status register before calling this function.
 *   The function hdc1000_set_reg(CONFIG_REGISTER, mode) has to be called, where
 *   the mode should enable measuring temperature or humidity.
 * 
 * @Param
 *   None.
 * 
 * @Returns
 *   The result of the temperature conversion.
 */
uint16_t hdc1000_get_temperature(void);

/**
 * @Summary
 *   This function triggers a humidity conversion and returns the result.
 * 
 * @Preconditions
 *   Initialize the contents of the status register before calling this function.
 *   The function hdc1000_set_reg(CONFIG_REGISTER, mode) has to be called, where
 *   the mode should enable measuring temperature or humidity.
 * 
 * @Param
 *   None.
 * 
 * @Returns
 *   The result of the humidity conversion.
 */
uint16_t hdc1000_get_humidity(void);

/**
 * @Summary
 *   This function triggers a temperature and humidity conversion and returns
 *   the result.
 * 
 * @Preconditions
 *   Initialize the contents of the status register before calling this function.
 *   The function hdc1000_set_reg(CONFIG_REGISTER, mode) has to be called, where
 *   the mode should enable measuring temperature and humidity.
 * 
 * @Param
 *   None.
 * 
 * @Returns
 *   Address of a two element array where the first element is the temperature 
 *   value and the second element is the humidity value.
 */
uint16_t * hdc1000_get_everything(void);

#endif	/* HDC1000_H */

