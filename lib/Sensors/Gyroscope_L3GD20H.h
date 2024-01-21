#pragma once

#include <Gyroscope.h>
#include <I2CDevice.h>

// Based on Arduino L3G library
class Gyroscope_L3GD20H : public Gyroscope, I2CDevice
{
public:
    Gyroscope_L3GD20H();
    bool update() override;

private:
    constexpr static uint8_t data_address = 0x28;
    constexpr static float   scaler       = 8.75f;
};