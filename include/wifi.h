#ifdef  ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include "credentials.h"

namespace Wifi {

  void printStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print your WiFi shield's name:
    const char* hostname = WiFi.getHostname();
    Serial.print("Hostname: ");
    Serial.println(hostname);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
  }

  void setup() {
    ESP8266WiFiMulti wifiMulti;
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connecting to WiFi netowrk.");
    while (wifiMulti.run() != WL_CONNECTED) {
      delay(500);
    }
    printStatus();
  }
}
#else
namespace Wifi {
  void setup() {}
}
#endif
