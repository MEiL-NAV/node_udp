#include "Accelerometer.h"

void Accelerometer::send(WifiHander &wifi_handler) 
{
    VectorPacket payload
    {
        time: millis(),
        X: X,
        Y: Y,
        Z: Z
    };
    
    wifi_handler.send_udp_multicast(
        Commands::ACCELEROMETER_READING,
        &payload
    );
}