#pragma once
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <CRC16.h>
#include <Commands.h>
#include <Messages.h>

class WifiHander
{
public:
    WifiHander(WiFiUDP& udp);

    void start_wifi(const String& ssid, const String& passphrase, uint8_t node_id);
    void set_udp_listener(uint16_t listener_port);
    void set_udp_multicast_group(IPAddress multicast_group, uint16_t multicast_port);

    void set_udp_target(IPAddress target_ip, uint16_t target_port);
    void set_udp_multicast_target(IPAddress multicast_group, uint16_t multicast_port, uint8_t multicast_ttl);

    template <typename T>
    bool send_udp(uint8_t command, const T* payload);

    template <typename T>
    bool send_udp_multicast(uint8_t command, const T* payload);

private:
    WiFiUDP& _udp;
    CRC16 crc16;
    uint8_t _node_id;

    IPAddress _target_ip;
    uint16_t _target_port;

    IPAddress _multicast_group;
    uint16_t _multicast_port;
    uint8_t _multicast_ttl;
};

template <typename T>
inline bool WifiHander::send_udp(uint8_t command, const T* payload)
{
    struct __attribute__((__packed__)) Packet
    {
        uint8_t node_id;
        uint8_t command;
        T payload;
        uint16_t CRC16;
    } packet;
    if(0 == _udp.beginPacket(_target_ip, _target_port))
    {
        //Serial.println("Can not begin packet!");
        return false;
    }
    packet.node_id = _node_id;
    packet.command = command;
    memcpy(static_cast<void*>(reinterpret_cast<uint8_t*>(&packet) + offsetof(Packet, payload)),
        static_cast<const void*>(payload), sizeof(T));
    packet.CRC16 = crc16.calculateCRC(reinterpret_cast<const uint8_t*>(&packet), sizeof(Packet) - sizeof(uint16_t));
    if(sizeof(Packet) != _udp.write(reinterpret_cast<uint8_t*>(&packet) , sizeof(Packet)))
    {
        //Serial.println("Error while write packet!");
        return false;
    }
    if(0 == _udp.endPacket())
    {
        //Serial.println("Error while end packet!");
        return false;
    }
    return true;
}

template <typename T>
inline bool WifiHander::send_udp_multicast(uint8_t command, const T* payload)
{
    struct __attribute__((__packed__)) Packet
    {
        uint8_t node_id;
        uint8_t command;
        T payload;
        uint16_t CRC16;
    } packet;
    if(0 == _udp.beginPacketMulticast(_multicast_group, _multicast_port, WiFi.localIP(), static_cast<int>(_multicast_ttl)))
    {
        //Serial.println("Can not begin packet!");
        return false;
    }
    packet.node_id = _node_id;
    packet.command = command;
    memcpy(static_cast<void*>(reinterpret_cast<uint8_t*>(&packet) + offsetof(Packet, payload)),
        static_cast<const void*>(payload), sizeof(T));
    packet.CRC16 = crc16.calculateCRC(reinterpret_cast<const uint8_t*>(&packet), sizeof(Packet) - sizeof(uint16_t));
    if(sizeof(Packet) != _udp.write(reinterpret_cast<uint8_t*>(&packet) , sizeof(Packet)))
    {
        //Serial.println("Error while write packet!");
        return false;
    }
    if(0 == _udp.endPacket())
    {
        //Serial.println("Error while end packet!");
        return false;
    }
    return true;
}
