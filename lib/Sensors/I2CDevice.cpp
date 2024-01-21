#include "I2CDevice.h"
#include <Wire.h>

I2CDevice::I2CDevice(uint8_t device_address) 
    : device_address{device_address}
{}

// Writes a gyro register
void I2CDevice::writeReg(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(device_address);
  Wire.write(reg);
  Wire.write(value);
  last_status = Wire.endTransmission();
}

// Reads a gyro register
uint8_t I2CDevice::readReg(uint8_t reg)
{
  uint8_t value;

  Wire.beginTransmission(device_address);
  Wire.write(reg);
  last_status = Wire.endTransmission();
  Wire.requestFrom(device_address, static_cast<uint8_t>(1));
  value = Wire.read();
  Wire.endTransmission();

  return value;
}
