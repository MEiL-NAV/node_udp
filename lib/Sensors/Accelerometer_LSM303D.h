#pragma once

#include <Accelerometer.h>
#include <I2CDevice.h>

// Based on Arduino L3G library
class Accelerometer_LSM303D : public Accelerometer, I2CDevice
{
public:
    Accelerometer_LSM303D();
    bool update() override;

private:
    constexpr static uint8_t data_address = 0x28;
    constexpr static float   scaler       = 0.061f*9.805f/1000.0f;
};