#include "WifiHandler.h"
#include "user_interface.h"

WifiHander::WifiHander(WiFiUDP &udp)
    : _udp{udp}
{
}

void WifiHander::start_wifi(const String &ssid, const String &passphrase, uint8_t node_id)
{
    _node_id = node_id;

    // Connect to WiFi
    WiFi.mode(WIFI_STA);
    wifi_set_sleep_type(NONE_SLEEP_T);
    WiFi.setOutputPower(17.5f);
    WiFi.begin(ssid, passphrase);
    while (WiFi.status() != WL_CONNECTED) {
        yield();
        delay(100);
        Serial.println(".");
    }
    Serial.println("Connected to WiFi");
    Serial.print("Address: ");
    Serial.println(WiFi.localIP());

    while(WiFi.localIP() == INADDR_NONE)
    {
        yield();
        delay(100);
    }

}

void WifiHander::set_udp_listener(uint16_t listener_port) 
{
    _udp.begin(listener_port);
    Serial.println("UDP started");
}

void WifiHander::set_udp_multicast_group(IPAddress multicast_group, uint16_t multicast_port)
{
    delay(100);
    if (_udp.beginMulticast(WiFi.localIP(), multicast_group, multicast_port))
    {
        Serial.println("UDP multicast started");
    }
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

void WifiHander::set_udp_multicast_target(IPAddress multicast_group,
                                          uint16_t multicast_port,
                                          uint8_t multicast_ttl) 
{
    _multicast_group = multicast_group;
    _multicast_port = multicast_port;
    _multicast_ttl = multicast_ttl;

    Serial.print("UDP multicast target set to: ");
    Serial.print(multicast_group);
    Serial.print(", ");
    Serial.println(multicast_port);
}
