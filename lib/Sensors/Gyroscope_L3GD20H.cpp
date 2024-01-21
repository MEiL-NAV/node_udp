#include "Gyroscope_L3GD20H.h"

#include <Wire.h>

Gyroscope_L3GD20H::Gyroscope_L3GD20H()
    : I2CDevice(0x6B)
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
    Wire.beginTransmission(device_address);
    // assert the MSB of the address to get the gyro
    // to do slave-transmit subaddress updating.
    Wire.write(data_address | (1 << 7));
    Wire.endTransmission();
    Wire.requestFrom(device_address, static_cast<uint8_t>(6));
    
    int16_t measurements[3];

    if (3 * sizeof(int16_t) !=
        Wire.readBytes(reinterpret_cast<uint8_t *>(measurements),
                       3 * sizeof(int16_t))) 
    {
      return false;
    }

    X = measurements[0] * scaler;
    Y = measurements[1] * scaler;
    Z = measurements[2] * scaler;
    return true; 
}