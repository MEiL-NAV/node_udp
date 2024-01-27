#include "Gyroscope.h"

void Gyroscope::send(WifiHander &wifi_handler) 
{
    VectorPacket payload
    {
        time: millis(),
        X: X,
        Y: Y,
        Z: Z
    };

    wifi_handler.send_udp(
        Commands::GYROSCOPE_READING,
        &payload
    );
}