#include "Accelerometer_LSM303D.h"

#include <Wire.h>

enum regAddr
{
  CTRL0             = 0x1F, // D
  CTRL1             = 0x20, // D
  CTRL2             = 0x21, // D
  CTRL3             = 0x22, // D
  CTRL4             = 0x23, // D
  CTRL5             = 0x24, // D
  CTRL6             = 0x25, // D
  CTRL7             = 0x26, // D
};

Accelerometer_LSM303D::Accelerometer_LSM303D()
    : I2CDevice(0x1D)
{
   // Accelerometer

    // 0x00 = 0b00000000
    // AFS = 0 (+/- 2 g full scale)
    writeReg(CTRL2, 0x00);

    // 0x97 = 0b10010111
    // AODR = 1001 (800 Hz ODR); AZEN = AYEN = AXEN = 1 (all axes enabled)
    writeReg(CTRL1, 0x97);

    // Magnetometer - disabled

    // 0x18 = 0b00011000
    // M_RES = 00 (high resolution mode); M_ODR = 110 (6.25 Hz ODR)
    writeReg(CTRL5, 0x18);
}

bool Accelerometer_LSM303D::update() 
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