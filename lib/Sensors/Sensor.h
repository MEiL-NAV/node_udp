#pragma once

#include <WifiHandler.h>

class Sensor
{
public:
    virtual void send(WifiHander& wifi_handler) = 0;
    virtual bool update() = 0;
};