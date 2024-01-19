#include "WifiHandler.h"

WifiHander::WifiHander(WiFiUDP &udp)
    : _udp{udp}
{
}

void WifiHander::start_wifi(const String &ssid, const String &passphrase)
{
    // Connect to WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passphrase);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.println(".");
    }
    Serial.println("Connected to WiFi");
    Serial.print("Address: ");
    Serial.println(WiFi.localIP());

    _udp.begin(50000); // Set the local port for UDP communication

    Serial.println("UDP started");
}

void WifiHander::set_udp_target(IPAddress target_ip, uint16_t target_port)
{
    _target_ip = target_ip;
    _target_port = target_port;

    Serial.print("UDP target set to: ");
    Serial.print(target_ip);
    Serial.print(", ");
    Serial.println(target_port);
}
