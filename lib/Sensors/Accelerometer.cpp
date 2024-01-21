#include "Accelerometer.h"

void Accelerometer::send(WifiHander &wifi_handler) 
{
    struct __attribute__((__packed__))
    {
        uint32_t time = millis();
        float X = X;
        float Y = Y;
        float Z = Z;
    } payload;

    wifi_handler.send_udp(
        Commands::ACCELEROMETER_READING,
        &payload
    );

    // Serial.print("X: ");
    // Serial.print(X);
    // Serial.print(", Y: ");
    // Serial.print(Y);
    // Serial.print(", Z: ");
    // Serial.println(Z);
}