#include <WifiHandler.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ParametersHandler.h>
#include <Sensors.h>

WiFiUDP udp;
WifiHander wifi_handler(udp);
ParametersHandler parameters;

constexpr size_t num_of_sensor = 1;
Sensor* sensors[num_of_sensor];

void setup() 
{
  Serial.begin(115200);
  
  parameters.init();
  
  wifi_handler.start_wifi(
    parameters.parameters.wifi_ssid,
    parameters.parameters.wifi_password,
    parameters.parameters.node_id
  );
  wifi_handler.set_udp_listener
  (
    parameters.parameters.udp_listener
  );
  wifi_handler.set_udp_target(
    IPAddress(parameters.parameters.server_ip),
    parameters.parameters.server_port
  );

  sensors[0] = new DummySensor();
}

void loop() 
{
  yield();

  int packetSize = udp.parsePacket();
  if (packetSize > 0) {
    switch(static_cast<uint8_t>(udp.read()))
    {
      case 's':
      case 'S':
        struct __attribute__((__packed__))
        {
          uint8_t sync_id = static_cast<uint8_t>(udp.read());
          uint32_t time = millis();
        } payload;
        wifi_handler.send_udp(
          Commands::TIMESYNC,
          &payload
        );
      break;
    }
  }

  for (size_t i = 0; i < num_of_sensor; i++)
  {
    if(sensors[i]->update())
    {
      sensors[i]->send(wifi_handler);
    }
  }
  
  delay(50);
}
