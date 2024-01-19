#include <WifiHandler.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ParametersHandler.h>

WiFiUDP udp;
WifiHander wifi_handler(udp);
ParametersHandler parameters;

void setup() 
{
  Serial.begin(115200);
  
  parameters.init();
  
  wifi_handler.start_wifi(
    parameters.parameters.wifi_ssid,
    parameters.parameters.wifi_password
  );

  wifi_handler.set_udp_target(
    IPAddress(parameters.parameters.server_ip),
    parameters.parameters.server_port
  );
}

void loop() {
  yield();
  // Your main code here
  unsigned long time = millis();

  wifi_handler.send_udp(&time);
  
  delay(10); // Adjust delay according to your needs
}
