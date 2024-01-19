#include "DummySensor.h"

void DummySensor::send(WifiHander &wifi_handler)
{
    wifi_handler.send_udp(
        Commands::DUMMY,
        &_counter
    );
}

bool DummySensor::update()
{
    _counter++;
    return true;
}