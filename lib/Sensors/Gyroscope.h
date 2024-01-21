#pragma once

#include <Sensor.h>

class Gyroscope : public Sensor
{
public:
    void send(WifiHander& wifi_handler) final;
    virtual bool update() = 0;

protected:
    // mdeg/s
    float X, Y, Z;
};