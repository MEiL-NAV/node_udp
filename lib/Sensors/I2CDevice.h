#pragma once

#include <cstdint>

class I2CDevice 
{
protected:
    I2CDevice(uint8_t device_address);

    uint8_t last_status; // status of last I2C transmission

    void writeReg(uint8_t reg, uint8_t value);
    uint8_t readReg(uint8_t reg);

    const uint8_t device_address;
};