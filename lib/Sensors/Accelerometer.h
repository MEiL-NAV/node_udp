#pragma once

#include <Sensor.h>

class Accelerometer : public Sensor
{
public:
    void send(WifiHander& wifi_handler) final;
    virtual bool update() = 0;

protected:
    // m/s^2
    float X, Y, Z;
};