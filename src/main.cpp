#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

#include <WifiHandler.h>
#include <ParametersHandler.h>
#include <Sensors.h>

WiFiUDP udp;
WifiHander wifi_handler(udp);
ParametersHandler parameters;

constexpr size_t num_of_sensor = 2;
Sensor* sensors[num_of_sensor];

void setup() 
{
  Wire.setTimeout(50U);
  Wire.setClock(400000);
  Wire.begin();
  Serial.begin(115200);
  
  parameters.init();
  
  wifi_handler.start_wifi(
    parameters.parameters.wifi_ssid,
    parameters.parameters.wifi_password,
    parameters.parameters.node_id
  );
  wifi_handler.set_udp_multicast_group
  (
    IPAddress(parameters.parameters.multicast_group_address),
    parameters.parameters.udp_listener
  );
  wifi_handler.set_udp_multicast_target(
    IPAddress(parameters.parameters.multicast_group_address),
    parameters.parameters.server_port,
    parameters.parameters.multicast_ttl
  );

  sensors[1] = new Gyroscope_L3GD20H();
  sensors[0] = new Accelerometer_LSM303D();
}

void loop() 
{
  yield();

  int packetSize = udp.parsePacket();
  if (packetSize > 0) {
    struct __attribute__((__packed__))
    {
      uint8_t sync_id;
      uint32_t time;
    } payload;
    switch(static_cast<uint8_t>(udp.read()))
    {
      case 's':
      case 'S':
        payload.sync_id = static_cast<uint8_t>(udp.read());
        payload.time = millis();
        wifi_handler.send_udp_multicast(
          Commands::TIMESYNC,
          &payload
        );
      break;
      default:
        Serial.println("UDP received. Size: " + String(packetSize));
      break;
    }
  }

  for (size_t i = 0; i < num_of_sensor; i++)
  {
    if(sensors[i]->update())
    {
      sensors[i]->send(wifi_handler);
      delay(1);
    }
  }
}
