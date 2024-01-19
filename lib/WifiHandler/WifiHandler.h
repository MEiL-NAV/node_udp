#pragma once
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <CRC16.h>

class WifiHander
{
public:
    WifiHander(WiFiUDP& udp);

    void start_wifi(const String& ssid, const String& passphrase);
    void set_udp_target(IPAddress target_ip, uint16_t target_port);

    template <typename T>
    bool send_udp(const T* payload);

private:
    WiFiUDP& _udp;
    CRC16 crc16;
    IPAddress _target_ip;
    uint16_t _target_port;
};

template <typename T>
inline bool WifiHander::send_udp(const T* payload)
{
    struct __attribute__((__packed__)) Packet
    {
        T payload;
        uint16_t CRC16;
    } packet;

    if(0 == _udp.beginPacket(_target_ip, _target_port))
    {
        return false;
    }
    memcpy(static_cast<void*>(&packet), static_cast<const void*>(payload), sizeof(T));
    packet.CRC16 = crc16.calculateCRC(reinterpret_cast<const uint8_t*>(&payload), sizeof(T));
    if(sizeof(Packet) != _udp.write(reinterpret_cast<uint8_t*>(&packet) , sizeof(Packet)))
    {
        return false;
    }
    if(0 == _udp.endPacket())
    {
        return false;
    }
    return true;
}
