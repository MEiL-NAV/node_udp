#include "Gyroscope.h"

void Gyroscope::send(WifiHander &wifi_handler) 
{
    struct __attribute__((__packed__))
    {
        uint32_t time = millis();
        float X = X;
        float Y = Y;
        float Z = Z;
    } payload;

    wifi_handler.send_udp(
        Commands::GYROSCOPE_READING,
        &payload
    );
}