#pragma once

#include <Sensor.h>

class DummySensor : public Sensor
{
public:
    void send(WifiHander& wifi_handler) override;
    bool update() override;

public:
    uint32_t _counter = 0;
};