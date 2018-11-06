#define lightPin D0
#define waterPin D1

#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <ArduinoJson.h> 
#include <TroykaDHT11.h>

File fsUploadFile;
DHT11 dht(D4);
ESP8266WebServer server(80);


String ssid = "podlev";
String password = "89278615058";
String jsonConfig = "{}";

int timeZone = 3; // Central European Time

//интервал освещения
byte lightStartH = 19; 
byte lightStopH = 23;
byte lightStartM = 0; 
byte lightStopM = 60;

//интервал полива
byte waterStartH = 0; 
byte waterStopH = 23;
byte period = 1;
byte waterStartM = 0; 
byte waterStopM = 10;

byte lightStatus;
byte waterStatus;

byte valueT = -1;
byte valueH = -1;

byte NOWDAY;
byte NOWHOUR;
byte NOWMINUTE;

void setup() {
    //Настройка Pin
    pinMode(lightPin, OUTPUT);
    pinMode(waterPin, OUTPUT);
    digitalWrite(lightPin, 1);
    digitalWrite(waterPin, 1);
    //Монитор порта
    Serial.begin(115200);
    dht.begin();
    spiffsStart();
    loadConfig();
    wifiSetup();
    delay(1000);
    updateTime();
    serverStart();
    
    NOWDAY = day();
    NOWHOUR = hour();
    NOWMINUTE = minute();

    checkLightWater();
}


void loop() {
   if (NOWMINUTE != minute()) {
       temperature();
       checkLightWater();
       NOWMINUTE = minute();
    }
   server.handleClient();
}
