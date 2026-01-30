#include <Arduino.h>

// **********************************
// ********1. Light Blinking Code****
// **********************************
// #define LED_PIN 2

// void setup() {
//   pinMode(LED_PIN, OUTPUT);
//   Serial.begin(115200);
//   Serial.println("Hello from setup");
// }

// void loop() {
//   digitalWrite(LED_PIN, HIGH);
//   Serial.println("LED ON");
//   delay(1000);

//   digitalWrite(LED_PIN, LOW);
//   Serial.println("LED OFF");
//   delay(1000);
// }

// **********************************
// **********2.Connet Wifi **********
// **********************************
// #include<WiFi.h>

// const char *ssid = "Intellinety";
// const char *password = "intellinety";

// void setup(){
//   Serial.begin(115200);
//   WiFi.begin(ssid,password);
//   while(WiFi.status() != WL_CONNECTED){
//     delay(500);
//     Serial.println("Connecting to wifi . . . ");
//   }
//   Serial.println("Connection successfull with wifi");
// }

// void loop(){}

// **********************************
// **********3.Create Wifi **********
// **********************************
// #include<WiFi.h>
// #include<esp_wifi.h>
// #include<esp_netif.h>

// const char *ssid = "ESP_32_WiFi";
// password must be in 8 words
// const char *password = "12345678";
// void setup(){
//   Serial.begin(115200);
//   Serial.println("Setting up the AP(Access Point) with ESP-32");
//   // mode: AP -> Access Point or like Router
//   WiFi.mode(WIFI_AP);
//   WiFi.softAP(ssid,password);
//   Serial.println("AP Ip address: ");
//   Serial.println(WiFi.softAPIP());
// }

// void loop(){
//   // connention info: low-level
//   wifi_sta_list_t stationList;
//   // connection info: high-level
//   tcpip_adapter_sta_list_t adapterList;

//   // get the value:
//   esp_wifi_ap_get_sta_list(&stationList);
//   tcpip_adapter_get_sta_list(&stationList, &adapterList);

//   // print the value:
//   Serial.println("Connected Device:");
//   Serial.println("------------------");
//   for(int i=0;i<adapterList.num;i++){
//     tcpip_adapter_sta_info_t station = adapterList.sta[i];
//     Serial.println("IP Address:");
//     Serial.println(IPAddress(station.ip.addr));
//   }
//   delay(1000);
// }

// *******************************************************
// **********4.Create Wifi See List In Websites **********
// *******************************************************
#include <WebServer.h>
#include <WiFi.h>
#include <esp_netif.h>
#include <esp_wifi.h>
#include <string>

WebServer server(80);

void handleRegister() {
  String name = server.arg("name");
  IPAddress ip = server.client().remoteIP();

  // for serial monitor:
  Serial.printf("Device Name:");
  Serial.println(name);

  // for website:
  String response = "";
  response += "Registered\n";
  response += "Device Name" + name + "\n";
  response += "Ip Address " + ip.toString() + "\n";
  server.send(200, "text/plain", response);
}

const char *ssid = "ESP_32_WiFi";
const char *password = "12345678";

void setup() {
  Serial.begin(115200);
  Serial.println("Setting up the AP(Access Point) with ESP-32");
  // mode: AP -> Access Point or like Router
  WiFi.softAP(ssid, password);
  Serial.println("AP Ip address: ");
  Serial.println(WiFi.softAPIP());
  server.on("/register", handleRegister);
  server.begin();
}

void loop() { server.handleClient(); }
