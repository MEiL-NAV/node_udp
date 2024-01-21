#include "Gyroscope_L3GD20H.h"

#include <Wire.h>

Gyroscope_L3GD20H::Gyroscope_L3GD20H()
{
  // Low_ODR = 0 (low speed ODR disabled)
  writeReg(0x39, 0x00);
  
  // 0x00 = 0b00000000
  // FS = 00 (+/- 250 dps full scale)
  writeReg(0x23, 0x00);
  
  // 0xEF = 0b11101111
  // DR = 11 (800 Hz ODR); Disable filtration; PD = 1 (normal mode); Zen = Yen = Xen = 1 (all axes enabled)
  writeReg(0x20, 0xEF);
}

bool Gyroscope_L3GD20H::update() 
{
    Wire.beginTransmission(address);
    // assert the MSB of the address to get the gyro
    // to do slave-transmit subaddress updating.
    Wire.write(data_address | (1 << 7));
    Wire.endTransmission();
    Wire.requestFrom(address, static_cast<uint8_t>(6));
    
    int16_t measurements[3];

    if (3 * sizeof(int16_t) !=
        Wire.readBytes(reinterpret_cast<uint8_t *>(measurements),
                       3 * sizeof(int16_t))) 
    {
      return false;
    }

    X = measurements[0] * 8.75f;
    Y = measurements[1] * 8.75f;
    Z = measurements[2] * 8.75f;
    return true; 
}

// Writes a gyro register
void Gyroscope_L3GD20H::writeReg(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  last_status = Wire.endTransmission();
}

// Reads a gyro register
uint8_t Gyroscope_L3GD20H::readReg(uint8_t reg)
{
  uint8_t value;

  Wire.beginTransmission(address);
  Wire.write(reg);
  last_status = Wire.endTransmission();
  Wire.requestFrom(address, static_cast<uint8_t>(1));
  value = Wire.read();
  Wire.endTransmission();

  return value;
}