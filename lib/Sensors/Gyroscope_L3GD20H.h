#pragma once

#include <Gyroscope.h>

// Based on Arduino L3G library
class Gyroscope_L3GD20H : public Gyroscope
{
public:
    Gyroscope_L3GD20H();
    bool update() override;

private:

    void writeReg(byte reg, byte value);
    uint8_t readReg(byte reg);
    uint8_t last_status; // status of last I2C transmission

    constexpr static uint8_t data_address = 0x28;
    constexpr static uint8_t address = 0x6B;
};