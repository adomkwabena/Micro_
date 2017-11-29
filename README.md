# Micro_Weather_Station
A tiny weather station based on the HDC1000 temperature and humidity sensor.

## Code
The code was tested on a PIC18F46K22 on an easypic v7 development board.
All configuration code for the MCU was created using MCC (Microchip Code Configurator).
Sensor output is displayed via a serial port connected to PORTC.

## Hardware Settings
An HDC1000 click board from mikroe was used as a breakout board for the sensor.
The MCU and the sensor talk via I2C using RC3/SCL and RC4/SDA on the MCU.
A USB-UART adapter is connected to RC6/TX and RC7/RX for serial output.
